from machine import Pin, UART, unique_id, Timer
from mqtt import MQTTClient
import ntptime
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
ntptime.settime()
(year,month,day,week,hour,minute,second,mili) = rtc.datetime()
rtc.datetime((year,month,day,week,hour-5,minute,second,mili))

#from machine import RTC
#rtc = RTC()

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
com = 30
load_alarm()
comp_alarm = False
inh = False
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
            elif mensaje2[0] == "CONF":
                for i in range(0,len(mensaje2)-1,9):
                    ALARM[str(i)] = "CONF_INVER," + mensaje2[i+1] + "," + mensaje2[i+2] + "," + mensaje2[i+3] + "," + mensaje2[i+4] + "," + mensaje2[i+5] + "," + mensaje2[i+6] + "," + mensaje2[i+7] + "," + mensaje2[i+8]
                try:
                    for y in ALARM:
                        if x > int(y):
                            x=int(y)
                    da = ALARM[str(x)].split(",")
                    com = int(da[6]) + int(da[7])/60
                except:
                    com=30
            elif mensaje2[0] == "HORA":
                uart.write(mensaje)
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
        if comp_alarm:
            if not inh:
                sep = ALARM[str(x)].split(",")
                uart.write(+";")
                del ALARM[str(x)]
                uos.remove("/alarm.json")
                save_alarm()
                inh = True
                x=x+1
            else:
                try:
                    da = alarm[str(x)].split(",")
                    com = int(da[6]) + int(da[7])/60
                except:
                    com = 30
                comp_alarm = False
                inh = False
