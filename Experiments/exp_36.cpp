#include <stdio.h>
#include <string.h>
#include <ctype.h>
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int modInverse(int a) {
    int i;
    for (i = 1; i < 26; i++) {
        if ((a * i) % 26 == 1)
            return i;
    }
    return -1;
}
int main(void) {
    char plaintext[200], ciphertext[200], decrypted[200];
    int a, b, i, inverse;
    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';
    printf("Enter key a: ");
    scanf("%d", &a);
    printf("Enter key b: ");
    scanf("%d", &b);
    a = (a % 26 + 26) % 26;
    b = (b % 26 + 26) % 26;
    if (gcd(a, 26) != 1) {
        printf("Invalid key: a must be relatively prime to 26.\n");
        return 1;
    }
    inverse = modInverse(a);
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha((unsigned char)plaintext[i])) {
            int p = toupper((unsigned char)plaintext[i]) - 'A';
            ciphertext[i] = (a * p + b) % 26 + 'A';
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[i] = '\0';

    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha((unsigned char)ciphertext[i])) {
            int c = toupper((unsigned char)ciphertext[i]) - 'A';
            int p = (inverse * (c - b + 26)) % 26;
            decrypted[i] = p + 'A';
        } else {
            decrypted[i] = ciphertext[i];
        }
    }
    decrypted[i] = '\0';
    printf("\nEncrypted text: %s\n", ciphertext);
    printf("Decrypted text: %s\n", decrypted);
    return 0;
}
