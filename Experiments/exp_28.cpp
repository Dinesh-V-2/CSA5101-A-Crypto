#include <stdio.h>
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
    long long q, a, x, y;
    long long A, B, keyAlice, keyBob;
    long long wrongA, wrongB;
    printf("Enter public prime q: ");
    if (scanf("%lld", &q) != 1 || q <= 2)
        return 1;
    printf("Enter public base a: ");
    if (scanf("%lld", &a) != 1 || a <= 1 || a >= q)
        return 1;
    printf("Enter Alice's secret number x: ");
    if (scanf("%lld", &x) != 1 || x <= 0)
        return 1;
    printf("Enter Bob's secret number y: ");
    if (scanf("%lld", &y) != 1 || y <= 0)
        return 1;
    A = modPow(a, x, q);
    B = modPow(a, y, q);
    keyAlice = modPow(B, x, q);
    keyBob = modPow(A, y, q);
    printf("\n--- Diffie-Hellman Key Exchange ---\n");
    printf("Alice sends A = a^x mod q = %lld\n", A);
    printf("Bob sends B = a^y mod q = %lld\n", B);
    printf("Alice's shared key = %lld\n", keyAlice);
    printf("Bob's shared key   = %lld\n", keyBob);
    if (keyAlice == keyBob)
        printf("Key exchange successful!\n");
    else
        printf("Key exchange failed.\n");
    wrongA = modPow(x, a, q);
    wrongB = modPow(y, a, q);
    printf("\n--- Alternative: Secret^a mod q ---\n");
    printf("Alice sends x^a mod q = %lld\n", wrongA);
    printf("Bob sends y^a mod q = %lld\n", wrongB);
    printf("This alternative does not generally produce a common key.\n");
    return 0;
}