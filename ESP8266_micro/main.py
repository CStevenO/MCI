from jq6500 import Player
from machine import I2C, Pin, UART, unique_id
from mqtt import MQTTClient
import micropython
import time
import ubinascii
import mlx90614
import machine
import math

player = Player(port=1, volume=30)
uart = UART(2, 115200)


from machine import RTC
rtc = RTC()


def Conexion_MQTT():
    client_id = b"Covid_" + ubinascii.hexlify(unique_id())
    #client_id = b"covid"
    mqtt_server = '10.50.1.153'
    port_mqtt = 1883
    user_mqtt = None #Si su servidor no necesita usuario escribe None sin comillas
    pswd_mqtt = None #Si su servidor no necesita contraseña escribe None sin comillas
    client = MQTTClient(client_id, mqtt_server,port_mqtt,user_mqtt,pswd_mqtt)
    client.set_callback(form_sub)
    client.connect()
    client.subscribe(b'HORA')
    client.subscribe(b'SAL_DA')
    print('Conectado a %s' % mqtt_server)
    return client

def Reinciar_conexion():
    print('Fallo en la conexion. Intentando de nuevo...')
    time.sleep(3)
    machine.reset()

def read_tem():
    try:
        laser.value(1)
        start = time.ticks_ms()
        while sensor.read_object_temp() <= 30:
            time.sleep(0.5)
            delta = time.ticks_diff(time.ticks_ms(), start)
            if delta >= 5000:
                return 1
        time.sleep(0.5)
        prom = 0
        for i in range(20):
            prom = prom + sensor.read_object_temp()
            time.sleep_ms(50)
        prom = prom/20
        laser.value(0)
        return prom
    except:
        print("Error")
        return 0

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

def pregun():
    global persona
    ver = True
    while ver:
        si = ressi.value()
        no = resno.value()
        while si == 1 and no == 1:
            si = ressi.value()
            no = resno.value()
        time.sleep_ms(750)
        while ressi.value()==0 or resno.value()==0:
            time.sleep_ms(750)
        if si==0 and no==1:
            #persona.update({respu: 1})
            player.play_by_index(13)
            ver = 0
            return 1
        elif no==0 and si==1:
            player.play_by_index(12)
            #persona.update({respu: 0})
            ver = 0
            return 0
        elif no==0 and si==0:
            #sonar audio 02.mp3  de por favor nada mas si o no
            player.play_by_index(16)
            ver = True
            time.sleep(1)

def codigo_de_barras():
    global codigo , sr
    while True:
        while uart.any() is 0:
            pass
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

ressi = Pin(27, Pin.IN, Pin.PULL_UP)
resno = Pin(26, Pin.IN, Pin.PULL_UP)
laser = Pin(25, Pin.OUT)
alarma = Pin(14, Pin.OUT)
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
    try:
        i2c = I2C(scl=Pin(22), sda=Pin(21),freq=50000)
        sensor = mlx90614.MLX90614(i2c)
    except:
        print("conectando...")
        sensor = mlx90614.MLX90614(i2c)
    try:
        client = Conexion_MQTT()
    except OSError as e:
        Reinciar_conexion()
    except:
        Reinciar_conexion()
    try:
        disp_pub = client.check_msg()
        client.publish(b'ING_DATOS', b'00,16523')
    except OSError as e:
        Reinciar_conexion()
    client.wait_msg()
    try:
        print(mensaje2[1])
    except:
        time.sleep(2)
        mensaje2 = mensaje.replace(";","").split(",")
        print(mensaje2[1])
    time.sleep(2)
    player.play_by_index(10)
    while True:
        print("hola")
        codigo_de_barras()
        codigo = "00," + codigo + ";"
        try:
            disp_pub = client.check_msg()
            client.publish(b'ING_DATOS', codigo.encode())
            time.sleep(.1)
        except OSError as e:
            Reinciar_conexion()
        client.wait_msg()
        mensaje2 = mensaje.replace(";","").split(",")
        persona = {
          "codigo": codigo, #toca agregarle el codigo que ingresa de la respuesta
          "cedula": mensaje2[2], #toca agregarle la cedula que ingresa de la respuesta
          "Nombre": mensaje2[1],
          "tipo": 01, #toca revisar como se hace eso
          "finca": CONFIG['finca'], #mirar id finca
          "equipo": CONFIG['equipo'], #mirar equipo
        }
        player.play_by_index(19)
        x = read_tem()
        if x = 0:
            contador = contador + 1
        if contador >= 2:
            player.play_by_index(14)
            machine.reset()
        tem = 1.4424*x-0.0154*x**2+2.2569
        if tem < 30:
            player.play_by_index(14)
        else:
            contador = 0
            persona.update({"temperatura": tem})
            time.sleep(1)
            player.play_by_index(18)
            persona.update({"Res1": pregun()})
            player.play_by_index(17)
            persona.update({"Res2": pregun()})
            persona.update({"ingreso": '{}-{}-{} {}:{}:{}'.format(rtc.datetime()[0],rtc.datetime()[1],rtc.datetime()[2],rtc.datetime()[4],rtc.datetime()[5],rtc.datetime()[6])})
            trama = '{},{},{},{},{},{},{},{},{},{};'.format(02,persona["codigo"],persona["cedula"],persona["tipo"],persona["temperatura"],persona["Res1"],persona["Res2"],persona["finca"],persona["equipo"],persona["ingreso"])
            print(trama)
            player.play_by_index(11)
            if pregun() is 0:
                if persona["Res1"] is 1 or persona["Res2"] is 1 or tem >= 38:
                    player.play_by_index(20)
                    time.sleep(1)
                    player.play_by_index(21)
                    time.sleep(3)
                try:
                    disp_pub = client.check_msg()
                    client.publish(b'ING_DATOS', trama.encode())
                    time.sleep(.1)
                except OSError as e:
                    Reinciar_conexion()
                client.wait_msg()
                print(mensaje)
                if mensaje is "Exitoso":
                    player.play_by_index(15) #exitoso
                else:
                    player.play_by_index(14) #fallido
        persona.clear()
        print(persona)
        while uart.any() is not 0:
            uart.read(1)
