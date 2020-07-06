#Librerias
import time
import ubinascii
from mqtt import MQTTClient
from machine import unique_id,Pin
import micropython
import network

#Cada que hay algo nuevo en las suscribciones las muestra aquí
#Nota: decode() y b'' se utiliza para poder convertir un string a byte y vice versa
def form_sub(topic, msg):
    if topic.decode() == "button": #Si el topic button recibe algo entra a las siguientes condiciones para activar / desactivar la salida
    if (msg.decode() == "true"):
        led.on()
    elif (msg.decode() == "false"):
        led.off()
    elif topic.decode() == 'prueba': #Si el topic prueba recibe algo lo muestra
    print ('Recibi el mensaje: ' , msg.decode())
    #print((topic, msg))

#Función que conecta y se suscribe a MQTT
def Conexion_MQTT():
    client_id = b""ubinascii.hexlify(unique_id())
    mqtt_server = 'mantenimiento.elite.local'
    port_mqtt = 1883
    user_mqtt = None #Si su servidor no necesita usuario escribe None sin comillas
    pswd_mqtt = None #Si su servidor no necesita contraseña escribe None sin comillas
    client = MQTTClient(client_id, mqtt_server,port_mqtt,user_mqtt,pswd_mqtt)
    client.set_callback(form_sub)
    client.connect()
    client.subscribe(b'SAL_DA')
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

#Bucle
while True:
    try:
    disp_pub = client.check_msg()

    estado_btn = button.value()
    if disp_pub != 'None':
        if not estado_btn and not candado:
        client.publish(b'ING_DATOS', b'true')
        candado = True
        print (estado_btn)
        elif estado_btn and candado:
        client.publish(b'ING_DATOS', b'false')
        candado = False
        print (estado_btn)
    time.sleep(.1)
    except OSError as e:
    Reinciar_conexion()
