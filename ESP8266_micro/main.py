from jq6500 import Player
from machine import I2C, Pin, UART
import time
import ubinascii
import ntptime
import mlx90614

player = Player(port=1, volume=30)
i2c = I2C(scl=Pin(22), sda=Pin(21))
sensor = mlx90614.MLX90614(i2c)
uart = UART(2, 115200)
sr=b""

def read_tem():
    laser.value(1)
    while sensor.read_object_temp() < 34:
        pass
    prom = 0
    for i in range(20):
        prom = prom + sensor.read_object_temp()
        time.sleep_ms(50)
    prom = prom/20
    return prom
    laser.value(0)

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

def pregun(respu):
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
            persona.update({respu: 1})
            ver = 0
        elif no==0 and si==1:
            persona.update({respu: 0})
            ver = 0
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
    while True:
        data = uart.read(1)
        while data is None:
            data = uart.read(1)
        while data is not b"\r":
            sr=sr+data
            data = uart.read(1)
        codigo=sr.decode("utf-8")[0:len(b)-3]
        sr=b""
        #client.publish('{},{};'.format(CONFIG['topic'],codigo))
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
        time.sleep(3)
        player.play_by_index(2)
        pregun("Res1")
        player.play_by_index(1)
        pregun("Res2")
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
        print(persona)

if __name__ == '__main__':
    load_config()
    main()
