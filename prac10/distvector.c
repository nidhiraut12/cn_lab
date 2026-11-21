
#include <stdio.h>

#define MAX_NODES 10
#define INF 9999

struct Node {
    int dist[MAX_NODES];
    int from[MAX_NODES];
} rt[MAX_NODES];

int main() {
    int cost[MAX_NODES][MAX_NODES];
    int nodes, i, j, k;
    int updated, iteration;

    printf("Enter number of nodes: ");
    scanf("%d", &nodes);

    if (nodes <= 0 || nodes > MAX_NODES) {
        printf("Invalid number of nodes.\n");
        return 1;
    }

    printf("Enter cost matrix row by row (use 9999 for INF/no connection):\n");

    for (i = 0; i < nodes; i++) {
        for (j = 0; j < nodes; j++) {
            scanf("%d", &cost[i][j]);

            if (cost[i][j] < 0) {
                printf("Invalid cost.\n");
                return 1;
            }
        }
    }

    // Initialize routing tables
    for (i = 0; i < nodes; i++) {
        for (j = 0; j < nodes; j++) {
            rt[i].dist[j] = cost[i][j];

            if (i == j)
                rt[i].from[j] = -1;
            else if (cost[i][j] < INF)
                rt[i].from[j] = j;
            else
                rt[i].from[j] = -1;
        }
    }

    // Distance Vector Routing Algorithm
    for (iteration = 0; iteration < nodes - 1; iteration++) {
        updated = 0;

        for (i = 0; i < nodes; i++) {
            for (j = 0; j < nodes; j++) {
                for (k = 0; k < nodes; k++) {

                    // Only directly connected neighbors
                    if (cost[i][k] >= INF)
                        continue;

                    if (rt[k].dist[j] >= INF)
                        continue;

                    int newdist = cost[i][k] + rt[k].dist[j];

                    if (newdist < rt[i].dist[j]) {
                        rt[i].dist[j] = newdist;
                        rt[i].from[j] = k;
                        updated = 1;
                    }
                }
            }
        }

        if (updated == 0)
            break;
    }

    // Display routing tables
    for (i = 0; i < nodes; i++) {
        printf("\nRouting table for Router %d:\n", i + 1);
        printf("Destination\tDistance\tNext Hop\n");

        for (j = 0; j < nodes; j++) {
            printf("%d\t\t", j + 1);

            if (rt[i].dist[j] >= INF) {
                printf("INF\t\t-");
            }
            else {
                printf("%d\t\t", rt[i].dist[j]);

                if (i == j)
                    printf("-");
                else
                    printf("%d", rt[i].from[j] + 1);
            }

            printf("\n");
        }
    }

    return 0;
}
