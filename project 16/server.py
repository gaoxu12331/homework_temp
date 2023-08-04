import socket
from gmssl import sm2
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


s = socket.socket()
s.bind(('127.0.0.1',9006))
s.listen(5)
private_key = '00B9AB0B828FF68872F21A837FC303668428DEA11DCD1B24429D0C99E24EED83D5'
public_key = 'B9C9A6E04E9C91F7BA880429273747D7EF5DDEB0BB2FF6317EB00BEF331A83081A6994B8993F3F5D6EADDDB81872266C87C018FB4162F5AF347B483E24620207'
print("HEARING!!!")
while 1:
    sock,addr = s.accept()
    print(sock,addr)
    while 1:
        text = sock.recv(1024)
        ret = dec(bytes(text.decode().encode()))
        print("GET:{}".format(ret))
        content = input("SENT:")
        sock.send(content.encode())
    sock.close()