# Project2: implement the Rho method of reduced SM3

## 运行环境

操作系统：Ubuntu 22.04.2 LTS 64位

编译环境：C++ 使用 g++ (Ubuntu 11.3.0-1ubuntu1~22.04.1) 11.3.0，
不使用编译优化

硬件环境：11th Gen Intel® Core™ i5-1135G7 @ 2.40G   16.0 GiB

---

选择迭代函数
```  C
#define func(n) (n * n + 1)
```

主要程序内容描述：
```  C
int main()
{
    clock_t s, t;
    bit32 V1[8] = {0x7380166f, 0x4914b2b9, 0x172442d7, 0xda8a0600, 0xa96f30bc, 0x163138aa, 0xe38dee4d, 0xb0fb0e4e};
    bit32 V2[8] = {0x7380166f, 0x4914b2b9, 0x172442d7, 0xda8a0600, 0xa96f30bc, 0x163138aa, 0xe38dee4d, 0xb0fb0e4e};
    s = clock();
    for (bit32 i = 0; i < (2 << 20); i++)
    {
        bit32 m = func(i);
        bit32 n = func(2 * i);
        SM3((bit8 *)(&m), V1);
        SM3((bit8 *)(&n), V2);
        if (strcmp((char *)V1, (char *)V2) == 0)
        {
            cout << "Success!\n";
            cout << hex << "0x" << m << endl;
            cout << hex << "0x" << n << endl;
            break;
        }
    }
    t = clock();
    cout << (double)(t - s) / (CLOCKS_PER_SEC) << " s" << endl;
    return 0;
}
``` 

选择的攻击长度：20bit

实验结果

``` 
Success!
0x176c911
0x5db2441
0.016944 s
```

发现0x176c911和0x5db2441出现碰撞；

可以发现：进行Rho攻击明显速度较快，有很好的攻击结果。
