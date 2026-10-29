#include <stdio.h>
#include <string.h>
#define N 2
int mod26(int x) {
    return (x % 26 + 26) % 26;
}
int main() {
    char plain[100], cipher[100];
    int P[2][2], C[2][2];
    int K[2][2];
    int det, invDet;
    int i, j, k;
    printf("Enter known plaintext (4 letters): ");
    scanf("%4s", plain);
    printf("Enter corresponding ciphertext (4 letters): ");
    scanf("%4s", cipher);
    if (strlen(plain) != 4 || strlen(cipher) != 4) {
        printf("Enter exactly 4 letters for each string.\n");
        return 1;
    }
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            P[i][j] = plain[i * 2 + j] - 'A';
            C[i][j] = cipher[i * 2 + j] - 'A';
        }
    }
    det = mod26(P[0][0] * P[1][1]
              - P[0][1] * P[1][0]);
    invDet = -1;
    for (i = 0; i < 26; i++) {
        if (mod26(det * i) == 1) {
            invDet = i;
            break;
        }
    }
    if (invDet == -1) {
        printf("Cannot recover key: plaintext matrix is not invertible mod 26.\n");
        return 1;
    }
    int invP[2][2];
    invP[0][0] = mod26( P[1][1] * invDet);
    invP[0][1] = mod26(-P[0][1] * invDet);
    invP[1][0] = mod26(-P[1][0] * invDet);
    invP[1][1] = mod26( P[0][0] * invDet);
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            K[i][j] = 0;
            for (k = 0; k < 2; k++) {
                K[i][j] += C[i][k] * invP[k][j];
            }
            K[i][j] = mod26(K[i][j]);
        }
    }
    printf("\nRecovered Hill Cipher Key Matrix:\n");
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            printf("%d ", K[i][j]);
        }
        printf("\n");
    }
    return 0;
}