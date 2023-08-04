# Project8: AES impl with ARM instruction

## 运行环境

操作系统：Ubuntu 22.04.2 LTS 64位

编译环境：C++ 使用 g++ (Ubuntu 11.3.0-1ubuntu1~22.04.1) 11.3.0，
不使用编译优化

硬件环境：11th Gen Intel® Core™ i5-1135G7 @ 2.40G   16.0 GiB

---

通过查阅资料：得知——
 <wmmintrin.h> 头文件存在加密指令

主体函数：
```  C
int main() 
{
    __m128i key = _mm_setr_epi32(0x2b7e1516, 0x28aed2a6, 0xabf7143f, 0x9c2c560d);
    __m128i data = _mm_setr_epi32(0x3243f6a8, 0x885a308d, 0x313198a2, 0xe0370734);

    // 执行AES加密
    __m128i encrypted = _mm_aesenc_si128(data, key);

    return 0;
}
```

程序使用gcc指令进行编译运行

实验结果：
``` C
0x765849803a25e7793608278b5183e353
```
