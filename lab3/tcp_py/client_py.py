import socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("192.168.100.13", 7777))
s.send("Salut")
# print s.recv(10)
s.close()
