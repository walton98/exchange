import socket

from meng_pb2 import Book

MCAST_GRP = '224.1.1.1'
MCAST_PORT = 30001
# allow upto two hops
MULTICAST_TTL = 2

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, MULTICAST_TTL)

book = Book()
book.id = 69
msg = book.SerializeToString()
sock.sendto(msg, (MCAST_GRP, MCAST_PORT))
print(f"Sent: {msg}")