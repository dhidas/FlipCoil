#!/usr/bin/python

import socket
import time
import sys

cs = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

if len(sys.argv) == 1:
    cs.connect( ('192.6.94.120', 4001) )
elif len(sys.argv) == 3:
    cs.connect( (sys.argv[1], sys.argv[2]) )
else:
    raise ValueError('something is wrong with the input')


def getdata (out):
    out += '\r\n'
    cs.send(out.encode())
    sin = ''
    data = cs.recv(512)
    while data.decode() != '\r\n':
        sin += data.decode()
        data = cs.recv(512)
    return sin
    
#print( getdata('*IDN?') )
print( getdata('FETCH?') )


#####s = '*IDN?'.encode()
#####print(s)
####cs.send( '*IDN?\r\n'.encode() )
####data = cs.recv(512)
####print(data)
####data = cs.recv(512)
####print(data)
####
####
####cs.send( 'fetch?\r\n'.encode() )
####data = cs.recv(128)
####print(data)
####while data.decode() != '\r\n':
####    data = cs.recv(128)
####    print(data.decode())
