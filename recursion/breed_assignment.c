#include <stdio.h>
#include <string.h>

#define MAX_N 16

int is_valid(int cow_id, char* assignments, int constraints[][MAX_N]) {
    int valid = 1;
    for (int i = 0; i < cow_id; i++) {
        // No relation
        if (constraints[i][cow_id] == -1) {
            continue;
        }
        // Must be same
        if (constraints[i][cow_id] == 1 &&
            assignments[i] != assignments[cow_id]) {
            valid = 0;
            break;
        }
        // Must be different
        if (constraints[i][cow_id] == 0 &&
            assignments[i] == assignments[cow_id]) {
            valid = 0;
            break;
        }
    }
    return valid;
}

int count_assignments(char* assignments, char* breeds, int constraints[][MAX_N],
                      int cow_id, int N) {
    if (cow_id > N) {
        return 1;
    }

    int count = 0;

    for (int i = 0; i < 3; i++) {
        assignments[cow_id] = breeds[i];
        if (is_valid(cow_id, assignments, constraints)) {
            count += count_assignments(assignments, breeds, constraints,
                                       cow_id + 1, N);
        }
    }

    return count;
}

int main(void) {
    int N, K;
    char C;
    int constraints[MAX_N][MAX_N];

    // Open the input file
    FILE* fin = fopen("assign.in", "r");
    FILE* out = fopen("assign.out", "w");
    if (fin == NULL) {
        printf("Error: Could not open assign.in\n");
        return 1;
    }

    fscanf(fin, "%d %d", &N, &K);

    for (int i = 0; i < MAX_N; i++) {
        for (int j = 0; j < MAX_N; j++) {
            constraints[i][j] = -1;
        }
    }

    for (int k = 0; k < K; k++) {
        char type;
        int u, v;

        fscanf(fin, " %c %d %d", &type, &u, &v);

        int val = -1;
        if (type == 'S') {
            val = 1;
        } else {
            val = 0;
        }

        // Store in both directions so order doesn't matter
        constraints[u][v] = val;
        constraints[v][u] = val;
    }

    char assignments[MAX_N];

    int result = count_assignments(assignments, "HJG", constraints, 1, N);
    fprintf(out, "%d\n", result);
}