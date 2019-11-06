import socket
from threading import Thread


def currentSocketExecutor(currentSocket, i):
    print("client #" + str(i) + " connected to server")
    while True:
        buffer = currentSocket.recv(1024)
        message = buffer.decode("utf-8")
        if message == "close":
            print("closing connection with client #" + str(i))
            currentSocket.close()
            break
        else:
            print("received message: " + message + "from client #" + str(i))
            message = message + "!\0"
            currentSocket.send(message.encode())


def main():
    soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    soc.bind(("0.0.0.0", 7777))
    soc.listen(5)
    i = 0
    while True:
        i = i + 1
        currentSocket, address = soc.accept()
        thread = Thread(target=currentSocketExecutor, args=(currentSocket, i,))
        thread.start()


main()
