#include <stdio.h>
#include <string.h>
#define BLOCK_SIZE 8
void encryptBlock(unsigned char input[], unsigned char output[],
                  unsigned char key[]) {
    int i;
    for (i = 0; i < BLOCK_SIZE; i++) {
        output[i] = input[i] ^ key[i];
    }
}
void xorBlocks(unsigned char a[], unsigned char b[],
               unsigned char result[]) {
    int i;
    for (i = 0; i < BLOCK_SIZE; i++) {
        result[i] = a[i] ^ b[i];
    }
}
void cbcMac(unsigned char message[][BLOCK_SIZE], int blocks,
            unsigned char key[], unsigned char tag[]) {
    unsigned char state[BLOCK_SIZE] = {0};
    unsigned char temp[BLOCK_SIZE];
    int i, j;
    for (i = 0; i < blocks; i++) {
        xorBlocks(state, message[i], temp);
        encryptBlock(temp, state, key);
    }
    for (j = 0; j < BLOCK_SIZE; j++) {
        tag[j] = state[j];
    }
}
void printBlock(const char *label, unsigned char block[]) {
    int i;
    printf("%s", label);
    for (i = 0; i < BLOCK_SIZE; i++) {
        printf("%02X ", block[i]);
    }
    printf("\n");
}
int main(void) {
    unsigned char key[BLOCK_SIZE] =
        {0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80};
    unsigned char message[2][BLOCK_SIZE] = {
        {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08},
        {0}
    };
    unsigned char tag1[BLOCK_SIZE];
    unsigned char tag2[BLOCK_SIZE];
    unsigned char forgedBlock[BLOCK_SIZE];
    int i;
    cbcMac(message, 1, key, tag1);
    xorBlocks(message[0], tag1, forgedBlock);
    for (i = 0; i < BLOCK_SIZE; i++) {
        message[1][i] = forgedBlock[i];
    }

    cbcMac(message, 2, key, tag2);
    printf("CBC-MAC Forgery Demonstration\n\n");
    printBlock("Message X       : ", message[0]);
    printBlock("Tag T            : ", tag1);
    printBlock("Forged block     : ", forgedBlock);
    printBlock("MAC of 2-block msg: ", tag2);
    if (memcmp(tag1, tag2, BLOCK_SIZE) == 0) {
        printf("\nForgery successful: both tags match.\n");
    } else {
        printf("\nTags do not match.\n");
    }
    return 0;
}
