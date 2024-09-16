import socket

class SocketWrapper:
    _socket = None

    @classmethod
    def set_socket(cls, sock):
        cls._socket = sock

    @classmethod
    def get_socket(cls):
        return cls._socket

    @classmethod
    def shutdown_socket(cls):
        if cls._socket:
            cls._socket.shutdown(socket.SHUT_RDWR)
            cls._socket.close()
            cls._socket = None
