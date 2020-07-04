import mlx90614
from machine import I2C, Pin
import time
from machine import UART
import ubinascii
"""
uart = UART(2, 115200)
sr=b""
while True:
    while True:
        while uart.any() is 0:
            pass
        data = uart.read(1)
        if data==b"\r":
            codigo=sr.decode("utf-8")[0:len(sr)-3]
            print(codigo)
            sr=b""
            break
        elif data is not None:
            sr=sr+data
"""
laser = Pin(25, Pin.OUT)

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

conexion()
while True:
    x = read_tem()
    print("medida mejorada: ", 1.4424*x-0.0154*x*x+2.2569)
    print("medida cruda: ", x)
    #print(sensor.read_object_temp()*0.535+12)
    time.sleep(1)
