import json
import os
from src.broadcast.encryption.derive_key import derive_key
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import padding
import base64


# def encrypt_data(data: dict, teamname: str) -> str:
#     json_data = json.dumps(data).encode()
#     salt = os.urandom(16)
#     key = derive_key(teamname, salt)
#     iv = os.urandom(16)
#     cipher = Cipher(algorithms.AES(key), modes.CBC(iv), backend=default_backend())
#     encryptor = cipher.encryptor()
#     padder = padding.PKCS7(algorithms.AES.block_size).padder()
#     padded_data = padder.update(json_data) + padder.finalize()
#     encrypted_data = encryptor.update(padded_data) + encryptor.finalize()
#     encrypted_message = salt + iv + encrypted_data
#     encoded_message = base64.b64encode(encrypted_message).decode()
#     return encoded_message


def encrypt_data(data: dict, teamname: str) -> str:
    return base64.b64encode((salt := os.urandom(16)) + (iv := os.urandom(16)) + ((encryptor := Cipher(algorithms.AES(derive_key(teamname, salt)), modes.CBC(iv), backend=default_backend()).encryptor()).update((padder := padding.PKCS7(algorithms.AES.block_size).padder()).update(json.dumps(data).encode()) + padder.finalize()) + encryptor.finalize())).decode()
