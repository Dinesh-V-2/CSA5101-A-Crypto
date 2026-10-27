#include <stdio.h>
#include <ctype.h>
#include <string.h>
int main() {
    char plain[] = "abcdefghijklmnopqrstuvwxyz";
    char cipher[27];
    char keyword[] = "CIPHER";
    char message[100];
    char encrypted[100];
    int i, j, k = 0, found;
    for (i = 0; keyword[i] != '\0'; i++) {
        cipher[k++] = keyword[i];
    }
    for (i = 0; i < 26; i++) {
        found = 0;
        for (j = 0; keyword[j] != '\0'; j++) {
            if (plain[i] == tolower(keyword[j])) {
                found = 1;
                break;
            }
        }
        if (!found) {
            cipher[k++] = plain[i] - 'a' + 'A';
        }
    }
    cipher[26] = '\0';
    printf("Enter plaintext: ");
    fgets(message, sizeof(message), stdin);
    for (i = 0; message[i] != '\0'; i++) {
        if (isalpha((unsigned char)message[i])) {
            j = tolower((unsigned char)message[i]) - 'a';
            encrypted[i] = cipher[j];
        } else {
            encrypted[i] = message[i];
        }
    }
    encrypted[i] = '\0';
    printf("\nPlaintext alphabet : %s\n", plain);
    printf("Cipher alphabet    : %s\n", cipher);
    printf("Encrypted message  : %s", encrypted);
    return 0;
}
