#include <stdio.h>
#include <string.h>
#define MAX 256
#define BLOCK 8
void encryptBlock(unsigned char in, unsigned char key,
                  unsigned char *out) {
    *out = in ^ key; 
}
void decryptBlock(unsigned char in, unsigned char key,
                  unsigned char *out) {
    *out = in ^ key;
}
int padMessage(unsigned char data[], int len) {
    int paddedLen = ((len / BLOCK) + 1) * BLOCK;
    data[len] = 0x80;  
    for (int i = len + 1; i < paddedLen; i++)
        data[i] = 0x00;
    return paddedLen;
}
void ECB(unsigned char data[], int len, unsigned char key,
         unsigned char output[]) {
    for (int i = 0; i < len; i++)
        encryptBlock(data[i], key, &output[i]);
}
void CBC(unsigned char data[], int len, unsigned char key,
         unsigned char iv, unsigned char output[]) {
    unsigned char prev = iv;
    for (int i = 0; i < len; i++) {
        unsigned char temp = data[i] ^ prev;
        encryptBlock(temp, key, &output[i]);
        prev = output[i];
    }
}
void CFB(unsigned char data[], int len, unsigned char key,
         unsigned char iv, unsigned char output[]) {
    unsigned char prev = iv;
    for (int i = 0; i < len; i++) {
        unsigned char stream;
        encryptBlock(prev, key, &stream);
        output[i] = data[i] ^ stream;
        prev = output[i];
    }
}
void printData(const char *label, unsigned char data[], int len) {
    printf("%s", label);
    for (int i = 0; i < len; i++)
        printf("%02X ", data[i]);
    printf("\n");
}
int main(void) {
    unsigned char data[MAX], ecb[MAX], cbc[MAX], cfb[MAX];
    unsigned char key, iv;
    char text[MAX];
    int len, paddedLen;
    printf("Enter plaintext: ");
    if (!fgets(text, sizeof(text), stdin))
        return 1;
    text[strcspn(text, "\n")] = '\0';
    len = (int)strlen(text);
    if (len == 0) {
        printf("Plaintext must not be empty.\n");
        return 1;
    }
    printf("Enter one-byte key (hex): ");
    if (scanf("%hhx", &key) != 1)
        return 1;
    printf("Enter one-byte IV (hex): ");
    if (scanf("%hhx", &iv) != 1)
        return 1;
    memcpy(data, text, len);
    paddedLen = padMessage(data, len);
    printf("\nPadded plaintext:\n");
    printData("", data, paddedLen);
    ECB(data, paddedLen, key, ecb);
    CBC(data, paddedLen, key, iv, cbc);
    CFB(data, paddedLen, key, iv, cfb);
    printf("\nECB ciphertext:\n");
    printData("", ecb, paddedLen);
    printf("\nCBC ciphertext:\n");
    printData("", cbc, paddedLen);
    printf("\nCFB ciphertext:\n");
    printData("", cfb, paddedLen);
    return 0;
}