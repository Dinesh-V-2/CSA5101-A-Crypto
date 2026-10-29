#include <stdio.h>
#include <string.h>
#define BLOCKS 4
#define SIZE 8
void encryptBlock(const char input[], char output[])
{
    for (int i = 0; i < SIZE; i++)
        output[i] = input[i] ^ 0x5A;
}
void decryptBlock(const char input[], char output[])
{
    encryptBlock(input, output);
}
void printBlocks(char blocks[BLOCKS][SIZE + 1])
{
    for (int i = 0; i < BLOCKS; i++)
        printf("P%d: %s\n", i + 1, blocks[i]);
}
int main(void)
{
    char plain[BLOCKS][SIZE + 1] = {
        "BLOCK001", "BLOCK002", "BLOCK003", "BLOCK004"
    };
    char cipher[BLOCKS][SIZE + 1] = {{0}};
    char received[BLOCKS][SIZE + 1] = {{0}};
    char recovered[BLOCKS][SIZE + 1] = {{0}};
    char iv[SIZE + 1] = "INITVECT";
    int i, j;
    char temp[SIZE];
    printf("ERROR PROPAGATION IN ECB AND CBC MODES\n");
    printf("--------------------------------------\n");
    for (i = 0; i < BLOCKS; i++) {
        encryptBlock(plain[i], cipher[i]);
        cipher[i][SIZE] = '\0';
    }
    memcpy(received, cipher, sizeof(cipher));
    received[0][0] ^= 1;
    printf("\nECB Mode: Error in C1\n");
    for (i = 0; i < BLOCKS; i++) {
        decryptBlock(received[i], recovered[i]);
        recovered[i][SIZE] = '\0';
    }
    printBlocks(recovered);
    for (i = 0; i < BLOCKS; i++) {
        for (j = 0; j < SIZE; j++) {
            char previous = (i == 0)
                ? iv[j]
                : cipher[i - 1][j];
            temp[j] = plain[i][j] ^ previous;
        }
        encryptBlock(temp, cipher[i]);
        cipher[i][SIZE] = '\0';
    }
    memcpy(received, cipher, sizeof(cipher));
    received[0][0] ^= 1;
    printf("\nCBC Mode: Error in C1\n");
    for (i = 0; i < BLOCKS; i++) {
        decryptBlock(received[i], temp);
        for (j = 0; j < SIZE; j++) {
            char previous = (i == 0)
                ? iv[j]
                : received[i - 1][j];
            recovered[i][j] = temp[j] ^ previous;
        }
        recovered[i][SIZE] = '\0';
    }
    printBlocks(recovered);
    return 0;
}