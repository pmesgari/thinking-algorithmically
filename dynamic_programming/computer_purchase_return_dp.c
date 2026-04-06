#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    int cost;
    struct Node* next;
} Node;

void print_dp_table(int B, int T, int dp[B + 1][T + 1]) {
    printf("\n--- DP Table ---\n");
    printf("Rows = Budget (0 to %d), Cols = Component Type (0 to %d)\n\n", B,
           T);

    // Print column headers
    printf("      |");
    for (int j = 0; j <= T; j++) {
        printf(" T=%-3d |", j);
    }
    printf("\n");

    // Print separator line
    printf("-------");
    for (int j = 0; j <= T; j++) {
        printf("--------");
    }
    printf("\n");

    // Print table body
    for (int i = 0; i <= B; i++) {
        printf("B=%-3d |", i);
        for (int j = 0; j <= T; j++) {
            if (dp[i][j] == -1) {
                printf("  --   |");  // Visual indicator for unreachable states
            } else {
                printf(" %4d  |", dp[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

int solve(int B, int T, Node* parts[], int dp[][T + 1]) {
    int i, j, ret, best_val;

    for (i = 1; i <= B; i++) {
        for (j = 1; j <= T; j++) {
            best_val = -1;
            Node* part = parts[j];
            while (part != NULL) {
                if (i - part->cost >= 0) {
                    if (dp[i - part->cost][j - 1] >= 0) {
                        ret = dp[i - part->cost][j - 1] + part->val;
                        if (ret < 0) {
                            part = part->next;
                            continue;
                        }
                        if (ret > best_val) {
                            best_val = ret;
                        }
                    }
                }
                part = part->next;
            }
            dp[i][j] = best_val;
        }
    }

    return dp[B][T];
}

int main(int argc, char* argv[]) {
    // 1. Default to Standard Input
    FILE* fin = stdin;

    // 2. If a filename is provided, open it
    if (argc > 1) {
        fin = fopen(argv[1], "r");
        if (fin == NULL) {
            printf("Error: Could not open %s\n", argv[1]);
            return 1;
        }
    }

    static Node* parts[1000] = {NULL};

    int i, j;
    int T, n, c, v, t, B;

    fscanf(fin, "%d", &T);
    fscanf(fin, "%d", &n);

    for (i = 0; i < n; i++) {
        fscanf(fin, "%d %d %d", &c, &v, &t);
        Node* new_node = (Node*)malloc(sizeof(Node));
        if (new_node == NULL) {
            fprintf(stderr, "malloc error\n");
            exit(1);
        }

        new_node->cost = c;
        new_node->val = v;
        new_node->next = parts[t];
        parts[t] = new_node;
    }

    fscanf(fin, "%d", &B);

    int dp[B + 1][T + 1];

    for (i = 0; i < B + 1; i++) {
        dp[i][0] = 0;
    }
    for (j = 0; j < T + 1; j++) {
        dp[0][j] = -1;
    }
    for (i = 1; i < B + 1; i++) {
        for (j = 1; j < T + 1; j++) {
            dp[i][j] = -1;
        }
    }
    dp[0][0] = 0;

    int result = solve(B, T, parts, dp);
    printf("%d\n", result);
    print_dp_table(B, T, dp);

    return 0;
}