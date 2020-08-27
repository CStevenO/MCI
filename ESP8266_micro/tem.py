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



def read_tem():
    try:
        laser.value(1)
        while sensor.read_object_temp() < 21:
            time.sleep(0.5)
        time.sleep(0.5)
        prom = 0
        prom2 = 0
        nor=0
        for i in range(20):
            amb = sensor.read_ambient_temp()
            obj =  sensor.read_object_temp()
            prom2 = prom2 + amb
            prom = prom + obj + 29 - amb
            nor= nor + obj
            time.sleep_ms(50)
        prom = prom/20
        prom2 = prom2/20
        nor=nor/20
        print(prom2)
        print(nor)
        laser.value(0)
        return prom
    except:
        print("Error")
        return 0

try:
    i2c = I2C(scl=Pin(22), sda=Pin(21),freq=100000)
    sensor = mlx90614.MLX90614(i2c)
except:
    print("conectando...")
    sensor = mlx90614.MLX90614(i2c)
while True:
    x = read_tem()
    print("medida mejorada: ", 0.0631*x**3-5.9572*x**2+187.43*x-1929.4)
    print("medida cruda: ", x+4)
    #print(sensor.read_object_temp()*0.535+12)
    time.sleep(1)
