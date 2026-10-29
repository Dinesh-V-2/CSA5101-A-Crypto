#include <stdio.h>
int main(void)
{
    int n = 3599;
    int e = 31;
    int p = 0, q = 0;
    int phi;
    int i;
    long long t = 0, newt = 1;
    long long r, newr;
    long long quotient, temp;
    for (i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            p = i;
            q = n / i;
            break;
        }
    }
    if (p == 0) {
        printf("The number n is prime.\n");
        return 1;
    }
    phi = (p - 1) * (q - 1);
    printf("RSA Public Key: (e, n) = (%d, %d)\n", e, n);
    printf("p = %d\n", p);
    printf("q = %d\n", q);
    printf("Phi(n) = %d\n", phi);
    r = phi;
    newr = e;
    while (newr != 0) {
        quotient = r / newr;
        temp = t;
        t = newt;
        newt = temp - quotient * newt;
        temp = r;
        r = newr;
        newr = temp - quotient * newr;
    }
    if (r != 1) {
        printf("Private key does not exist.\n");
        return 1;
    }
    if (t < 0)
        t += phi;
    printf("Private exponent d = %lld\n", t);
    printf("RSA Private Key: (d, n) = (%lld, %d)\n", t, n);
    return 0;
}
