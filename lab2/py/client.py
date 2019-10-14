import socket
s=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
s.sendto("hey",("172.30.114.164",5555))
print s.recvfrom(10)
