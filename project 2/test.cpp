#include "SM3.h"
#include <ctime>

// 迭代函数
#define func(n) (n * n + 1)

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