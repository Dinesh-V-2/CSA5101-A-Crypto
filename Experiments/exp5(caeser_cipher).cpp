#include <stdio.h>
#include <string.h>
#include <ctype.h>

int gcd(int a, int b)
{
    while (b != 0)
    {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main()
{
    char text[100];
    int a, b, i;

    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter value of a: ");
    scanf("%d", &a);

    printf("Enter value of b: ");
    scanf("%d", &b);

    b = b % 26;

    if (gcd(a, 26) != 1)
    {
        printf("Invalid value of a!\n");
        printf("a must be coprime with 26.\n");
        printf("Allowed values: 1,3,5,7,9,11,15,17,19,21,23,25\n");
        return 0;
    }

    for (i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]))
        {
            char base = isupper(text[i]) ? 'A' : 'a';
            int p = text[i] - base;

            text[i] = ((a * p + b) % 26) + base;
        }
    }

    printf("Encrypted text: %s", text);

    return 0;
}