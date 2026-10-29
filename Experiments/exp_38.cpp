 #include <stdio.h>
#define MOD 26
int mod(int x) {
    return (x % MOD + MOD) % MOD;
}
int modInverse(int a) {
    int i;
    a = mod(a);
    for (i = 1; i < MOD; i++) {
        if ((a * i) % MOD == 1)
            return i;
    }
    return -1;
}
int main(void) {
    int P[2][2], C[2][2];
    int Pinv[2][2], K[2][2];
    int det, invDet;
    int i, j, k;
    printf("Enter plaintext matrix P (2x2, values 0-25):\n");
    for (i = 0; i < 2; i++)
        for (j = 0; j < 2; j++)
            scanf("%d", &P[i][j]);
    printf("Enter corresponding ciphertext matrix C (2x2):\n");
    for (i = 0; i < 2; i++)
        for (j = 0; j < 2; j++)
            scanf("%d", &C[i][j]);
    for (i = 0; i < 2; i++)
        for (j = 0; j < 2; j++) {
            P[i][j] = mod(P[i][j]);
            C[i][j] = mod(C[i][j]);
        }
    det = mod(P[0][0] * P[1][1] - P[0][1] * P[1][0]);
    invDet = modInverse(det);
    if (invDet == -1) {
        printf("Attack failed: plaintext matrix is not invertible mod 26.\n");
        return 1;
    }
    Pinv[0][0] = mod(P[1][1] * invDet);
    Pinv[0][1] = mod(-P[0][1] * invDet);
    Pinv[1][0] = mod(-P[1][0] * invDet);
    Pinv[1][1] = mod(P[0][0] * invDet);
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            K[i][j] = 0;
            for (k = 0; k < 2; k++)
                K[i][j] += C[i][k] * Pinv[k][j];
            K[i][j] = mod(K[i][j]);
        }
    }
    printf("\nRecovered Hill cipher key matrix K:\n");
    for (i = 0; i < 2; i++)
        printf("%d %d\n", K[i][0], K[i][1]);
    return 0;
}