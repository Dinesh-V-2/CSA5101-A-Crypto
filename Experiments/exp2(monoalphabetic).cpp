#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main()
{
    char plaintext[100], ciphertext[100];
    char key[27] = "QWERTYUIOPASDFGHJKLZXCVBNM";
    int i;
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    for (i = 0; plaintext[i] != '\0'; i++)
    {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
            ciphertext[i] = key[plaintext[i] - 'A'];
        else if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
            ciphertext[i] = tolower(key[plaintext[i] - 'a']);
        else
            ciphertext[i] = plaintext[i];
    }
    ciphertext[i] = '\0';
    printf("Ciphertext: %s", ciphertext);
    return 0;
}