from sys import stdin, stdout
import xbee
import time

# TODO: replace with the 64-bit address of your target device.
# TARGET_64BIT_ADDR = b'\x00\x13\xA2\xFF\x00\x00\x00\x5D'
MESSAGE = "hola a todos;"

def buscar(read_text):
    sr=b''
    while sr.decode() is not ';':
        sr = stdin.buffer.read(1)
        read_text = read_text + sr
    return read_text

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
        except:
            read_text = buscar(read_text)
        try:
            xbee.transmit(xbee.ADDR_COORDINATOR, read_text)
        except Exception as e:
            pass
    time.sleep(0.1)
