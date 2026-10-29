#include <stdio.h>
long long gcd(long long a, long long b)
{
    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}
long long modInverse(long long e, long long phi)
{
    long long t = 0, newT = 1;
    long long r = phi, newR = e;
    while (newR != 0) {
        long long q = r / newR;
        long long temp = t - q * newT;
        t = newT;
        newT = temp;
        temp = r - q * newR;
        r = newR;
        newR = temp;
    }
    if (r != 1)
        return -1;
    t %= phi;
    if (t < 0)
        t += phi;
    return t;
}
int main(void)
{
    long long p, q, n, phi;
    long long oldE, oldD, newE, newD;
    printf("Enter prime p: ");
    scanf("%lld", &p);
    printf("Enter prime q: ");
    scanf("%lld", &q);
    n = p * q;
    phi = (p - 1) * (q - 1);
    printf("Enter leaked private key d: ");
    scanf("%lld", &oldD);
    printf("Enter new public exponent e: ");
    scanf("%lld", &newE);
    newD = modInverse(newE, phi);
    if (newD == -1) {
        printf("Invalid public exponent. Choose e coprime to phi(n).\n");
        return 1;
    }
    printf("\nRSA Key Analysis\n");
    printf("----------------\n");
    printf("Modulus n = %lld\n", n);
    printf("phi(n) = %lld\n", phi);
    printf("Leaked private key d = %lld\n", oldD);
    printf("New public key = (%lld, %lld)\n", newE, n);
    printf("New private key = (%lld, %lld)\n", newD, n);
    printf("\nSecurity analysis:\n");
    printf("The modulus n has been reused.\n");
    printf("If the attacker knows p and q, the attacker can calculate phi(n)\n");
    printf("and derive the private exponent for the new public exponent.\n");
    printf("Therefore, replacing only e and d is not a safe recovery method.\n");
    return 0;
}