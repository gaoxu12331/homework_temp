#include "SM3.h"
#include <random>
int main()
{
    // 设置原本明文0xffffffff，长度为32位；
    bit32 mes1 = 0xffffffff;
    // 设置扩展内容为0x1234
    bit8 add[2] = {0x12, 0x34};
    bit32 V1[8] = {0x7380166f, 0x4914b2b9, 0x172442d7, 0xda8a0600, 0xa96f30bc, 0x163138aa, 0xe38dee4d, 0xb0fb0e4e};
    // 计算原本的SM3结果
    SM3((bit8 *)(&mes1), V1);
    // 原本加密结果为V1
    // ******************************
    // 现在的填充长度为512+16 = 528位
    // 以下计算加入扩展内容的最后一个分段的数值
    size_t len = 528;
    int k = (447 - len) % 512 >= 0 ? (447 - len) % 512 : (447 - len) % 512 + 512;
    const size_t total_len = (len + 65 + k) / 8;
    bit8 B[total_len]{};
    strcpy((char *)B, (char *)add);
    B[len / 8] = 0x80;
    *(size_t *)(B + total_len - 8) = len;
    swap(B[total_len - 8], B[total_len - 1]);
    swap(B[total_len - 7], B[total_len - 2]);
    swap(B[total_len - 6], B[total_len - 3]);
    swap(B[total_len - 5], B[total_len - 4]);
    // ******************************
    // 以下步骤实现消息扩展与混淆计算
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
    // ******************************
    // 最后与原本结果V进行异或实现长度拓展攻击
    int i1 = 1;
    CF(V1, B, i1, W[i1], Wp[i1]);
    for (int i = 0; i < 64; i++)
    {
        cout << hex << (bit32)(V1[i]) << " ";
    }
    cout << endl;
    return 0;
}