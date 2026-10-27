#include <stdio.h>
#include <string.h>
#include <ctype.h>
char matrix[5][5];
void createMatrix(char key[])
{
    int used[26] = {0};
    int i, j, k = 0;
    char ch;
    for (i = 0; key[i] != '\0'; i++)
    {
        ch = toupper(key[i]);
        if (ch == 'J')
            ch = 'I';

        if (ch >= 'A' && ch <= 'Z' && !used[ch - 'A'])
        {
            matrix[k / 5][k % 5] = ch;
            used[ch - 'A'] = 1;
            k++;
        }
    }
    for (ch = 'A'; ch <= 'Z'; ch++)
    {
        if (ch == 'J')
            continue;

        if (!used[ch - 'A'])
        {
            matrix[k / 5][k % 5] = ch;
            used[ch - 'A'] = 1;
            k++;
        }
    }
}
void findPosition(char ch, int *row, int *col)
{
    int i, j;
    if (ch == 'J')
        ch = 'I';
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (matrix[i][j] == ch)
            {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
void encrypt(char text[])
{
    int i, r1, c1, r2, c2;
    char a, b;
    for (i = 0; text[i] != '\0'; i += 2)
    {
        a = text[i];
        b = text[i + 1];
        findPosition(a, &r1, &c1);
        findPosition(b, &r2, &c2);
        if (r1 == r2)
        {
            text[i] = matrix[r1][(c1 + 1) % 5];
            text[i + 1] = matrix[r2][(c2 + 1) % 5];
        }
        else if (c1 == c2)
        {
            text[i] = matrix[(r1 + 1) % 5][c1];
            text[i + 1] = matrix[(r2 + 1) % 5][c2];
        }
        else
        {
            text[i] = matrix[r1][c2];
            text[i + 1] = matrix[r2][c1];
        }
    }
}
int main()
{
    char key[50], plaintext[100];
    int i, len;
    printf("Enter the keyword: ");
    scanf("%s", key);
    printf("Enter the plaintext: ");
    scanf("%s", plaintext);
    for (i = 0; plaintext[i] != '\0'; i++)
    {
        plaintext[i] = toupper(plaintext[i]);
        if (plaintext[i] == 'J')
            plaintext[i] = 'I';
    }
    len = strlen(plaintext);
    if (len % 2 != 0)
    {
        plaintext[len] = 'X';
        plaintext[len + 1] = '\0';
    }
    createMatrix(key);
    printf("\nPlayfair Matrix:\n");
    for (i = 0; i < 5; i++)
    {
        printf("%c %c %c %c %c\n",
               matrix[i][0], matrix[i][1], matrix[i][2],
               matrix[i][3], matrix[i][4]);
    }
    encrypt(plaintext);
    printf("\nEncrypted Text: %s\n", plaintext);
    return 0;
}