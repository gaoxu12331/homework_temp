# Project16: implement sm2 2P decrypt with real network communication

加密函数
``` python
def enc(data):
    private_key = 'B17EACC0BB629AB92C591287F2FA4589D10CD1E13BD4BDFDC9589A940F937C7C'
    public_key = '53B97D723AA4CEAC97A13B8C50AA53D40DE36960CFC3A3D7929FD54F39F824ED5A4A27AF871AD62C25C75C9D75C75A0907C565A78B805E9502E616C4E77F3B42'
    sm2_crypt = sm2.CryptSM2(
        public_key=public_key, private_key=private_key)
    enc_data = sm2_crypt.encrypt(data)
    return enc_data
```

解密函数

``` python
def dec(data):
    private_key = 'B17EACC0BB629AB92C591287F2FA4589D10CD1E13BD4BDFDC9589A940F937C7C'
    public_key = '53B97D723AA4CEAC97A13B8C50AA53D40DE36960CFC3A3D7929FD54F39F824ED5A4A27AF871AD62C25C75C9D75C75A0907C565A78B805E9502E616C4E77F3B42'
    sm2_crypt = sm2.CryptSM2(
        public_key=public_key, private_key=private_key)
    dec_data =sm2_crypt.decrypt(data)
    return dec_data

``` 

实验结果：

发送“123”

```  C
HEARING!!!
<socket.socket fd=4, family=AddressFamily.AF_INET, type=SocketKind.SOCK_STREAM, proto=0, laddr=('127.0.0.1', 9006), raddr=('127.0.0.1', 42652)> ('127.0.0.1', 42652)
GET:b'\xfcq5Y\xe1\x11JI\xf6\xe8\x89\x15\xd7M<`\x9a\xe3:\x9eK\xed\x1a\xe1\xf8\xbb\xaea\xc9F\xb7\x06i\xcd\xa9\x181\xe2n\xeb\x88\xd8\xea"\xff]\x81s$?\x94\xde\xf6\x97=\x87/\xc1y\x01\xb1\xa5\x86\x87`\x9c\x04\x91n\xb7\xadf\xd2\xab\x17\x10\xb8\xcf\x98\x80[\xb1\xf0\x92\xd8`\xf5O\x19F1-\xeb\xbdDy\xf5x\xb4Mi\xa2<\xe8.\x9fm\xb0W \x141\xcfv\xcb\xf7f\x7f\x1a\x0c\x0f\xa2>\xbb!P\x8b\xe6\xeeO\x94m-\xf2\xd5\x82@\xe5\xb7\xe1\x02\x0f\xbb\x87\xfe\xfc\x1e\xc1Y\xa4&\xd3ns\\\x9b\x16\r2\xfe\xe6\xc8T\xbe\x03(\xbb;\xd1\xac\x89\x14R\x9c\xa0\xf3(=\xe1$T\xc4\xfb\xfd\x17\xb1\x03\x87T\xd7ZN\xdc\xda\xa0\xbf\xd1]\xa1>\x83\x85\xa5\x99'
```