import socket
import time

UDP_IP = "192.168.0.28"
UDP_PORT = 4210
START = 'a'
STOP = 'b'
SPEED_UP = 'c'
SPEED_DOWN = 'd'
EMERGENCY = 'e'

print ("UDP target IP:", UDP_IP)
print ("UDP target port:", UDP_PORT)
print ("message:", START)
sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
sock.sendto(START.encode(), (UDP_IP, UDP_PORT))
time.sleep(3)

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.sendto(STOP.encode(), (UDP_IP, UDP_PORT))

