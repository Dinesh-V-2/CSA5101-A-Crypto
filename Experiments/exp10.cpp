#include <stdio.h>
#include <string.h>
#include <ctype.h>
char key[5][5] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};
void findPosition(char ch, int *row, int *col)
{
    int i, j;

    if (ch == 'J')
        ch = 'I';

    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (key[i][j] == ch)
            {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
int main()
{
    char text[200], plain[200], cipher[200];
    int i, j, r1, c1, r2, c2, len = 0;
    printf("Enter the plaintext: ");
    fgets(text, sizeof(text), stdin);
    for (i = 0; text[i] != '\0'; i++)
    {
        if (isalpha((unsigned char)text[i]))
        {
            char ch = toupper((unsigned char)text[i]);

            if (ch == 'J')
                ch = 'I';

            plain[len++] = ch;
        }
    }
    plain[len] = '\0';
    for (i = 0; i < len; i += 2)
    {
        if (i + 1 >= len || plain[i] == plain[i + 1])
        {
            for (j = len; j > i + 1; j--)
                plain[j] = plain[j - 1];

            plain[i + 1] = 'X';
            len++;
            plain[len] = '\0';
        }
    }
    for (i = 0; i < len; i += 2)
    {
        findPosition(plain[i], &r1, &c1);
        findPosition(plain[i + 1], &r2, &c2);

        if (r1 == r2)
        {
            cipher[i] = key[r1][(c1 + 1) % 5];
            cipher[i + 1] = key[r2][(c2 + 1) % 5];
        }
        else if (c1 == c2)
        {
            cipher[i] = key[(r1 + 1) % 5][c1];
            cipher[i + 1] = key[(r2 + 1) % 5][c2];
        }
        else
        {
            cipher[i] = key[r1][c2];
            cipher[i + 1] = key[r2][c1];
        }
    }
    cipher[len] = '\0';
    printf("Prepared Plaintext: %s\n", plain);
    printf("Encrypted Message:  %s\n", cipher);
    return 0;
}
