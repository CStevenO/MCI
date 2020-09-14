import time
from umqtt.robust import MQTTClient

def sub_cb(topic, msg):
    print((topic, msg))


c = MQTTClient("Prueba_mqtt","10.50.1.153")
c.DEBUG = True
c.set_callback(sub_cb)

time.sleep(3)
if not c.connect(clean_session=False):
    print("New session being set up")
    c.subscribe(b"MCI_ST_OUT")
while 1:
    c.wait_msg()

c.disconnect()
