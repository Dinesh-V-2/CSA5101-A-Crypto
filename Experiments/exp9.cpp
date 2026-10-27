#include <stdio.h>
#include <string.h>
#include <ctype.h>
char matrix[5][5];
void createMatrix(char key[]) {
    int used[26] = {0};
    int i, j, k = 0;
    char ch;
    used['J' - 'A'] = 1;
    for (i = 0; key[i] != '\0'; i++) {
        ch = toupper((unsigned char)key[i]);
        if (ch >= 'A' && ch <= 'Z') {
            if (ch == 'J')
                ch = 'I';
            if (!used[ch - 'A']) {
                matrix[k / 5][k % 5] = ch;
                used[ch - 'A'] = 1;
                k++;
            }
        }
    }
    for (ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            matrix[k / 5][k % 5] = ch;
            k++;
        }
    }
}
void findPosition(char ch, int *row, int *col) {
    int i, j;
    if (ch == 'J')
        ch = 'I';
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
void decrypt(char text[]) {
    int i, r1, c1, r2, c2;
    char a, b;
    printf("\nDecrypted text: ");
    for (i = 0; text[i] != '\0' && text[i + 1] != '\0'; i += 2) {
        a = toupper((unsigned char)text[i]);
        b = toupper((unsigned char)text[i + 1]);
        if (!isalpha((unsigned char)a) ||
            !isalpha((unsigned char)b))
            continue;
        findPosition(a, &r1, &c1);
        findPosition(b, &r2, &c2);
        if (r1 == r2) {
            c1 = (c1 + 4) % 5;
            c2 = (c2 + 4) % 5;
        } else if (c1 == c2) {
            r1 = (r1 + 4) % 5;
            r2 = (r2 + 4) % 5;
        } else {
            int temp = c1;
            c1 = c2;
            c2 = temp;
        }
        printf("%c%c", matrix[r1][c1], matrix[r2][c2]);
    }
    printf("\n");
}
int main() {
    char key[100];
    char text[] =
        "KXJEYUREBEZWEHEWRYTUHEYFS"
        "KREHEGOYFIWTTTUOLKSYCAJPO"
        "BOTEIZONTXBYBNTGONEYCUZWR"
        "GDSONSXBOUYWRHEBAAHYUSEDQ";
    printf("Enter Playfair keyword: ");
    fgets(key, sizeof(key), stdin);
    createMatrix(key);
    printf("\nPlayfair Key Matrix:\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++)
            printf("%c ", matrix[i][j]);
        printf("\n");
    }
    decrypt(text);

    return 0;
}
