#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 200
int main(void) {
    char plaintext[MAX], ciphertext[MAX], decrypted[MAX];
    int key[MAX], n, i;
    printf("Enter plaintext (letters only): ");
    scanf("%199s", plaintext);
    n = (int)strlen(plaintext);
    printf("Enter %d key values (0 to 25):\n", n);
    for (i = 0; i < n; i++) {
        if (scanf("%d", &key[i]) != 1 || key[i] < 0 || key[i] > 25) {
            printf("Invalid key! Values must be between 0 and 25.\n");
            return 1;
        }
    }
    for (i = 0; i < n; i++) {
        if (!isalpha((unsigned char)plaintext[i])) {
            printf("Please enter letters only.\n");
            return 1;
        }
        int p = toupper((unsigned char)plaintext[i]) - 'A';
        ciphertext[i] = (p + key[i]) % 26 + 'A';
    }
    ciphertext[n] = '\0';
    for (i = 0; i < n; i++) {
        int c = ciphertext[i] - 'A';
        decrypted[i] = (c - key[i] + 26) % 26 + 'A';
    }
    decrypted[n] = '\0';
    printf("\nCiphertext: %s\n", ciphertext);
    printf("Decrypted text: %s\n", decrypted);
    return 0;
}