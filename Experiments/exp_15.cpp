#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 1000
double freq[26] = {
    8.12, 1.49, 2.71, 4.32, 12.02, 2.30, 2.03,
    5.92, 7.31, 0.10, 0.69, 3.98, 2.61, 6.95,
    7.68, 1.82, 0.11, 6.02, 6.28, 9.10, 2.88,
    1.11, 2.09, 0.17, 2.11, 0.07
};
typedef struct {
    int key;
    double score;
    char text[MAX];
} Candidate;
void decrypt(char cipher[], char plain[], int key) {
    int i;
    for (i = 0; cipher[i] != '\0'; i++) {
        if (isalpha((unsigned char)cipher[i])) {
            char base = isupper((unsigned char)cipher[i])
                        ? 'A' : 'a';
            plain[i] = (cipher[i] - base - key + 26) % 26 + base;
        } else {
            plain[i] = cipher[i];
        }
    }
    plain[i] = '\0';
}
double calculateScore(char text[]) {
    int count[26] = {0};
    int total = 0, i;
    double score = 0.0;

    for (i = 0; text[i] != '\0'; i++) {
        if (isalpha((unsigned char)text[i])) {
            count[tolower((unsigned char)text[i]) - 'a']++;
            total++;
        }
    }
    if (total == 0)
        return 0.0;
    for (i = 0; i < 26; i++) {
        double observed = (double)count[i] / total * 100.0;
        double difference = observed - freq[i];
        score += difference * difference;
    }
    return score;
}
int main() {
    char cipher[MAX], plain[MAX];
    Candidate candidates[26], temp;
    int top, i, j;
    printf("Enter ciphertext: ");
    fgets(cipher, MAX, stdin);
    cipher[strcspn(cipher, "\n")] = '\0';
    printf("How many top plaintexts do you want (1-26)? ");
    if (scanf("%d", &top) != 1 || top < 1 || top > 26) {
        printf("Invalid number. Enter a value from 1 to 26.\n");
        return 1;
    }
    for (i = 0; i < 26; i++) {
        candidates[i].key = i;
        decrypt(cipher, plain, i);
        strcpy(candidates[i].text, plain);
        candidates[i].score = calculateScore(plain);
    }
    for (i = 0; i < 25; i++) {
        for (j = i + 1; j < 26; j++) {
            if (candidates[j].score < candidates[i].score) {
                temp = candidates[i];
                candidates[i] = candidates[j];
                candidates[j] = temp;
            }
        }
    }
    printf("\nTop %d possible plaintexts:\n", top);
    for (i = 0; i < top; i++) {
        printf("%d. Key = %d | Score = %.2f\n",
               i + 1, candidates[i].key,
               candidates[i].score);
        printf("   %s\n", candidates[i].text);
    }
    return 0;
}
