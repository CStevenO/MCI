from machine import Pin, UART, unique_id, Timer, RTC
from umqtt.robust import MQTTClient
import time
import ubinascii
import machine
import math
import boot
import uos

uos.dupterm(None, 1)
uart = UART(0, baudrate=9600, bits=8, parity=None, stop=1, rxbuf=50, timeout=0, timeout_char=2)
#UART(0, baudrate=9600, bits=8, parity=None, stop=1, rxbuf=15, timeout=0, timeout_char=2)
tim0 = Timer(0)
rtc = RTC()

def load_last():
    import ujson as json
    try:
        with open("/last.json") as f:
            last = json.loads(f.read())
    except (OSError, ValueError):
        print("Couldn't load /last.json")
        save_alarm()
    else:
        LAST.update(last)
        print("Loaded alarm from /last.json")

def save_last():
    import ujson as json
    try:
        with open("/last.json", "w") as f:
            f.write(json.dumps(LAST))
    except OSError:
        print("Couldn't save /last.json")

def load_alarm():
    import ujson as json
    try:
        with open("/alarm.json") as f:
            alarm = json.loads(f.read())
    except (OSError, ValueError):
        print("Couldn't load /alarm.json")
        save_alarm()
    else:
        ALARM.update(alarm)
        print("Loaded alarm from /alarm.json")

def save_alarm():
    import ujson as json
    try:
        with open("/alarm.json", "w") as f:
            f.write(json.dumps(ALARM))
    except OSError:
        print("Couldn't save /alarm.json")

def alarma():
    global com,comp_alarm
    hora = rtc.datetime()
    if com <= (int(hora[4])+int(hora[5])/60):
        comp_alarm = True

ALARM = {
}
def Conexion_MQTT():
    #client_id = b"Covid_1" + ubinascii.hexlify(machine.unique_id())
    client_id = CONFIG["client_id"]
    mqtt_server = CONFIG["broker"]
    port_mqtt = 1883
    user_mqtt = None #Si su servidor no necesita usuario escribe None sin comillas
    pswd_mqtt = None #Si su servidor no necesita contraseña escribe None sin comillas
    client = MQTTClient(client_id, mqtt_server,port_mqtt,user_mqtt,pswd_mqtt)
    client.DEBUG = True
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
LAST = {
}
CONFIG = {
    "broker": '10.50.1.153',
    "client_id": b'SP30',
    "subscribe": b'MCI_ST_OUT',
    "publish": b'MCI_SP_IN'
}
com = 30
load_alarm()
load_last()
comp_alarm = False
x = 500000
try:
    for y in ALARM:
        if x > int(y):
            x=int(y)
    da = ALARM[str(x)].split(",")
    com = int(da[6]) + int(da[7])/60
except:
    com=30
sr=b''
mensaje = ""
espera = False
contador = 0
read_text = ""
tim0.init(period=20000,mode=Timer.PERIODIC,callback=lambda t:alarma())
while uart.any() is not 0:
    uart.read(1)
if __name__ == '__main__':
    mensaje2 = ["","",""]
    mensaje_re = ["","",""]
    load_config()
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
            elif mensaje2[0] == "CONF":
                ALARM.clear()
                for i in range(0,len(mensaje2)-1,9):
                    ALARM[str(int(i/9))] = "CONF_INVER," + mensaje2[i+1] + "," + mensaje2[i+2] + "," + mensaje2[i+3] + "," + mensaje2[i+4] + "," + mensaje2[i+5] + "," + mensaje2[i+6] + "," + mensaje2[i+7] + "," + mensaje2[i+8]
                    print(i)
                save_alarm()
                try:
                    x=0
                    da = ALARM[str(x)].split(",")
                    com = int(da[6]) + int(da[7])/60
                except:
                    com=30
                    x=0
            elif mensaje2[0] == "HORA":
                uart.write(mensaje)
                rtc.datetime((mensaje2[1],mensaje2[2],mensaje2[3],0,mensaje2[4],mensaje2[5],mensaje2[6],0))
            else:
                print("otros")
        if uart.any() is not 0:
            uart_lectura()
            if (read_text.split(",")[0] is "ACT"):
                try:
                    uart.write(LAST[read_text.split(",")[1]]+";")
                except:
                    uart.write("CONF_INVER," + read_text.split(",")[1] + ",OFF,OFF,OFF,OFF,0,0,0;")
            else:
                try:
                    disp_pub = client.check_msg()
                    client.publish(CONFIG["publish"], read_text.encode())
                except:
                    print("No Mensaje")
                    Reinciar_conexion()
        if comp_alarm:
            comp_alarm = False
            sep = ALARM[str(x)].split(",")
            LAST[str(sep[1])] = ALARM[str(x)]
            uart.write(ALARM[str(x)]+";")
            save_last()
            del ALARM[str(x)]
            uos.remove("/alarm.json")
            save_alarm()
            x=x+1
            try:
                da = ALARM[str(x)].split(",")
                com = int(da[6]) + int(da[7])/60
            except:
                com=30
