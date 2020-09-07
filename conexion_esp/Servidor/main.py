from machine import I2C, Pin, UART, unique_id, Timer, WDT
from mqtt import MQTTClient
import micropython
import time
import ubinascii
import machine
import math
import boot
import uos

uos.dupterm(None, 1)
uart = UART(0, baudrate=9600, bits=8, parity=None, stop=1, rxbuf=50, timeout=0, timeout_char=2)
#UART(0, baudrate=9600, bits=8, parity=None, stop=1, rxbuf=15, timeout=0, timeout_char=2)



#from machine import RTC
#rtc = RTC()


def Conexion_MQTT():
    #client_id = b"Covid_1" + ubinascii.hexlify(machine.unique_id())
    client_id = CONFIG["client_id"]
    mqtt_server = CONFIG["broker"]
    port_mqtt = 1883
    user_mqtt = None #Si su servidor no necesita usuario escribe None sin comillas
    pswd_mqtt = None #Si su servidor no necesita contraseña escribe None sin comillas
    client = MQTTClient(client_id, mqtt_server,port_mqtt,user_mqtt,pswd_mqtt)
    client.set_callback(form_sub)
    client.connect(True)
    client.subscribe(CONFIG["subscribe"])
    print('Conectado a %s' % mqtt_server)
    return client

def Reinciar_conexion():
    print('Fallo en la conexion. Intentando de nuevo...')
    time.sleep(3)
    machine.reset()

def load_config():
    import ujson as json
    try:
        with open("/config.json") as f:
            config = json.loads(f.read())
    except (OSError, ValueError):
        print("Couldn't load /config.json")
        save_config()
    else:
        CONFIG.update(config)
        print("Loaded config from /config.json")

def save_config():
    import ujson as json
    try:
        with open("/config.json", "w") as f:
            f.write(json.dumps(CONFIG))
    except OSError:
        print("Couldn't save /config.json")


def uart_lectura():
    global read_text, sr
    while True:
        data = uart.read(1)
        if data==b";":
            read_text=sr.decode()
            sr=b""
            break
        elif data is not None:
            sr=sr+data


def form_sub(topic, msg):
    global mensaje, espera
    mensaje = msg.decode()
    if topic.decode() is CONFIG["subscribe"]:
        espera = True

def kpalive():
    global client
    try:
        disp_pub = client.check_msg()
        client.publish(CONFIG["publish"], b"KP,Hola;")
        time.sleep(.1)
    except:
        print("Conexión Perdida")
        Reinciar_conexion()

def ip_sol():
    global client
    web_so = "IPWEB," + CONFIG["client_id"] + "," + wlan.ifconfig()[0] + ";"
    try:
        disp_pub = client.check_msg()
        client.publish(CONFIG["publish"], web_so.encode())
    except:
        print("No Mensaje")
        Reinciar_conexion()

CONFIG = {
    "broker": '10.50.1.153',
    "client_id": b'SP30',
    "subscribe": b'MCI_ST_OUT',
    "publish": b'MCI_SP_IN'
}
sr=b''
mensaje = ""
espera = False
contador = 0
read_text = ""
while uart.any() is not 0:
    uart.read(1)
if __name__ == '__main__':
    mensaje2 = ["","",""]
    mensaje_re = ["","",""]
    load_config()
    #wdt = WDT(timeout=90000)
    try:
        print("conectando MQTT...")
        client = Conexion_MQTT()
    except:
        print("No MQTT")
        Reinciar_conexion()
    ip_sol()
    time.sleep(1)
    while True:
        if client.check_msg():
            client.wait_msg()
        if espera:
            espera = False
            mensaje2 = mensaje.split(",")
            if mensaje2[0] == "IPWEB":
                ip_sol()
            elif mensaje2[0] == "RED":
                uart.write(mensaje)
                print("red")
            elif mensaje2[0] == "CONF_INVER":
                uart.write(mensaje)
                print("conf")
            elif mensaje2[0] == "HORA":
                uart.write(mensaje)
                print("hora")
            else:
                print("otros")
        if uart.any() is not 0:
            uart_lectura()
            if (read_text.split(","))[0] is "ACT":
                pass
            else:
                try:
                    disp_pub = client.check_msg()
                    client.publish(CONFIG["publish"], read_text.encode())
                except:
                    print("No Mensaje")
                    Reinciar_conexion()
