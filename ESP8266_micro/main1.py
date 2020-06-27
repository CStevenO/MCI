from jq6500 import Player
from machine import I2C, Pin
import time

player = Player(port=1, volume=30)


ressi = Pin(27, Pin.IN)
resno = Pin(26, Pin.IN)
persona = {
  "codigo": 16523, #toca agregarle el codigo que ingresa de la respuesta
  "cedula": 1026591258, #toca agregarle la cedula que ingresa de la respuesta
  "tipo": 01, #toca revisar como se hace eso
  "finca": 01, #mirar id finca
  "equipo": 01, #mirar equipo
}

time.sleep(3)
ver = True
print('audio2')
player.play_by_index(2)
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
        persona.update({"Res1": 1})
        ver = 0
    elif no==0 and si==1:
        persona.update({"Res1": 0})
        ver = 0
    elif no==0 and si==0:
        #sonar audio 02.mp3  de por favor nada mas si o no
        ver = True
        time.sleep(1)
ver = True
print('audio2')
player.play_by_index(1)
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
        persona.update({"Res2": 1})
        ver = 0
    elif no==0 and si==1:
        persona.update({"Res2": 0})
        ver = 0
    elif no==0 and si==0:
        #sonar audio 02.mp3  de por favor nada mas si o no
        ver = True
        time.sleep(1)
print(persona)
