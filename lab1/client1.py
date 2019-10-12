import socket
s=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)  
s.sendto("dani pop",("127.0.0.1",9998))                 
print s.recvfrom(10) 
