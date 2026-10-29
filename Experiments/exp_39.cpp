#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 5000
double englishFreq[26] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228,
    2.015, 6.094, 6.966, 0.153, 0.772, 4.025,
    2.406, 6.749, 7.507, 1.929, 0.095, 5.987,
    6.327, 9.056, 2.758, 0.978, 2.360, 0.150,
    1.974, 0.074
};
typedef struct {
    int key;
    double score;
    char text[MAX];
} Candidate;
int main(void) {
    char cipher[MAX];
    int topN, i, k, count, total = 0;
    Candidate candidates[26];
    printf("Enter ciphertext:\n");
    if (!fgets(cipher, sizeof(cipher), stdin))
        return 1;
    cipher[strcspn(cipher, "\n")] = '\0';
    printf("How many possible plaintexts? ");
    if (scanf("%d", &topN) != 1 || topN < 1) {
        printf("Invalid number.\n");
        return 1;
    }
    for (k = 0; k < 26; k++) {
        int freq[26] = {0};
        count = 0;
        for (i = 0; cipher[i] != '\0'; i++) {
            if (isalpha((unsigned char)cipher[i])) {
                int c = toupper((unsigned char)cipher[i]) - 'A';
                int p = (c - k + 26) % 26;
                candidates[k].text[i] = (char)('A' + p);
                freq[p]++;
                count++;
            } else {
                candidates[k].text[i] = cipher[i];
            }
        }
        candidates[k].text[i] = '\0';
        candidates[k].key = k;
        candidates[k].score = 0.0;
        if (count > 0) {
            for (i = 0; i < 26; i++) {
                double expected = englishFreq[i] * count / 100.0;
                double diff = freq[i] - expected;

                if (expected > 0)
                    candidates[k].score += diff * diff / expected;
            }
        }
    }
    for (i = 0; i < 25; i++) {
        for (int j = i + 1; j < 26; j++) {
            if (candidates[j].score < candidates[i].score) {
                Candidate temp = candidates[i];
                candidates[i] = candidates[j];
                candidates[j] = temp;
            }
        }
    }
    if (topN > 26)
        topN = 26;
    printf("\nTop %d possible plaintexts:\n", topN);
    for (i = 0; i < topN; i++) {
        printf("\n%d. Key = %d, Score = %.2f\n%s\n",
               i + 1,
               candidates[i].key,
               candidates[i].score,
               candidates[i].text);
    }
    return 0;
}