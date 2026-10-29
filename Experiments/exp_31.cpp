#include <stdio.h>
#include <string.h>
void leftShift(unsigned char input[], unsigned char output[], int n) {
    int i;
    unsigned char carry = 0;
    for (i = n - 1; i >= 0; i--) {
        unsigned char nextCarry = (input[i] & 0x80) ? 1 : 0;
        output[i] = (input[i] << 1) | carry;
        carry = nextCarry;
    }
}
void generateSubkey(unsigned char input[], unsigned char output[],
                    int n, unsigned char Rb) {
    int i;
    unsigned char shifted[16];
    unsigned char msb = input[0] & 0x80;
    leftShift(input, shifted, n);
    for (i = 0; i < n; i++)
        output[i] = shifted[i];
    if (msb)
        output[n - 1] ^= Rb;
}
void printHex(const char *label, unsigned char data[], int n) {
    int i;
    printf("%s", label);
    for (i = 0; i < n; i++)
        printf("%02X", data[i]);
    printf("\n");
}
int main(void) {
    int bits, n, i;
    unsigned char L[16] = {0};
    unsigned char K1[16], K2[16];
    unsigned char Rb;
    printf("Enter block size (64 or 128): ");
    scanf("%d", &bits);
    if (bits != 64 && bits != 128) {
        printf("Invalid block size.\n");
        return 1;
    }
    n = bits / 8;
    Rb = (bits == 64) ? 0x1B : 0x87;
    printf("Enter L = E_K(0^n) in hexadecimal (%d bytes):\n", n);
    for (i = 0; i < n; i++) {
        unsigned int value;
        scanf("%2x", &value);
        L[i] = (unsigned char)value;
    }
    generateSubkey(L, K1, n, Rb);
    generateSubkey(K1, K2, n, Rb);
    printHex("L  = ", L, n);
    printHex("K1 = ", K1, n);
    printHex("K2 = ", K2, n);
    return 0;
}