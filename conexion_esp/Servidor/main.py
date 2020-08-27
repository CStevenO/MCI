from machine import I2C, Pin, UART, unique_id, Timer, WDT
from mqtt import MQTTClient
import micropython
import time
import ubinascii
import machine
import math

uart = UART(2, 115200)


from machine import RTC
rtc = RTC()


def Conexion_MQTT():
    #client_id = b"Covid_1" + ubinascii.hexlify(machine.unique_id())
    client_id = b""
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

CONFIG = {
    "broker": "mantenimiento.elite.local",
    "client_id": b"esp8266_" + ubinascii.hexlify(machine.unique_id()),
    "topic": b"ING_DATOS",
    "sub_topic": b"SAL_DA",
    "finca": 01, #id_finca
    "equipo": 01, #id_equipo
    "A": -0.0154,
    "B": 1.4424,
    "C": 2.2569,
}
sr=b""
mensaje = ""
espera = False
codigo = ""
contador = 0
if __name__ == '__main__':
    mensaje2 = ["","",""]
    load_config()
    wdt = WDT(timeout=90000)
    try:
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
    time.sleep(1)
    #wdt = WDT(timeout=90000)
    while True:
        print("hola")
        codigo_de_barras()
        if codigo=="16523" or codigo=="17971":
            if pregun() == 1:
                sys.exit()
        codigo = "00," + codigo + ";"
        try:
            disp_pub = client.check_msg()
            client.publish(b'ING_DATOS', codigo.encode())
            time.sleep(.1)
        except:
            print("No Mensaje")
            Reinciar_conexion()
        client.wait_msg()
        mensaje2 = mensaje.replace(";","").split(",")
        if mensaje2 == "NO":
            pass
        else:
            persona = {
              "codigo": codigo, #toca agregarle el codigo que ingresa de la respuesta
              "cedula": mensaje2[2], #toca agregarle la cedula que ingresa de la respuesta
              "Nombre": mensaje2[1],
              "tipo": 01, #toca revisar como se hace eso
              "finca": CONFIG['finca'], #mirar id finca
              "equipo": CONFIG['equipo'], #mirar equipo
            }
            x = read_tem()
            if x == 0:
                contador = contador + 1
            if contador >= 2:
                machine.reset()
            #tem = 1.4424*x-0.0154*x**2+2.2569
            tem = 0.0000583*x**4-0.0081*x**3+0.3929*x**2-7.3155*x+68.59
            """
            crudo = "05," + x + "+" + tem + ";"
            try:
                disp_pub = client.check_msg()
                client.publish(b'ING_DATOS', crudo.encode())
                time.sleep(.1)
            except:
                print("No Mensaje")
                Reinciar_conexion()
            """
            if tem < 29 or tem > 42:
                pass
            else:
                contador = 0
                persona.update({"temperatura": tem})
                time.sleep(1)
                persona.update({"Res1": pregun()})
                persona.update({"Res2": pregun()})
                persona.update({"ingreso": '{}-{}-{} {}:{}:{}'.format(rtc.datetime()[0],rtc.datetime()[1],rtc.datetime()[2],rtc.datetime()[4],rtc.datetime()[5],rtc.datetime()[6])})
                trama = '{},{},{},{},{},{},{},{},{},{};'.format(02,persona["codigo"],persona["cedula"],persona["tipo"],persona["temperatura"],persona["Res1"],persona["Res2"],persona["finca"],persona["equipo"],persona["ingreso"])
                print(trama)
                if pregun() is 0:
                    if persona["Res1"] is 1 or persona["Res2"] is 1 or tem >= 38:
                        time.sleep(3)
                        time.sleep(3)
                    try:
                        disp_pub = client.check_msg()
                        client.publish(b'ING_DATOS', trama.encode())
                        time.sleep(.1)
                    except:
                        print("No Mensaje")
                        Reinciar_conexion()
                    client.wait_msg()
                    print(mensaje)
                    if mensaje is "Exitoso":
                        pass
                    else:
                        pass
        persona.clear()
        print(persona)
        while uart.any() is not 0:
            uart.read(1)
