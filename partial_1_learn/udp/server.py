import socket


soc = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
soc.bind(("0.0.0.0", 5555))

while True:
    buff, addr = soc.recvfrom(100)
    message = buff.decode("utf-8")
    if message == "close":
        print("closing server")
        break
    print("server received: " + message)
    messageToSend = message + " beautified\0"
    soc.sendto(messageToSend.encode(), addr)
