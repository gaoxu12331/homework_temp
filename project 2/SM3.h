#ifndef _SM3_
#define _SM3_

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>

using namespace std;
using bit8 = unsigned char;
using bit32 = unsigned int;

#define lift32(input, n) ((input << n) | (input >> (32 - n)))

#define T(j) (j <= 15 ? 0x79cc4519 : 0x7a879d8a)

#define FF(X, Y, Z, j) (j <= 15 ? X ^ Y ^ Z : (X & Y) | (X & Z) | (Y & Z))

#define GG(X, Y, Z, j) (j <= 15 ? X ^ Y ^ Z : (X & Y) | ((~X) & Z))

#define P0(X) (X ^ lift32(X, 9) ^ lift32(X, 17))

bit32 P1(bit32 X)
{
    return X ^ lift32(X, 15) ^ lift32(X, 23);
}

// CF操作
void CF(bit32 V[8], bit8 B[64], int i, bit32 *W, bit32 *Wp)
{
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
    }
    for (int j = 0; j < 8; j++)
        V[j] = V[j] ^ temp[j];
}

/// SM3计算函数主体
void SM3(bit8 *mes, bit32 V[8])
{
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
    const size_t plen = total_len / 64;
    bit32 W[plen][68]{};
    bit32 Wp[plen][64]{};
    for (size_t i = 0; i < plen; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            swap((B + i * 64)[4 * j], (B + i * 64)[4 * j + 3]);
            swap((B + i * 64)[4 * j + 1], (B + i * 64)[4 * j + 2]);
            W[i][j] = *(bit32 *)(&(B + i * 64)[4 * j]);
        }
        for (int j = 16; j <= 67; j++)
            W[i][j] = P1(W[i][j - 16] ^ W[i][j - 9] ^ lift32(W[i][j - 3], 15)) ^ lift32(W[i][j - 13], 7) ^ W[i][j - 6];

        for (int j = 0; j < 64; j += 4)
        {
            Wp[i][j] = W[i][j] ^ W[i][j + 4];
            Wp[i][j + 1] = W[i][j + 1] ^ W[i][j + 5];
            Wp[i][j + 2] = W[i][j + 2] ^ W[i][j + 6];
            Wp[i][j + 3] = W[i][j + 3] ^ W[i][j + 7];
        }
    }
    for (size_t i = 0; i < plen; i++)
        CF(V, B + i * 64, i, W[i], Wp[i]);
}

#endif 