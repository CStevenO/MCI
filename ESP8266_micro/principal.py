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

def conexion():
    try:
        i2c = I2C(scl=Pin(22), sda=Pin(21),freq=50000)
        sensor = mlx90614.MLX90614(i2c)
    except:
        print("conectando...")
        time.sleep(2)
        conexion()

def Conexion_MQTT():
    client_id = b"Covid_" + ubinascii.hexlify(unique_id())
    #client_id = b"covid"
    mqtt_server = 'mantenimiento.elite.local'
    port_mqtt = 1883
    user_mqtt = None #Si su servidor no necesita usuario escribe None sin comillas
    pswd_mqtt = None #Si su servidor no necesita contraseña escribe None sin comillas
    client = MQTTClient(client_id, mqtt_server,port_mqtt,user_mqtt,pswd_mqtt)
    client.set_callback(form_sub)
    client.connect()
    client.subscribe(b'SAL_DA')
    client.subscribe(b'HORA')
    print('Conectado a %s' % mqtt_server)
    return client

def Reinciar_conexion():
    print('Fallo en la conexion. Intentando de nuevo...')
    time.sleep(10)
    machine.reset()


def read_tem():
    try:
        laser.value(1)
        while sensor.read_object_temp() <= 25:
            pass
        time.sleep(0.5)
        prom = 0
        for i in range(30):
            prom = prom + sensor.read_object_temp()
            time.sleep_ms(30)
        prom = prom/30
        laser.value(0)
        return prom
    except:
        print("Error")
        read_tem()

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
        rtc.datetime((dat[0],dat[1],dat[2],0,dat[3],dat[4],dat[5]))
        print(rtc.datetime())
    elif topic.decode() is "SAL_DA":
        espera = True

ressi = Pin(27, Pin.IN, Pin.PULL_UP)
resno = Pin(26, Pin.IN, Pin.PULL_UP)
laser = Pin(25, Pin.OUT)
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
def main():
    """
    client = MQTTClient(CONFIG['client_id'], CONFIG['broker'])
    client.connect()
    print("Connected to {}".format(CONFIG['broker']))
    """
    global sr,mensaje,espera,codigo
    try:
        client = Conexion_MQTT()
    except OSError as e:
        Reinciar_conexion()
    except:
        Reinciar_conexion()
    player.play_by_index(10)
    while True:
        print("hola")
        codigo_de_barras()
        #client.publish('{},{};'.format(CONFIG['topic'],b"01," + codigo))
        codigo = "00," + codigo + ";"
        try:
            disp_pub = client.check_msg()
            client.publish(b'ING_DATOS', codigo.encode())
            time.sleep(.1)
        except OSError as e:
            Reinciar_conexion()
        time.sleep(1)
        while espera is not True:
            pass
        espera = False
        #5. Recibe los datos
        mensaje2 = mensaje.replace(";","").split(",")
        #5.1. Suena audio 00.mp3  audio de bienvenido
        persona = {
          "codigo": codigo, #toca agregarle el codigo que ingresa de la respuesta
          #"cedula": 12312412,
          "cedula": mensaje2[2], #toca agregarle la cedula que ingresa de la respuesta
          "Nombre": mensaje2[1],
          "tipo": 01, #toca revisar como se hace eso
          "finca": CONFIG['finca'], #mirar id finca
          "equipo": CONFIG['equipo'], #mirar equipo
        }
        #5.2. Suena audio 01.mp3 audio para pedir la temperatura
        player.play_by_index(19)
        x = read_tem()
        #print(x)
        tem = CONFIG["A"]*x*x+CONFIG["B"]*x+CONFIG["C"]
        #print(tem) #asignar temperatura del sensor
        persona.update({"temperatura": tem})
        time.sleep(1)
        player.play_by_index(18)
        persona.update({"Res1": pregun()})
        player.play_by_index(17)
        persona.update({"Res2": pregun()})
        #player.pause()
        #7. Crea trama para enviar
        #persona.update({"ingreso": 12})
        persona.update({"ingreso": '{}-{}-{} {}:{}:{}'.format(rtc.datetime()[0],rtc.datetime()[1],rtc.datetime()[2],rtc.datetime()[4],rtc.datetime()[5],rtc.datetime()[6])})
        trama = '{},{},{},{},{},{},{},{},{},{};'.format(02,persona["codigo"],persona["cedula"],persona["tipo"],persona["temperatura"],persona["Res1"],persona["Res2"],persona["finca"],persona["equipo"],persona["ingreso"])
        #8. Envia trama
        print(trama)
        try:
            disp_pub = client.check_msg()
            client.publish(b'ING_DATOS', trama.encode())
            time.sleep(.1)
        except OSError as e:
            Reinciar_conexion()
        #client.publish('{},{}'.format(CONFIG['topic'],trama))
        while espera is not True:
            pass
        espera = False
        mensaje2 = mensaje.replace(";","").split(",")
        if mensaje2 == "Exitoso":
            player.play_by_index(15) #exitoso
        else:
            player.play_by_index(14) #fallido
        #9. Le dice al usuario que el registro fue exitoso
        #9.1 Suena audio 05.mp3  audio de registro exitoso
        persona.clear()
        print(persona)
        while uart.any() is not 0:
            uart.read(1)

if __name__ == '__main__':
    save_config()
    load_config()
    conexion()
    main()
