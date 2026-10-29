#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAX 2000
#define ALPHABET 26
const double englishFreq[26] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228,
    2.015, 6.094, 6.966, 0.153, 0.772, 4.025,
    2.406, 6.749, 7.507, 1.929, 0.095, 5.987,
    6.327, 9.056, 2.758, 0.978, 2.360, 0.150,
    1.974, 0.074
};
typedef struct {
    char text[MAX];
    double score;
    int key;
} Candidate;
void decryptText(const char cipher[], char plain[], int key)
{
    int i;
    for (i = 0; cipher[i] != '\0'; i++) {
        if (isupper((unsigned char)cipher[i])) {
            plain[i] = 'A' + (cipher[i] - 'A' - key + 26) % 26;
        } else if (islower((unsigned char)cipher[i])) {
            plain[i] = 'a' + (cipher[i] - 'a' - key + 26) % 26;
        } else {
            plain[i] = cipher[i];
        }
    }
    plain[i] = '\0';
}
double calculateScore(const char text[])
{
    int count[26] = {0};
    int total = 0;
    double score = 0.0;
    int i;
    for (i = 0; text[i] != '\0'; i++) {
        if (isalpha((unsigned char)text[i])) {
            count[toupper((unsigned char)text[i]) - 'A']++;
            total++;
        }
    }
    if (total == 0)
        return 1e9;
    for (i = 0; i < 26; i++) {
        double expected = englishFreq[i] * total / 100.0;
        double difference = count[i] - expected;
        if (expected > 0)
            score += difference * difference / expected;
    }
    return score;
}
int main(void)
{
    char cipher[MAX], plain[MAX];
    Candidate candidates[26];
    int topN, i, j;
    printf("Enter the ciphertext:\n");
    if (fgets(cipher, sizeof(cipher), stdin) == NULL)
        return 1;
    cipher[strcspn(cipher, "\n")] = '\0';
    printf("Enter the number of top plaintexts to display (1-26): ");
    if (scanf("%d", &topN) != 1 || topN < 1) {
        printf("Invalid number.\n");
        return 1;
    }
    if (topN > 26)
        topN = 26;
    for (i = 0; i < 26; i++) {
        decryptText(cipher, plain, i);
        strcpy(candidates[i].text, plain);
        candidates[i].score = calculateScore(plain);
        candidates[i].key = i;
    }
    for (i = 0; i < 25; i++) {
        for (j = i + 1; j < 26; j++) {
            if (candidates[j].score < candidates[i].score) {
                Candidate temp = candidates[i];
                candidates[i] = candidates[j];
                candidates[j] = temp;
            }
        }
    }
    printf("\nTop %d possible plaintexts:\n", topN);
    for (i = 0; i < topN; i++) {
        printf("\n%d. %s\n", i + 1, candidates[i].text);
        printf("   Shift: %d | Frequency score: %.2f\n",
               candidates[i].key, candidates[i].score);
    }
    return 0;
}