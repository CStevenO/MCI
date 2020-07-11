#Librerias
import time
import ubinascii
import machine
from mqtt import MQTTClient
from machine import unique_id,Pin
import micropython
import network

#Cada que hay algo nuevo en las suscribciones las muestra aquí
#Nota: decode() y b'' se utiliza para poder convertir un string a byte y vice versa
def form_sub(topic, msg):
    global mensaje, espera, rtc
    mensaje = msg.decode()
    if topic.decode() is "HORA":
        dat = mensaje.replace(";","").split(",")
        rtc.datetime((dat[0],dat[1],dat[2],0,dat[3],dat[4],dat[5]))
        print(rtc.datetime())
    elif topic.decode() is "SAL_DA":
        espera = True

#Función que conecta y se suscribe a MQTT
def Conexion_MQTT():
    #client_id = b"Covid_" + ubinascii.hexlify(unique_id())
    client_id = b"covid"
    mqtt_server = '10.50.1.153'
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

#Reinicia la conexión de MQTT
def Reinciar_conexion():
    print('Fallo en la conexion. Intentando de nuevo...')
    time.sleep(10)
    machine.reset()

#Se coloca la conexión dentro de un Try por si hay errores en la misma
try:
    client = Conexion_MQTT()
except OSError as e:
    Reinciar_conexion()
except:
    Reinciar_conexion()
sr=b""
mensaje = ""
espera = False
codigo = ""

#Bucle

if __name__ == '__main__':
    mensaje2 = ["","",""]
    while True:
        try:
            disp_pub = client.check_msg()
            client.publish(b'ING_DATOS', b'00,16523;')
        except OSError as e:
            Reinciar_conexion()
        time.sleep(1)
        mensaje2 = mensaje.replace(";","").split(",")
        try:
            print(mensaje2[1])
        except:
            time.sleep(2)
            mensaje2 = mensaje.replace(";","").split(",")
            print(mensaje2[1])
