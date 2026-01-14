#include <limits.h>
#include <stdio.h>

#define SIZE 12

int calc_skill_level(int* team_sum) {
    int i;
    int min = INT_MAX;
    int max = INT_MIN;
    for (i = 0; i < 4; i++) {
        if (team_sum[i] < min) {
            min = team_sum[i];
        }
        if (team_sum[i] > max) {
            max = team_sum[i];
        }
    }

    return max - min + 1;
}

int calc_min_diff(int* members, int* seen, int* team_sums, int group) {
    if (group == 4) {
        return calc_skill_level(team_sums);
    }
    int n, i, j, k, ret;
    int min_diff = INT_MAX;
    for (n = 0; n < SIZE; n++) {
        if (seen[n] == 0) {
            i = n;
            break;
        }
    }

    for (j = i + 1; j < SIZE - 1; j++) {
        for (k = j + 1; k < SIZE; k++) {
            if (seen[i] || seen[j] || seen[k]) {
                continue;
            }
            printf("Group %d: (%d, %d, %d)\n", group, i + 1, j + 1, k + 1);
            seen[i] = 1;
            seen[j] = 1;
            seen[k] = 1;
            team_sums[group] = members[i] + members[j] + members[k];
            ret = calc_min_diff(members, seen, team_sums, group + 1);
            if (ret < min_diff) {
                min_diff = ret;
            }
            seen[i] = 0;
            seen[j] = 0;
            seen[k] = 0;
            team_sums[group] = 0;
        }
    }
    return min_diff;
}

int main(void) {
    int nums[SIZE];
    int i;
    int seen[SIZE] = {0};
    int team_sums[4];

    // Open the input file
    FILE* fin = fopen("bteams.in", "r");
    if (fin == NULL) {
        printf("Error: Could not open bteams.in\n");
        return 1;
    }

    // Read the 12 integers
    for (i = 0; i < SIZE; i++) {
        fscanf(fin, "%d", &nums[i]);
    }
    fclose(fin);

    // Calculate result
    int result = calc_min_diff(nums, seen, team_sums, 0);

    // Open the output file
    FILE* fout = fopen("bteams.out", "w");
    fprintf(fout, "%d\n", result);
    fclose(fout);

    // Optional: Print to console so you can see it while running
    printf("Result written to bteams.out: %d\n", result);

    return 0;
}