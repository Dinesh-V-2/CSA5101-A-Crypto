#include <stdio.h>
#include <string.h>

int main()
{
    char ciphertext[3000];
    char plaintext[3000];
    char key[256];
    int i;

    /* Initialize substitution table */
    for (i = 0; i < 256; i++)
        key[i] = '?';

    printf("Enter the ciphertext:\n");

    fgets(ciphertext, sizeof(ciphertext), stdin);

    /*
       Substitution mapping obtained by frequency analysis.

       The following mappings can be changed according
       to the deductions made from the ciphertext.
    */

    key['8'] = 'e';
    key['4'] = 't';
    key[';'] = 'h';
    key['*'] = 'a';
    key[')'] = 'o';
    key['6'] = 'i';
    key['‡'] = 'n';
    key['†'] = 'd';
    key['5'] = 's';
    key['2'] = 'r';
    key['0'] = 'l';
    key['3'] = 'c';
    key['9'] = 'm';
    key['1'] = 'f';
    key['('] = 'g';
    key[':'] = 'y';
    key['?'] = 'p';
    key['¶'] = 'u';
    key[']'] = 'v';
    key['.'] = 'w';
    key['—'] = 'b';

    /* Decrypt the ciphertext */
    for (i = 0; ciphertext[i] != '\0'; i++)
    {
        unsigned char ch = ciphertext[i];

        if (ch == ' ' || ch == '\n' || ch == '\t')
        {
            plaintext[i] = ch;
        }
        else if (key[ch] != '?')
        {
            plaintext[i] = key[ch];
        }
        else
        {
            plaintext[i] = ch;
        }
    }

    plaintext[i] = '\0';

    printf("\nDecrypted message:\n");
    printf("%s\n", plaintext);

    return 0;
}