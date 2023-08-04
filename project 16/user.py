import socket
from gmssl import sm2
import base64
import binascii
import hashlib

def enc(data):
    private_key = 'B17EACC0BB629AB92C591287F2FA4589D10CD1E13BD4BDFDC9589A940F937C7C'
    public_key = '53B97D723AA4CEAC97A13B8C50AA53D40DE36960CFC3A3D7929FD54F39F824ED5A4A27AF871AD62C25C75C9D75C75A0907C565A78B805E9502E616C4E77F3B42'
    sm2_crypt = sm2.CryptSM2(
        public_key=public_key, private_key=private_key)
    enc_data = sm2_crypt.encrypt(data)
    return enc_data

def dec(data):
    private_key = 'B17EACC0BB629AB92C591287F2FA4589D10CD1E13BD4BDFDC9589A940F937C7C'
    public_key = '53B97D723AA4CEAC97A13B8C50AA53D40DE36960CFC3A3D7929FD54F39F824ED5A4A27AF871AD62C25C75C9D75C75A0907C565A78B805E9502E616C4E77F3B42'
    sm2_crypt = sm2.CryptSM2(
        public_key=public_key, private_key=private_key)
    dec_data =sm2_crypt.decrypt(data)
    return dec_data


s1 = socket.socket()
s1.connect(('127.0.0.1', 9006))
while 1:
    send_data = input("MES SEND:")
    mes = bytes(send_data.encode())
    s1.send(str(enc(mes)).encode())
    text = s1.recv(1024).decode()
    print("GET:{}".format(text))
