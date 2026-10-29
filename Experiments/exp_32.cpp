#include <stdio.h>
#include <string.h>
#define P 23
#define Q 11
#define G 4
long long modPow(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}
long long hashMessage(const char *message) {
    long long h = 0;
    int i;
    for (i = 0; message[i] != '\0'; i++)
        h = (h + (unsigned char)message[i]) % Q;
    return h;
}
int modInverse(int a, int m) {
    int x;
    for (x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;
}
void dsaSign(long long h, int privateKey, int k,
             int *r, int *s) {
    int kinv;
    *r = modPow(G, k, P) % Q;
    kinv = modInverse(k, Q);
    *s = (int)((kinv * (h + privateKey * (*r))) % Q);
}
long long rsaSign(long long h, int d, int n) {
    return modPow(h, d, n);
}
int main(void) {
    char message[200];
    int privateKey = 3;
    int k1 = 2, k2 = 4;
    int r1, s1, r2, s2;
    int rsaD = 7, rsaN = 33;
    long long h;
    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';
    h = hashMessage(message);
    printf("\nMessage hash (demo only): %lld\n", h);
    dsaSign(h, privateKey, k1, &r1, &s1);
    dsaSign(h, privateKey, k2, &r2, &s2);
    printf("\nDSA demonstration:\n");
    printf("Signature 1: (r=%d, s=%d), k=%d\n", r1, s1, k1);
    printf("Signature 2: (r=%d, s=%d), k=%d\n", r2, s2, k2);
    printf("\nRSA textbook demonstration:\n");
    printf("Signature 1: %lld\n", rsaSign(h, rsaD, rsaN));
    printf("Signature 2: %lld\n", rsaSign(h, rsaD, rsaN));
    printf("\nConclusion:\n");
    printf("DSA signatures usually differ when fresh k values are used.\n");
    printf("Deterministic textbook RSA gives the same signature for the same message.\n");
    return 0;
}