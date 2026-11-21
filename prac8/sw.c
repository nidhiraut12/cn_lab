
#include <stdio.h>

int main() {
    int n, window, i, j;
    int ack;

    printf("Enter number of frames: ");
    scanf("%d", &n);

    printf("Enter window size: ");
    scanf("%d", &window);

    if (n <= 0 || window <= 0) {
        printf("Invalid input.\n");
        return 1;
    }

    i = 0;

    while (i < n) {
        printf("\nSending frames: ");

        for (j = i; j < i + window && j < n; j++) {
            printf("%d ", j + 1);
        }

        printf("\nEnter last acknowledged frame (0 if none): ");
        scanf("%d", &ack);

        if (ack == 0) {
            printf("No acknowledgement received.\n");
            printf("Go-Back-N: Retransmitting frames from %d\n", i + 1);
        }
        else if (ack >= i + 1 && ack <= j) {
            printf("Acknowledgement received for frame %d\n", ack);
            i = ack;

            if (i < n) {
                printf("Sliding window forward...\n");
            }
        }
        else {
            printf("Invalid acknowledgement.\n");
        }
    }

    printf("\nAll frames transmitted successfully.\n");

    return 0;
}
