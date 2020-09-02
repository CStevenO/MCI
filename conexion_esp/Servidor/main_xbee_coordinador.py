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


def uart_lectura():
    global read2,read_text,index
    read2 = stdin.read(-1)
    while read2 is not None:
        read_text = read_text + read2
        read2 = stdin.read(-1)
    try:
        index = read_text.index("\n")
        read_text = read_text[0:index]
    except Exception as e:
        pass

def intentos():
    global read_text,index_final
    uart_lectura()
    try:
        index_final = read_text.index(";")
        transmi()
    except:
        intentos()

def descubrir_red():
    global dispositivos
    for device in xbee.discover():
        dis = {
            "addr": device["sender_eui64"],
            "rssi": device["rssi"]
        }
        dispositivos[device["node_id"]] = dis

def transmi():
    global read_text,mensaje2, dispositivos
    mensaje2 = read_text.split(",")
    if mensaje2[0] is "RED":
        # Discover the network devices and print their basic information.
        descubrir_red()
        print(dispositivos)
    elif mensaje2[0] is "HORA":
        transmision("0",read_text)
    elif mensaje2[0] is "CONF_INVER":
        transmision(mensaje2[1],read_text)

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
    read_text = stdin.read(-1)
    if read_text:
        intentos()
    time.sleep(0.1)
