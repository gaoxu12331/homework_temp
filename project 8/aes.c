#include <wmmintrin.h>  // 包含AES指令集的头文件

int main() {
    __m128i key = _mm_setr_epi32(0x2b7e1516, 0x28aed2a6, 0xabf7143f, 0x9c2c560d);
    __m128i data = _mm_setr_epi32(0x3243f6a8, 0x885a308d, 0x313198a2, 0xe0370734);

    // 执行AES加密
    __m128i encrypted = _mm_aesenc_si128(data, key);

    return 0;
}