#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAX 5000
#define ALPHABET 26
double englishFreq[26] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228,
    2.015, 6.094, 6.966, 0.153, 0.772, 4.025,
    2.406, 6.749, 7.507, 1.929, 0.095, 5.987,
    6.327, 9.056, 2.758, 0.978, 2.360, 0.150,
    1.974, 0.074
};
typedef struct {
    char text[MAX];
    double score;
} Candidate;
int main(void) {
    char cipher[MAX];
    int count[26] = {0};
    int order[26];
    int map[26];
    int total = 0, topN, i, j;
    Candidate candidates[26];
    printf("Enter ciphertext:\n");
    if (!fgets(cipher, sizeof(cipher), stdin))
        return 1;
    cipher[strcspn(cipher, "\n")] = '\0';
    printf("How many possible plaintexts do you want? ");
    if (scanf("%d", &topN) != 1 || topN < 1) {
        printf("Invalid number.\n");
        return 1;
    }
    for (i = 0; cipher[i] != '\0'; i++) {
        if (isalpha((unsigned char)cipher[i])) {
            count[toupper((unsigned char)cipher[i]) - 'A']++;
            total++;
        }
    }
    if (total == 0) {
        printf("Ciphertext contains no letters.\n");
        return 1;
    }
    for (i = 0; i < 26; i++)
        order[i] = i;

    for (i = 0; i < 25; i++) {
        for (j = i + 1; j < 26; j++) {
            if (count[order[j]] > count[order[i]]) {
                int temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }
    for (int shift = 0; shift < 26; shift++) {
        char plainOrder[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
        for (i = 0; i < 26; i++) {
            int plainIndex = (i + shift) % 26;
            map[order[i]] = plainOrder[plainIndex];
        }
        for (i = 0; cipher[i] != '\0'; i++) {
            if (isalpha((unsigned char)cipher[i])) {
                int c = toupper((unsigned char)cipher[i]) - 'A';
                candidates[shift].text[i] = map[c];
            } else {
                candidates[shift].text[i] = cipher[i];
            }
        }
        candidates[shift].text[i] = '\0';
        {
            int plainCount[26] = {0};
            double score = 0.0;
            for (i = 0; candidates[shift].text[i] != '\0'; i++) {
                if (isalpha((unsigned char)candidates[shift].text[i]))
                    plainCount[toupper((unsigned char)candidates[shift].text[i]) - 'A']++;
            }
            for (i = 0; i < 26; i++) {
                double observed = 100.0 * plainCount[i] / total;
                double diff = observed - englishFreq[i];
                score += diff * diff;
            }
            candidates[shift].score = score;
        }
    }
    for (i = 0; i < 26; i++) {
        for (j = i + 1; j < 26; j++) {
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
        printf("\n%d. Score: %.2f\n%s\n",
               i + 1, candidates[i].score, candidates[i].text);
    }
    return 0;
}