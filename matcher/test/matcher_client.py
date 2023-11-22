import socket

from matcher_pb2 import Action


class MatcherClient:
    def __init__(self, mcast_grp: str, mcast_port: int, ttl: int) -> None:
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
        sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, ttl)
        self._sock = sock
        self._mcast_grp = mcast_grp
        self._mcast_port = mcast_port

    def send_request(self, action: Action) -> None:
        msg = action.SerializeToString()
        self._sock.sendto(msg, (self._mcast_grp, self._mcast_port))