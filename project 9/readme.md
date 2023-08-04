# Project9: AES / SM4 software implementation

## 运行环境

操作系统：Ubuntu 22.04.2 LTS 64位

编译环境：C++ 使用 g++ (Ubuntu 11.3.0-1ubuntu1~22.04.1) 11.3.0，
不使用编译优化

硬件环境：11th Gen Intel® Core™ i5-1135G7 @ 2.40G   16.0 GiB

---
使用宏进行加速优化

``` C
// 循环左移
#define lift32(val,n)(val >> (32 - n)) + (val << n)
```

``` C
// T 置换
bit32 deal_T(bit32 input)
{
    bit32 ret = 0;
    bit8 *point = (bit8 *)&input;
    bit8 a[4] = {point[3], point[2], point[1], point[0]};
    for (int i = 0; i < 4; i++)
    {
        ret = ret << 8;
        ret += Sbox[(a[i] / 16) * 16 + (a[i] % 16)];
    }
    ret = ret ^ (lift32(ret, 2)) ^ lift32(ret, 10) ^ lift32(ret, 18) ^ lift32(ret, 24);
    return ret;
}
```

``` C
// T’置换
bit32 deal_point_T(bit32 input)
{
    bit32 ret = 0;
    bit8 *point = (bit8 *)&input;
    bit8 a[4] = {point[3], point[2], point[1], point[0]};
    for (int i = 0; i < 4; i++)
    {
        ret = ret << 8;
        ret += Sbox[(a[i] / 16) * 16 + (a[i] % 16)];
    }
    ret = ret ^ (lift32(ret, 13)) ^ lift32(ret, 23);
    return ret;
}
```

``` C
// 密钥生成
void key_generate(bit32 MK[4], bit32 rK[32])
{
    bit32 K[36] = {MK[0] ^ FK[0], MK[1] ^ FK[1], MK[2] ^ FK[2], MK[3] ^ FK[3]};
    for (size_t i = 0; i < 32; i++)
        K[i + 4] = rK[i] = K[i] ^ deal_point_T(K[i + 1] ^ K[i + 2] ^ K[i + 3] ^ CK[i]);
}
```

输入 input[4] = {0x01234567, 0x89ABCDEF, 0xFEDCBA98, 0x76543210};
密钥 key[4] = {0x01234567, 0x89ABCDEF, 0xFEDCBA98, 0x76543210};

运行结果：
0x681edf34  0xd206965e  0x86b3e94f  0x536e4246 
通过文档验证
