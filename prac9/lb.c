
#include <stdio.h>

int main() {
    int B, R, N;
    int P[100];
    int bucket = 0;
    int sent, dropped;
    int i;

    // Input
    printf("Enter bucket capacity B: ");
    scanf("%d", &B);

    printf("Enter outgoing rate R: ");
    scanf("%d", &R);

    printf("Enter number of time units N: ");
    scanf("%d", &N);

    if (B <= 0 || R <= 0 || N <= 0 || N > 100) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Enter incoming packets for each time unit:\n");
    for (i = 0; i < N; i++) {
        printf("P[%d] = ", i + 1);
        scanf("%d", &P[i]);

        if (P[i] < 0) {
            printf("Invalid packet count.\n");
            return 1;
        }
    }

    printf("\nTime\tIncoming\tAccepted\tDropped\tSent\tRemaining\n");
    printf("-------------------------------------------------------------\n");

    // Leaky Bucket Algorithm
    for (i = 0; i < N; i++) {

        // Check bucket overflow
        if (bucket + P[i] > B) {
            dropped = (bucket + P[i]) - B;
            bucket = B;
        }
        else {
            dropped = 0;
            bucket = bucket + P[i];
        }

        // Send packets at fixed outgoing rate
        if (bucket >= R)
            sent = R;
        else
            sent = bucket;

        bucket = bucket - sent;

        printf("%d\t%d\t\t%d\t\t%d\t%d\t%d\n",
               i + 1,
               P[i],
               P[i] - dropped,
               dropped,
               sent,
               bucket);
    }

    // Empty remaining packets
    while (bucket > 0) {
        i++;

        if (bucket >= R)
            sent = R;
        else
            sent = bucket;

        bucket = bucket - sent;

        printf("%d\t-\t\t-\t\t-\t%d\t%d\n",
               i, sent, bucket);
    }

    return 0;
}
