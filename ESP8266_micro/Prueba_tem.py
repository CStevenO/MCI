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
def conexion():
    i2c = I2C(scl=Pin(22), sda=Pin(21),freq=50000)
    sensor = mlx90614.MLX90614(i2c)

try:
    conexion()
except:
    print("conectando...")
    time.sleep(2)
    conexion()

while True:
    print(sensor.read_object_temp()*0.535+12)
    time.sleep_ms(50)
