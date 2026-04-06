#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    int cost;
    struct Node* next;
} Node;

int solve(int b, int i, int T, Node* parts[], int memo[][T]) {
    if (b < 0) {
        return -1;
    }

    if (i == T + 1) {
        return 0;
    }

    if (memo[b][i] > 0) {
        return memo[b][i];
    }

    int best_val = -1;
    int ret;
    Node* part = parts[i];
    while (part != NULL) {
        ret = solve(b - part->cost, i + 1, T, parts, memo);
        if (ret < 0) {
            part = part->next;
            continue;
        }
        if ((ret + part->val) > best_val) {
            best_val = ret + part->val;
        }

        part = part->next;
    }
    if (best_val > 0) {
        memo[b][i] = best_val;
    }
    return best_val;
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
    int memo[3000][5];
    for (int i = 0; i < 3000; i++) {
        for (int j = 0; j < 5; j++) {
            memo[i][j] = -1;
        }
    }

    int i, T, N, c, v, t, B;

    fscanf(fin, "%d", &T);
    fscanf(fin, "%d", &N);

    for (i = 0; i < N; i++) {
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

    int result = solve(B, 1, T, parts, memo);
    printf("%d\n", result);

    return 0;
}