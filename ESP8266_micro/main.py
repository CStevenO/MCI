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
    print('Topic: ', topic.decode())
    print('Recibi el mensaje: ' , msg.decode())
    #print((topic, msg))

#Función que conecta y se suscribe a MQTT
def Conexion_MQTT():
    #client_id = b"Covid_" + ubinascii.hexlify(unique_id())
    client_id = b"covid"
    mqtt_server = 'node02.myqtthub.com'
    port_mqtt = 1883
    user_mqtt = None #Si su servidor no necesita usuario escribe None sin comillas
    pswd_mqtt = None #Si su servidor no necesita contraseña escribe None sin comillas
    client = MQTTClient(client_id, mqtt_server,port_mqtt,user_mqtt,pswd_mqtt)
    client.set_callback(form_sub)
    client.connect()
    client.subscribe(b'hub-CStevenO1997')
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

#Bucle
while True:
    try:
        disp_pub = client.check_msg()
        client.publish(b'hub-CStevenO1997', b'true')
        time.sleep(.1)
    except OSError as e:
        Reinciar_conexion()
