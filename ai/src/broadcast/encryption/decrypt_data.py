import json
from src.broadcast.encryption.derive_key import derive_key
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import padding
import base64


# def decrypt_data(encoded_message: str, teamname: str) -> dict:
#     encrypted_message = base64.b64decode(encoded_message.encode())
#     salt = encrypted_message[:16]
#     iv = encrypted_message[16:32]
#     encrypted_data = encrypted_message[32:]
#     key = derive_key(teamname, salt)
#     cipher = Cipher(algorithms.AES(key), modes.CBC(iv), backend=default_backend())
#     decryptor = cipher.decryptor()
#     padded_data = decryptor.update(encrypted_data) + decryptor.finalize()
#     unpadder = padding.PKCS7(algorithms.AES.block_size).unpadder()
#     json_data = unpadder.update(padded_data) + unpadder.finalize()
#     data = json.loads(json_data.decode())
#     return data


def decrypt_data(encoded_message: str, teamname: str) -> dict:
    return json.loads(((unpadder := padding.PKCS7(algorithms.AES.block_size).unpadder()).update((decryptor := Cipher(algorithms.AES(derive_key(teamname, (encrypted_message := base64.b64decode(encoded_message.encode()))[:16])), modes.CBC(encrypted_message[16:32]), backend=default_backend()).decryptor()).update(encrypted_message[32:]) + decryptor.finalize()) + unpadder.finalize()).decode())
