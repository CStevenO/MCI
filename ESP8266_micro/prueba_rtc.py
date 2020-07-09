import ntptime
ntptime.settime()
def do_connect():
    import network
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    ssid = 'Steven'
    ssidb = str.encode(ssid)
    password = '1026591258'
    pos = -1
    if not wlan.isconnected():
        while pos == -1:
            redes = wlan.scan()
            for i in range(len(redes)):
                if redes[i][0]==ssidb:
                    pos = i
                    break
            if pos == -1:
                print('Red no encontrada')
            else:
                print('Señal', redes[pos][3])
        print('connecting to network...')
        wlan.connect(ssid,password)
        while not wlan.isconnected():
            pass
    print('network config:', wlan.ifconfig())
do_connect()

from machine import RTC
(year, month, mday, week_of_year, hour, minute, second, milisecond)=RTC().datetime()
RTC().datetime((year, month, mday, week_of_year, hour-5, minute, second, milisecond))

persona = {
      "codigo": codigo, #toca agregarle el codigo que ingresa de la respuesta
      "cedula": mensaje2[2], #toca agregarle la cedula que ingresa de la respuesta
      "Nombre": mensaje2[1],
      "tipo": 01, #toca revisar como se hace eso
      "finca": CONFIG['finca'], #mirar id finca
      "equipo": CONFIG['equipo'], #mirar equipo
}
persona.update({"ingreso": '{}-{}-{} {}:{}:{}'.format(RTC.datetime()[0],RTC.datetime()[1],RTC.datetime()[2],RTC.datetime()[4],RTC.datetime()[5],RTC.datetime()[6])})
print(persona)
