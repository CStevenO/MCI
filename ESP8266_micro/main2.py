from machine import I2C, Pin, UART, unique_id, Timer, WDT
from mqtt import MQTTClient
import micropython
import time
import ubinascii
import machine


def Conexion_MQTT():
    #client_id = b"Covid" + ubinascii.hexlify(machine.unique_id())
    client_id = b"prueba"
    mqtt_server = '10.50.1.153'
    #mqtt_server = 'mantenimiento.elite.local'
    port_mqtt = 1883
    user_mqtt = None #Si su servidor no necesita usuario escribe None sin comillas
    pswd_mqtt = None #Si su servidor no necesita contraseña escribe None sin comillas
    client = MQTTClient(client_id, mqtt_server,port_mqtt,user_mqtt,pswd_mqtt)
    client.set_callback(form_sub)
    client.connect(True)
    client.subscribe(b'SAL_DA')
    print('Conectado a %s' % mqtt_server)
    client.set_last_will(b'SAL_DA',b'Desconexión Inesperada')
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

def form_sub(topic, msg):
    global mensaje, espera
    mensaje = msg.decode()
    if topic.decode() is "HORA":
        dat = mensaje.replace(";","").split(",")
        rtc.datetime((dat[1],dat[2],dat[3],0,dat[4],dat[5],dat[6]))
        print(rtc.datetime())
    elif topic.decode() is "SAL_DA":
        espera = True
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

sr=b""
mensaje = ""
espera = False
codigo = ""
contador = 0
try:
    time.sleep(.5)
    print("conectando MQTT...")
    client = Conexion_MQTT()
except:
    print("No MQTT")
    Reinciar_conexion()
try:
    disp_pub = client.check_msg()
    client.publish(b'ING_DATOS', b'00,16523')
except:
    print("No Mensaje")
    Reinciar_conexion()
client.wait_msg()
try:
    print(mensaje2[1])
except:
    time.sleep(2)
    mensaje2 = mensaje.replace(";","").split(",")
    print(mensaje2[1])
if __name__ == '__main__':
    mensaje2 = ["","",""]
