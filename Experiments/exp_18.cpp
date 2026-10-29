#include <stdio.h>
#include <stdint.h>
typedef uint64_t U64;
int PC1[56] = {
    57,49,41,33,25,17,9,
    1,58,50,42,34,26,18,
    10,2,59,51,43,35,27,
    19,11,3,60,52,44,36,
    63,55,47,39,31,23,15,
    7,62,54,46,38,30,22,
    14,6,61,53,45,37,29,
    21,13,5,28,20,12,4
};
int PC2[48] = {
    14,17,11,24,1,5,
    3,28,15,6,21,10,
    23,19,12,4,26,8,
    16,7,27,20,13,2,
    41,52,31,37,47,55,
    30,40,51,45,33,48,
    44,49,39,56,34,53,
    46,42,50,36,29,32
};
int shifts[16] = {
    1,1,2,2,2,2,2,2,
    1,2,2,2,2,2,2,1
};
U64 permute(U64 input, int table[], int n, int inputBits)
{
    U64 output = 0;
    for (int i = 0; i < n; i++) {
        output <<= 1;
        output |= (input >> (inputBits - table[i])) & 1ULL;
    }
    return output;
}
uint32_t leftRotate(uint32_t value, int shift)
{
    return ((value << shift) | (value >> (28 - shift)))
           & 0x0FFFFFFF;
}
int main(void)
{
    U64 key, permuted;
    uint32_t C, D;
    U64 subkey;
    printf("Enter 64-bit DES key in hexadecimal: ");
    if (scanf("%16llx", (unsigned long long *)&key) != 1) {
        printf("Invalid key.\n");
        return 1;
    }
    permuted = permute(key, PC1, 56, 64);
    C = (uint32_t)((permuted >> 28) & 0x0FFFFFFF);
    D = (uint32_t)(permuted & 0x0FFFFFFF);
    printf("\nInitial 28-bit halves:\n");
    printf("C0 = %07X\n", C);
    printf("D0 = %07X\n", D);
    printf("\nDES Round Subkeys:\n");
    for (int round = 0; round < 16; round++) {
        C = leftRotate(C, shifts[round]);
        D = leftRotate(D, shifts[round]);
        U64 combined = ((U64)C << 28) | D;
        subkey = permute(combined, PC2, 48, 56);
        printf("K%-2d = %012llX\n",
               round + 1, (unsigned long long)subkey);
    }
    return 0;
}