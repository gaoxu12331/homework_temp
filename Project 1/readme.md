# SM3生日攻击


## 运行环境

操作系统：Ubuntu 22.04.2 LTS 64位

编译环境：C++ 使用 g++ (Ubuntu 11.3.0-1ubuntu1~22.04.1) 11.3.0，
不使用编译优化

硬件环境：11th Gen Intel® Core™ i5-1135G7 @ 2.40G   16.0 GiB

---

## 重要代码描述

```  C
int main()
{
    size_t len = 15;
    clock_t a, b;
    bool mark = 0;
    a = clock();
    for (bit32 i = 0; i < (1 << len); i++)
    {
        for (bit32 j = 0; j < (1 << len); j++)
        {
            if (i == j)
                continue;
            bit32 V1[8] = {0x7380166f, 0x4914b2b9, 0x172442d7, 0xda8a0600, 0xa96f30bc, 0x163138aa, 0xe38dee4d, 0xb0fb0e4e};
            bit32 V2[8] = {0x7380166f, 0x4914b2b9, 0x172442d7, 0xda8a0600, 0xa96f30bc, 0x163138aa, 0xe38dee4d, 0xb0fb0e4e};
            SM3((bit8 *)(&i), V1);
            SM3((bit8 *)(&j), V2);
            if (strcmp((char *)V1, (char *)V2) == 0)
            {
                cout << "Success!\n";
                cout << hex << "0x" << i << endl;
                cout << hex << "0x" << j << endl;
                mark = 1;
                break;
            }
        }
        if(mark)
            break;
    }
    b = clock();
    cout << (double)(b - a) / (CLOCKS_PER_SEC) << " s" << endl;
    return 0;
}

```

遍历长度为15bit，方法为直接遍历，进行生日攻击，发现可以快速得到碰撞。


## 实验结果

```

Success!
0x129
0x315
28.4605 s
```
