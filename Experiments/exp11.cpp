#include <stdio.h>
#include <math.h>
int main()
{
    double totalKeys, uniqueKeys;
    double log2Total, log2Unique;
    totalKeys = tgamma(26);
    uniqueKeys = totalKeys / (25.0 * 24.0 * 2.0);
    log2Total = log(totalKeys) / log(2.0);
    log2Unique = log(uniqueKeys) / log(2.0);
    printf("Total possible keys = 25!\n");
    printf("Approximate power of 2 = 2^%.2f\n", log2Total);
    printf("\nEffectively unique keys = 25! / (25 * 24 * 2)\n");
    printf("Approximate power of 2 = 2^%.2f\n", log2Unique);

    return 0;
}
