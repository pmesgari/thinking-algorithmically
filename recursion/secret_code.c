#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int solve(char *s, int len) {
    int count = 0;
    if (len % 2 == 0 || len == 1) {
        return 0;
    }
    int sublen = (len + 1) / 2;
    int num_matches = 0;
    // S = parent + residue
    // Residue is prefix of parent
    if (strncmp(s, s + sublen, sublen - 1) == 0) {
        num_matches += 1;
    }
    // Residue is suffix of parent
    if (strncmp(s + 1, s + sublen, sublen - 1) == 0) {
        num_matches += 1;
    }
    // Count the parent
    if (num_matches > 0) {
        count += num_matches * (1 + solve(s, sublen));
    }

    num_matches = 0;
    // S = residue + parent
    // Residue is prefix of parent
    if (strncmp(s, s + sublen - 1, sublen - 1) == 0) {
        num_matches += 1;
    }
    // Residue is suffix of parent
    if (strncmp(s, s + sublen, sublen - 1) == 0) {
        num_matches += 1;
    }
    // Count the parent
    if (num_matches > 0) {
        count += num_matches * (1 + solve(s + sublen - 1, sublen));
    }

    return count;
}

int main(void) {
    // Open the input and output files
    FILE *in = fopen("scode.in", "r");
    FILE *out = fopen("scode.out", "w");

    if (!in || !out) {
        // Fallback to standard I/O if files are not present (for local testing)
        in = stdin;
        out = stdout;
    }

    char s[105];  // Buffer for the string (max length 100 + safety)

    // Read the string
    if (fscanf(in, "%s", s) == 1) {
        int result = solve(s, strlen(s));
        fprintf(out, "%d\n", result);
    }

    return 0;
}