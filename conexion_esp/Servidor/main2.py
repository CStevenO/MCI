from mqtt import MQTTClient
import time
from machine import RTC
import sys

rtc = RTC()
uart = UART(1,9600)

def Conexion_MQTT():
    #client_id = b"Covid_1" + ubinascii.hexlify(machine.unique_id())
    client_id = b"SP30"
    mqtt_server = '10.50.1.153'
    port_mqtt = 1883
    user_mqtt = None #Si su servidor no necesita usuario escribe None sin comillas
    pswd_mqtt = None #Si su servidor no necesita contraseña escribe None sin comillas
    client = MQTTClient(client_id, mqtt_server,port_mqtt,user_mqtt,pswd_mqtt)
    client.set_callback(form_sub)
    client.connect(True)
    client.subscribe(b'SAL_DA')
    print('Conectado a %s' % mqtt_server)
    return client

def Reinciar_conexion():
    print('Fallo en la conexion. Intentando de nuevo...')
    time.sleep(1)
    sys.exit()

def form_sub(topic, msg):
    global mensaje
    mensaje = msg.decode()
    if topic.decode() is "PROGRAMADOR":
        mensaje = hola
    elif topic.decode() is "SAL_DA":
        espera = True
        print(mensaje)
    print(mensaje)

def kpalive():
    global client
    try:
        disp_pub = client.check_msg()
        client.publish(b'ING_DATOS', b"05,Hola;")
        time.sleep(.1)
    except:
        print("Conexión Perdida")
        Reinciar_conexion()

def leer_uart():
    global mensaje_entrada, sr, wdt
    while True:
        data = uart.read(1)
        if data==b";":
            mensaje_entrada=sr.decode("utf-8")
            sr=b""
            break
        elif data is not None:
            sr=sr+data

mensaje_entrada = ""
mensaje = ""
conf = False
if __name__ == '__main__':
    mensaje2= ["","",""]
    wdt = WDT(timeout=90000)
    try:
        print("conectando MQTT...")
        client = Conexion_MQTT()
    except:
        print("No MQTT")
        Reinciar_conexion()
    time.sleep(1)
    while True:
        if uart.any() is 0:
            if client.check_msg() is not None:
                client.wait_msg()
        else:
            leer_uart()
            while conf is False:
                try:
                    disp_pub = client.check_msg()
                    client.publish(b'ING_DATOS', mensaje_entrada.encode())
                    time.sleep(.1)
                except:
                    print("No Mensaje")
                    Reinciar_conexion()
                client.wait_msg()
                mensaje2 = mensaje.replace(";","").split(",")
                if mensaje2[1] == "SI":
                    conf = True
            conf = False
