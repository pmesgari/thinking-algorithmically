#include <stdio.h>
#include <stdlib.h>

#define INITIAL_BUFFER_SIZE 16

char *read_line() {
    int c;
    size_t current_buffer_size = INITIAL_BUFFER_SIZE;
    size_t i = 0;
    char *word = malloc(current_buffer_size * sizeof(char));

    if (word == NULL) {
        perror("Memory allocation failed.");
    }

    while ((c = getchar()) != '\n' && c != EOF) {
        word[i++] = c;
        if (i == current_buffer_size) {
            current_buffer_size *= 2;
            char *temp = realloc(word, current_buffer_size * sizeof(char));
            if (temp == NULL) {
                perror("Memory reallocation failed.");
                free(word);
            }
            word = temp;
        }
    }

    word[i] = '\0';

    return word;
}

int main(void) {
    char *word;

    word = read_line();
    while (*word) {
        printf(word);
        word = read_line();
    }
}