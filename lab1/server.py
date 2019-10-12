import socket
s=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)  
s.bind(("127.0.0.1",9998))                           
while True:
	buff,addr=s.recvfrom(10)                           
	print buff
