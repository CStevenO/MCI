#import webrepl_setup
def do_connect():
    import network
    global wlan
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    ssid = 'Red Wi-Fi de Elite Apple'
    ssidb = str.encode(ssid)
    password = 'Elite2019'
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
import webrepl
webrepl.start()
