from sys import stdin, stdout
import xbee
import time

# TODO: replace with the 64-bit address of your target device.
# TARGET_64BIT_ADDR = b'\x00\x13\xA2\xFF\x00\x00\x00\x5D'
MESSAGE = "hola a todos;"
dispositivos = {}
existe = True
def transmision(bl,msj):
    global dispositivos, existe
    if bl is "0":
        try:
            xbee.transmit(xbee.ADDR_BROADCAST, msj)
        except Exception as e:
            pass
    else:
        try:
            xbee.transmit(dispositivos[bl]["addr"], msj)
        except Exception as e:
            if existe:
                existe = False
                descubrir_red()
                transmision(bl,msj)

def descubrir_red():
    global dispositivos
    dispositivos.clear()
    for device in xbee.discover():
        dis = {
            "name": device["node_id"],
            "addr": device["sender_eui64"],
            "rssi": device["rssi"]
        }
        dispositivos[device["node_id"]] = dis

def transmi():
    global read_text,mensaje2, dispositivos,trama_red
    mensaje2 = read_text.decode().split(",")
    if mensaje2[0] is "RED":
        # Discover the network devices and print their basic information.
        descubrir_red()
        trama_red = "RED," + str(len(dispositivos))
        for x in dispositivos:
            trama_red = trama_red + "," + dispositivos[x]["name"] + "," + str(dispositivos[x]["rssi"])
        trama_red = trama_red + ";"
        stdout.buffer.write(trama_red)
    elif mensaje2[0] is "HORA":
        transmision("0",read_text)
    elif mensaje2[0] is "CONF_INVER":
        transmision(mensaje2[1],read_text)

def buscar(read_text):
    sr=b''
    while sr.decode() is not ';':
        sr = stdin.buffer.read(1)
        read_text = read_text + sr
    return read_text

trama_red = None
descubrir_red()
while True:
    # Check if the XBee has any message in the queue.
    received_msg = xbee.receive()
    if received_msg:
        # Get the sender's 64-bit address and payload from the received message.
        sender = received_msg['sender_eui64']
        payload = received_msg['payload']
        stdout.buffer.write(payload)
    time.sleep_ms(50)
    read_text = stdin.buffer.read()
    if read_text is not None:
        try:
            index_final = read_text.decode().index(";")
            transmi()
        except:
            read_text=buscar(read_text)
            transmi()
    time.sleep(0.1)
