from jq6500 import Player
from machine import I2C, Pin, UART
import time
import ubinascii
import ntptime
import mlx90614
import machine
import math

player = Player(port=1, volume=30)
uart = UART(2, 115200)

#ntptime.settime()

from machine import RTC
#(year, month, mday, week_of_year, hour, minute, second, milisecond)=RTC().datetime()
#RTC().datetime((year, month, mday, week_of_year, hour-5, minute, second, milisecond))

def conexion():
    try:
        i2c = I2C(scl=Pin(22), sda=Pin(21),freq=50000)
        sensor = mlx90614.MLX90614(i2c)
    except:
        print("conectando...")
        time.sleep(2)
        conexion()

def read_tem():
    try:
        laser.value(1)
        while sensor.read_object_temp() <= 25:
            pass
        time.sleep(0.5)
        prom = 0
        for i in range(40):
            prom = prom + sensor.read_object_temp()
            time.sleep_ms(25)
        prom = prom/40
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
            ver = 0
            return 1
        elif no==0 and si==1:
            #persona.update({respu: 0})
            ver = 0
            return 0
        elif no==0 and si==0:
            #sonar audio 02.mp3  de por favor nada mas si o no
            ver = True
            time.sleep(1)

def codigo_de_barras():
    global codigo
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

def main():
    """
    client = MQTTClient(CONFIG['client_id'], CONFIG['broker'])
    client.connect()
    print("Connected to {}".format(CONFIG['broker']))
    """
    sr=b""
    mensaje = ""
    espera = False
    codigo = ""
    while True:
        codigo_de_barras()
        #client.publish('{},{};'.format(CONFIG['topic'],b"01," + codigo))
        time.sleep(1)
        while espera is not True:
            pass
        espera = False
        #5. Recibe los datos
        #player.play_by_index(2)
        mensaje2 = mensaje.replace(";","").split(",")
        #5.1. Suena audio 00.mp3  audio de bienvenido
        persona = {
          "codigo": codigo, #toca agregarle el codigo que ingresa de la respuesta
          "cedula": mensaje2[2], #toca agregarle la cedula que ingresa de la respuesta
          "Nombre": mensaje2[1],
          "tipo": 01, #toca revisar como se hace eso
          "finca": CONFIG['finca'], #mirar id finca
          "equipo": CONFIG['equipo'], #mirar equipo
        }
        #5.2. Suena audio 01.mp3 audio para pedir la temperatura
        x = read_tem()
        tem = CONFIG["A"]*math.sqrt(x)+CONFIG["B"]*x+CONFIG["C"]
        print(tem) #asignar temperatura del sensor
        persona.update({"temperatura": tem})
        time.sleep(1)
        player.play_by_index(2)
        persona.update({"Res1": pregun()})
        player.play_by_index(1)
        persona.update({"Res2": pregun()})
        player.pause()
        #7. Crea trama para enviar
        persona.update({"ingreso": 12})
        print(persona)
        #persona.update({"ingreso": '{}-{}-{} {}:{}:{}'.format(RTC.datetime()[0],RTC.datetime()[1],RTC.datetime()[2],RTC.datetime()[4],RTC.datetime()[5],RTC.datetime()[6])})
        trama = '{},{},{},{},{},{},{},{},{},{};'.format(02,persona["codigo"],persona["cedula"],persona["tipo"],persona["temperatura"],persona["Res1"],persona["Res2"],persona["finca"],persona["equipo"],persona["ingreso"])
        #8. Envia trama
        print(trama)
        #client.publish('{},{}'.format(CONFIG['topic'],trama))
        while espera is not True:
            pass
        espera = False
        mensaje2 = mensaje.replace(";","").split(",")
        if mensaje2 == "Exitoso":
            player.play_by_index(1) #exitoso
        else:
            player.play_by_index(1) #fallido
        #9. Le dice al usuario que el registro fue exitoso
        #9.1 Suena audio 05.mp3  audio de registro exitoso
        persona.clear()
        print(persona)
        while uart.any() is not 0:
            uart.read(1)

if __name__ == '__main__':
    load_config()
    conexion()
    main()
