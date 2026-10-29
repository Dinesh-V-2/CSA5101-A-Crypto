#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 200
long long modPow(long long base, long long exp, long long mod)
{
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2)
            result = (result * base) % mod;

        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}
int main(void)
{
    char message[MAX];
    long long e, n;
    printf("Enter plaintext (letters only): ");
    if (fgets(message, sizeof(message), stdin) == NULL)
        return 1;
    printf("Enter public exponent e: ");
    if (scanf("%lld", &e) != 1 || e <= 0)
        return 1;
    printf("Enter modulus n (greater than 25): ");
    if (scanf("%lld", &n) != 1 || n <= 25)
        return 1;
    printf("\nCharacter  Number  Ciphertext\n");
    printf("-----------------------------\n");
    for (int i = 0; message[i] != '\0'; i++) {
        if (isalpha((unsigned char)message[i])) {
            int m = toupper((unsigned char)message[i]) - 'A';
            long long c = modPow(m, e, n);

            printf("%9c  %6d  %10lld\n",
                   toupper((unsigned char)message[i]), m, c);
        }
    }
    printf("\nSecurity observation:\n");
    printf("Every occurrence of the same letter produces the same ciphertext.\n");
    printf("This leaks letter patterns and enables frequency analysis.\n");
    return 0;
}