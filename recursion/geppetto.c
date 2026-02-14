#include <stdio.h>

#define MAX_M 400

int is_valid(int iid, int* taken, int constraints[][MAX_M]) {
    int valid = 1;
    for (int i = 0; i < iid; i++) {
        // No constraints
        if (constraints[i][iid] == 0) {
            continue;
        }
        // Prohibited
        if (constraints[i][iid] == 1 && taken[i] == 1 && taken[iid] == 1) {
            valid = 0;
            break;
        }
    }

    return valid;
}

int solve(int ingredient_id, int N, int* taken, int constraints[][MAX_M]) {
    if (ingredient_id > N) {
        return 1;
    }
    int count = 0;

    // Skip it
    count += solve(ingredient_id + 1, N, taken, constraints);

    // Take it if valid
    taken[ingredient_id] = 1;

    if (is_valid(ingredient_id, taken, constraints)) {
        count += solve(ingredient_id + 1, N, taken, constraints);
    }

    taken[ingredient_id] = 0;

    return count;
}

int main(int argc, char* argv[]) {
    int N, M;
    int constraints[MAX_M][MAX_M];

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

    // Read N and M from whichever input source we selected
    fscanf(fin, "%d %d", &N, &M);

    // Initialize constraints
    for (int i = 0; i < MAX_M; i++) {
        for (int j = 0; j < MAX_M; j++) {
            constraints[i][j] = 0;
        }
    }

    // Read constraints
    for (int m = 0; m < M; m++) {
        int u, v;
        fscanf(fin, " %d %d", &u, &v);
        constraints[u][v] = 1;
        constraints[v][u] = 1;
    }

    // Close file if we opened one (optional for simple scripts, but good
    // practice)
    if (fin != stdin) {
        fclose(fin);
    }

    // Setup array (using N + 1 for 1-based indexing)
    int taken[N + 1];
    for (int n = 0; n < N + 1; n++) {
        taken[n] = 0;
    }

    // Solve
    int result = solve(1, N, taken, constraints);

    // Print to Standard Output
    printf("%d\n", result);

    return 0;
}