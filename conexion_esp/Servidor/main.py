from machine import I2C, Pin, UART, unique_id, Timer, WDT
from mqtt import MQTTClient
import micropython
import time
import ubinascii
import machine
import math
import boot

uart = UART(0, 115200)


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


def codigo_de_barras():
    global codigo , sr , wdt
    while True:
        start = time.ticks_ms()
        while uart.any() is 0:
            wdt.feed()
            delta = time.ticks_diff(time.ticks_ms(), start)
            if delta >= 10000:
                kpalive()
                start = time.ticks_ms()
        data = uart.read(1)
        if data==b"\r":
            codigo=sr.decode("utf-8")[0:len(sr)-3]
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

def uart_lectura():
    global read_text
    read_text = read_text + uart.read(uart.any())

def intentos():
    global read_text,index_final
    if uart.any() is not 0:
        uart_lectura()
    try:
        index_final = read_text.index(";")
        transmi()
    except:
        intentos()

CONFIG = {
    "broker": '10.50.1.153',
    "client_id": b'SP30',
    "subscribe": b'MCI_ST_OUT',
    "publish": b'MCI_SP_IN'
}
sr=b""
mensaje = ""
espera = False
codigo = ""
contador = 0
read_text = ""
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
            mensaje2 = mensaje.replace(";","").split(",")
            if mensaje2[0] == "IPWEB":
                ip_sol()
            elif mensaje[0] == "RED":
                pass
            elif mensaje2[0] == "CONF_INVER":
                pass
            elif mensaje2[0] == "HORA":
                pass
            else:
                pass
        if uart.any() is not 0:
            read_text = uart.read(uart.any())
            intentos()
            try:
                disp_pub = client.check_msg()
                client.publish(CONFIG["publish"], read_text.encode())
            except:
                print("No Mensaje")
                Reinciar_conexion()
            #enviar informacion a mqtt
