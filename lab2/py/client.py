import socket
s=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
s.sendto("dani ia bani",("192.168.100.13",5555))
# print(s.recvfrom(10))
