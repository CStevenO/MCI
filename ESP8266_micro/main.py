from jq6500 import Player
from machine import I2C, Pin, UART
import time
import ubinascii
import ntptime
import mlx90614
import machine

player = Player(port=1, volume=30)
try:
    conexion()
except:
    time.sleep(2)
    conexion()

uart = UART(2, 115200)

#ntptime.settime()

from machine import RTC
#(year, month, mday, week_of_year, hour, minute, second, milisecond)=RTC().datetime()
#RTC().datetime((year, month, mday, week_of_year, hour-5, minute, second, milisecond))

def conexion():
    i2c = I2C(scl=Pin(22), sda=Pin(21), freq=100000)
    sensor = mlx90614.MLX90614(i2c)

def read_tem():
    laser.value(1)
    while (sensor.read_object_temp() <= 34:
        pass
    prom = 0
    for i in range(40):
        prom = prom + sensor.read_object_temp()
        time.sleep_ms(25)
    prom = prom/40
    laser.value(0)
    return prom

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
}
persona = {
  "codigo": 16523, #toca agregarle el codigo que ingresa de la respuesta
  "cedula": 1026591258, #toca agregarle la cedula que ingresa de la respuesta
  "tipo": 01, #toca revisar como se hace eso
  "finca": CONFIG["finca"], #mirar id finca
  "equipo": CONFIG["equipo"], #mirar equipo
}

def main():
    """
    client = MQTTClient(CONFIG['client_id'], CONFIG['broker'])
    client.connect()
    print("Connected to {}".format(CONFIG['broker']))
    """
    sr=b""
    while True:
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
        #client.publish('{},{};'.format(CONFIG['topic'],codigo))
        #4. Espera confirmacion
        #5. Recibe los datos
        #5.1. Suena audio 00.mp3  audio de bienvenido
        persona = {
          "codigo": codigo, #toca agregarle el codigo que ingresa de la respuesta
          "cedula": 1026591258, #toca agregarle la cedula que ingresa de la respuesta
          "tipo": 01, #toca revisar como se hace eso
          "finca": CONFIG['finca'], #mirar id finca
          "equipo": CONFIG['equipo'], #mirar equipo
        }
        #5.2. Suena audio 01.mp3 audio para pedir la temperatura
        tem = read_tem()
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
        #9. Le dice al usuario que el registro fue exitoso
        #9.1 Suena audio 05.mp3  audio de registro exitoso
        persona.clear()
        print(persona)
        while uart.any() is not 0:
            uart.read(1)

if __name__ == '__main__':
    load_config()
    main()
