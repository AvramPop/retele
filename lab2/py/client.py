import socket
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.sendto("linux client py writing", ("192.168.100.40", 5555))
# print(s.recvfrom(10))
