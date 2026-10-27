#include <stdio.h>
#include <string.h>
#include <ctype.h>

int modInverse(int a)
{
    int i;

    for (i = 1; i < 26; i++)
    {
        if ((a * i) % 26 == 1)
            return i;
    }

    return -1;
}

int main()
{
    char ciphertext[500];
    char plaintext[500];
    int freq[26] = {0};
    int i, max1 = -1, max2 = -1;
    int a = 3, b = 15;
    int a_inv;

    printf("Enter ciphertext:\n");
    fgets(ciphertext, sizeof(ciphertext), stdin);

    /* Count frequency */
    for (i = 0; ciphertext[i] != '\0'; i++)
    {
        if (isalpha(ciphertext[i]))
        {
            char ch = toupper(ciphertext[i]);
            freq[ch - 'A']++;
        }
    }

    /* Find most frequent letter */
    for (i = 0; i < 26; i++)
    {
        if (max1 == -1 || freq[i] > freq[max1])
            max1 = i;
    }

    /* Find second most frequent letter */
    for (i = 0; i < 26; i++)
    {
        if (i != max1 &&
            (max2 == -1 || freq[i] > freq[max2]))
            max2 = i;
    }

    printf("\nMost frequent ciphertext letter : %c\n", max1 + 'A');
    printf("Second most frequent letter     : %c\n", max2 + 'A');

    /*
       Assume:
       E -> B
       T -> U

       Affine encryption:
       C = (aP + b) mod 26

       From the mappings:
       E = 4, B = 1
       T = 19, U = 20

       We get:
       a = 3
       b = 15
    */

    a_inv = modInverse(a);

    printf("\nAssuming E -> B and T -> U\n");
    printf("a = %d\n", a);
    printf("b = %d\n", b);
    printf("Inverse of a = %d\n", a_inv);

    /* Decryption */
    for (i = 0; ciphertext[i] != '\0'; i++)
    {
        if (isalpha(ciphertext[i]))
        {
            int c = toupper(ciphertext[i]) - 'A';
            int p = (a_inv * (c - b)) % 26;

            if (p < 0)
                p += 26;

            plaintext[i] = p + 'A';
        }
        else
        {
            plaintext[i] = ciphertext[i];
        }
    }

    plaintext[i] = '\0';

    printf("\nDecrypted plaintext:\n");
    printf("%s", plaintext);

    return 0;
}