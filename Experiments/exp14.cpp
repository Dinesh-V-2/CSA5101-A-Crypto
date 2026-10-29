#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main() {
    char plain[] = "send more money";
    char target[] = "cash not needed";
    char cipher[100], key2[100];
    int key[] = {9, 0, 1, 7, 23, 15, 21,
                 14, 11, 11, 2, 8, 9};
    int i, j = 0, n = 0;
    for (i = 0; plain[i] != '\0'; i++) {
        if (plain[i] != ' ') {
            int p = tolower(plain[i]) - 'a';
            cipher[n++] = (p + key[j++]) % 26 + 'a';
        } else {
            cipher[n++] = ' ';
        }
    }
    cipher[n] = '\0';
    printf("Part (a): Encryption\n");
    printf("Plaintext : %s\n", plain);
    printf("Ciphertext: %s\n\n", cipher);
    j = 0;
    for (i = 0; target[i] != '\0'; i++) {
        if (target[i] != ' ') {
            int c = tolower(cipher[i]) - 'a';
            int p = tolower(target[i]) - 'a';

            key2[j++] = (c - p + 26) % 26 + 'a';
        }
    }
    key2[j] = '\0';
    printf("Part (b): Key for target plaintext\n");
    printf("Desired plaintext: %s\n", target);
    printf("Required key     : %s\n", key2);
    return 0;
}
