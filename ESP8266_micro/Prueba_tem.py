import mlx90614
from machine import I2C, Pin
import time
from machine import UART
import ubinascii

uart = UART(2, 115200)
sr=b""
while True:
    data = uart.read(1)
    while data is None:
        data = uart.read(1)
    if data==b"\r":
        print(sr.decode("utf-8"))
        sr=b""
    elif data is not None:
        sr=sr+data

"""
i2c = I2C(scl=Pin(22), sda=Pin(21), freq=100000)
sensor = mlx90614.MLX90614(i2c)

def read_tem():
    print("Esperando...")
    while sensor.read_object_temp() < 35:
        pass
    prom = 0
    for i in range(20):
        arr.append(sensor.read_object_temp())
        #prom = prom + sensor.read_object_temp()
        time.sleep_ms(50)
    #prom = prom/20
    #return prom

arr = []

read_tem()
print(arr)
"""
