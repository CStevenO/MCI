import machine
import time
import ubinascii
import webrepl
import ntptime
from jq6500 import Player
import mlx90614
from machine import I2C, Pin

i2c = I2C(scl=Pin(22), sda=Pin(21))
sensor = mlx90614.MLX90614(i2c)


player = Player(port=1)
player.set_volume(20)
player.play_by_index(1)

ressi = Pin(15, Pin.IN, Pin.PULL_UP)
resno = Pin(16, Pin.IN, Pin.PULL_UP)
p1 = Pin(0, Pin.IN, Pin.PULL_UP)
"""
from umqtt.simple import MQTTClient
"""
time.sleep(5)
"""
ntptime.settime()

from machine import RTC
(year, month, mday, week_of_year, hour, minute, second, milisecond)=RTC().datetime()
RTC().datetime((year, month, mday, week_of_year, hour-5, minute, second, milisecond))

print ("Fecha: {:02d}/{:02d}/{}".format(RTC().datetime()[2],
                                        RTC().datetime()[1],
                                        RTC().datetime()[0]))

print ("Hora: {:02d}:{:02d}:{:02d}".format(RTC().datetime()[4],
                                           RTC().datetime()[5],
                                           RTC().datetime()[6]))

player.play_by_index(1)
time.sleep(5)
player.play_by_index(2)

"""
# These defaults are overwritten with the contents of /config.json by load_config()
CONFIG = {
    "broker": "mantenimiento.elite.local",
    "client_id": b"esp8266_" + ubinascii.hexlify(machine.unique_id()),
    "topic": b"ING_DATOS",
    "sub_topic": b"SAL_DA",
    "finca": 01, #id_finca
    "equipo": 01, #id_equipo
}

client = None

def read_tem():
    while sensor.read_ambient_temp()*1.2 < sensor.read_object_temp():
        pass
    prom = 0
    for i in range(20):
        prom = prom + sensor.read_object_temp()
    prom = prom/20
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

def main():
    """
    client = MQTTClient(CONFIG['client_id'], CONFIG['broker'])
    client.connect()
    print("Connected to {}".format(CONFIG['broker']))
    """
    while True:
        #1. espera hasta que el lector de codigo de barras lea un codigo
        #2. procesa el codigo
        while p1.value() == False:
            pass
        barcode = 123
        #3. Realiza la consulta a la base de datos
        #client.publish('{},{};'.format(CONFIG['topic'],barcode))
        #4. Espera confirmacion
        #5. Recibe los datos
        #5.1. Suena audio 00.mp3  audio de bienvenido
        persona = {
          "codigo": 16523, #toca agregarle el codigo que ingresa de la respuesta
          "cedula": 1026591258, #toca agregarle la cedula que ingresa de la respuesta
          "tipo": 01, #toca revisar como se hace eso
          "finca": CONFIG['finca'], #mirar id finca
          "equipo": CONFIG['equipo'], #mirar equipo
        }
        #5.2. Suena audio 01.mp3 audio para pedir la temperatura
        tem = read_tem() #asignar temperatura del sensor
        persona.update({"temperatura": tem})
        #6. Realiza las preguntas
        #6.1. Suena audio 03.mp3  audio de primera pregunta
        player.pause()
        player.play_by_index(2)
        time.sleep(3)
        #6.2. Registra respuesta
        ver = True
        while ver:
            while ressi.value() == False and resno.value() == False:
                pass
            si = ressi.value()
            no = resno.value()
            if si and no==False:
                persona.update({"Res1": 1})
                ver = False
            elif no and si==False:
                persona.update({"Res1": 0})
                ver = False
            elif no and si:
                #sonar audio 02.mp3  de por favor nada mas si o no
                ver = True
                time.sleep(1)
            while ressi.value() or resno.value():
                pass
        #6.3. Suena audio 04.mp3  audio de segunda pregunta
        player.pause()
        player.play_by_index(1)
        time.sleep(3)
        #6.4. Registra respuesta
        ver = True
        while ver:
            while ressi.value() == False and resno.value() == False:
                pass
            si = ressi.value()
            no = resno.value()
            if si and no==False:
                persona.update({"Res2": 1})
                ver = False
            elif no and si==False:
                persona.update({"Res2": 0})
                ver = False
            elif no and si:
                #sonar audio 02.mp3  de por favor nada mas si o no
                ver = True
                time.sleep(1)
            while ressi.value() or resno.value():
                pass
        #7. Crea trama para enviar
        persona.update({"ingreso": 12})
        #persona.update({"ingreso": '{}-{}-{} {}:{}:{}'.format(RTC.datetime()[0],RTC.datetime()[1],RTC.datetime()[2],RTC.datetime()[4],RTC.datetime()[5],RTC.datetime()[6]))
        trama = '{},{},{},{},{},{},{},{},{},{};'.format(02,persona["codigo"],persona["cedula"],persona["tipo"],persona["temperatura"],persona["Res1"],persona["Res2"],persona["finca"],persona["equipo"],persona["ingreso"])
        #8. Envia trama
        print(trama)
        #client.publish('{},{}'.format(CONFIG['topic'],trama))
        #9. Le dice al usuario que el registro fue exitoso
        #9.1 Suena audio 05.mp3  audio de registro exitoso
        persona.clear()
        #data = sensor_pin.read()
        #client.publish('{}/{}'.format(CONFIG['topic'],
        #                                  CONFIG['client_id']),
        #                                  bytes(str(data), 'utf-8'))
        #print('Sensor state: {}'.format(data))
        #time.sleep(5)

if __name__ == '__main__':
    load_config()
    main()
