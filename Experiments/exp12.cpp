#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main()
{
    char text[200], plain[200], cipher[200], decrypted[200];
    int key[2][2] = {{9, 4}, {5, 7}};
    int inv[2][2] = {{5, 12}, {15, 25}};
    int i, j, len = 0, a, b, x, y;
    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);
    for (i = 0; text[i] != '\0'; i++)
    {
        if (isalpha((unsigned char)text[i]))
            plain[len++] = toupper((unsigned char)text[i]);
    }
    if (len % 2 != 0)
        plain[len++] = 'X';
    plain[len] = '\0';
    printf("\n--- ENCRYPTION ---\n");
    for (i = 0; i < len; i += 2)
    {
        a = plain[i] - 'A';
        b = plain[i + 1] - 'A';
        x = (key[0][0] * a + key[0][1] * b) % 26;
        y = (key[1][0] * a + key[1][1] * b) % 26;
        cipher[i] = x + 'A';
        cipher[i + 1] = y + 'A';
        printf("%c%c -> (%d,%d) -> (%d,%d) -> %c%c\n",
               plain[i], plain[i + 1], a, b, x, y,
               cipher[i], cipher[i + 1]);
    }
    cipher[len] = '\0';
    printf("\nCiphertext: %s\n", cipher);
    printf("\n--- DECRYPTION ---\n");
    for (i = 0; i < len; i += 2)
    {
        a = cipher[i] - 'A';
        b = cipher[i + 1] - 'A';
        x = (inv[0][0] * a + inv[0][1] * b) % 26;
        y = (inv[1][0] * a + inv[1][1] * b) % 26;
        decrypted[i] = x + 'A';
        decrypted[i + 1] = y + 'A';
        printf("%c%c -> (%d,%d) -> (%d,%d) -> %c%c\n",
               cipher[i], cipher[i + 1], a, b, x, y,
               decrypted[i], decrypted[i + 1]);
    }
    decrypted[len] = '\0';
    printf("\nDecrypted text: %s\n", decrypted);
    return 0;
}
