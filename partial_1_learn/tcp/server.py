import socket
from threading import Thread


def clientCommunication(currentSocket, i):
    print("opened communication to client #" + str(i))
    x = 1
    y = 1
    while True:
        receivedBuffer = currentSocket.recv(1024)
        message = receivedBuffer.decode("utf-8")
        if message == "close":
            print("closing communication with client #" + str(i) + ". bye")
            currentSocket.close()
            break
        else:
            print("client #" + str(i) + " sent message: " + message)
            xCoord = int(message.charAt(0))
            yCoord = int(message.charAt(2))
            print("tried x = " + xCoord + " y = " + yCoord)
            if xCoord == x and yCoord == y:
                print("client #" + str(i) + " won")
                wonMessage = "1\0"
                currentSocket.send(wonMessage.encode())
                print("closing communication with client #" + str(i) + ". bye")
                currentSocket.close()
                break
            else:
                print("client #" + str(i) + " missed")
                wonMessage = "0\0"
                currentSocket.send(wonMessage.encode())


def main():
    soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    soc.bind(("0.0.0.0", 7777))
    soc.listen(5)
    i = 0
    while True:
        i = i + 1
        currentSocket, currentAddress = soc.accept()
        t = Thread(target=clientCommunication, args=(currentSocket, i))
        t.start()


main()
