# import struct
import socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind(("0.0.0.0", 7778))
sock.listen(5)
connection, address = sock.accept()
message = ''
while True:
    message = connection.recv(1024)
    print(message)
    if "close" in message:
        break
    connection.send("message received")
# connection.send(len(receivedMessageFromClient))
# connection.send(struct.pack('<I', len(receivedMessageFromClient)))
# connection.send(struct.pack('<I', 10))
# connection.send("message from server")
connection.close()
sock.close()
