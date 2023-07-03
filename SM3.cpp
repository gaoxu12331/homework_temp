#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;
using bit8 = unsigned char;
using bit32 = unsigned int;

bit32 lift32(bit32 input, char n)
{
    return (input << n) | (input >> (32 - n));
}

bit32 T(int j)
{
    if (j <= 15)
        return 0x79cc4519;
    else
        return 0x7a879d8a;
}

bit32 FF(bit32 X, bit32 Y, bit32 Z, int j)
{
    if (j <= 15)
        return X ^ Y ^ Z;
    else
        return (X & Y) | (X & Z) | (Y & Z);
}

bit32 GG(bit32 X, bit32 Y, bit32 Z, int j)
{
    if (j <= 15)
        return X ^ Y ^ Z;
    else
        return (X & Y) | ((~X) & Z);
}

bit32 P0(bit32 X)
{
    return X ^ lift32(X, 9) ^ lift32(X, 17);
}

bit32 P1(bit32 X)
{
    return X ^ lift32(X, 15) ^ lift32(X, 23);
}

void CF(bit32 V[8], bit8 B[64], int i)
{
    bit32 W[68]{};
    bit32 Wp[64]{};
    for (int j = 0; j < 16; j++)
    {
        swap(B[4 * j], B[4 * j + 3]);
        swap(B[4 * j + 1], B[4 * j + 2]);
        W[j] = *(bit32 *)(&B[4 * j]);
    }
    for (int j = 16; j <= 67; j++)
        W[j] = P1(W[j - 16] ^ W[j - 9] ^ lift32(W[j - 3], 15)) ^ lift32(W[j - 13], 7) ^ W[j - 6];

    for (int j = 0; j < 64; j++)
        Wp[j] = W[j] ^ W[j + 4];

    bit32 SS1 = 0, SS2 = 0, TT1 = 0, TT2 = 0;
    bit32 temp[8] = {V[0], V[1], V[2], V[3], V[4], V[5], V[6], V[7]};
    for (int j = 0; j <= 63; j++)
    {
        SS1 = lift32((lift32(temp[0], 12) + temp[4] + lift32(T(j), j % 32)), 7);
        SS2 = SS1 ^ lift32(temp[0], 12);
        TT1 = FF(temp[0], temp[1], temp[2], j) + temp[3] + SS2 + Wp[j];
        TT2 = GG(temp[4], temp[5], temp[6], j) + temp[7] + SS1 + W[j];
        temp[3] = temp[2];
        temp[2] = lift32(temp[1], 9);
        temp[1] = temp[0];
        temp[0] = TT1;
        temp[7] = temp[6];
        temp[6] = lift32(temp[5], 19);
        temp[5] = temp[4];
        temp[4] = P0(TT2);
        bit8 *tempp = (bit8 *)temp;
    }
    for (int j = 0; j < 8; j++)
        V[j] = V[j] ^ temp[j];
    for (int j = 0; j < 8; j++)
        cout << hex << V[j] << "  ";
    cout << endl;
}

void SM3(bit8 *mes)
{
    bit32 V[8] = {0x7380166f, 0x4914b2b9, 0x172442d7, 0xda8a0600, 0xa96f30bc, 0x163138aa, 0xe38dee4d, 0xb0fb0e4e};
    size_t len = 8 * strlen((char *)mes);
    int k = (447 - len) % 512 >= 0 ? (447 - len) % 512 : (447 - len) % 512 + 512;
    const size_t total_len = (len + 65 + k) / 8;
    bit8 B[total_len]{};
    strcpy((char *)B, (char *)mes);
    B[len / 8] = 0x80;
    *(size_t *)(B + total_len - 8) = len;
    swap(B[total_len - 8], B[total_len - 1]);
    swap(B[total_len - 7], B[total_len - 2]);
    swap(B[total_len - 6], B[total_len - 3]);
    swap(B[total_len - 5], B[total_len - 4]);
    for (size_t i = 0; i < total_len / 64; i++)
        CF(V, B + i * 64, i);
}

int main()
{
    bit8 mes[3] = {0x61, 0x62, 0x63};
    SM3(mes);
    return 0;
}