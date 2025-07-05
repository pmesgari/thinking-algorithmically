// https://open.kattis.com/problems/shiritori

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100000
#define WORD_LENGTH 120
#define P 53

typedef struct word_node {
    char* word;
    struct word_node* next;
} word_node;

/*based on https://stackoverflow.com/questions/16870485 */
char* read_line(int size) {
    char* str;
    int ch;
    int len = 0;
    str = malloc(size);
    if (str == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(1);
    }
    while ((ch = getchar()) != EOF && (ch != '\n')) {
        str[len++] = ch;
        if (len == size) {
            size = size * 2;
            str = realloc(str, size);
            if (str == NULL) {
                fprintf(stderr, "realloc error\n");
                exit(1);
            }
        }
    }
    str[len] = '\0';
    return str;
}

unsigned long hash(char* word) {
    int i;
    unsigned long hash = 0;

    for (i = 0; i < strlen(word); i++) {
        hash = hash * P * i + (int)word[i];
    }

    return hash % SIZE;
}

void insert_word(char* word, word_node* hash_table[]) {
    int hash_id = hash(word);
    word_node* new_node = (word_node*)malloc(sizeof(word_node));
    if (new_node == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(1);
    }

    new_node->word = word;
    new_node->next = hash_table[hash_id];
    hash_table[hash_id] = new_node;
}

int in_hash_table(char* word, word_node* hash_table[]) {
    int hash_id = hash(word);

    word_node* current;
    current = hash_table[hash_id];
    while (current) {
        if (strcmp(current->word, word) == 0) {
            return 1;
        }
        current = current->next;
    }

    return 0;
}

void print_hash_table(word_node* hash_table[]) {
    word_node* current;
    int i;
    printf("-----Begin Table------\n");
    for (i = 0; i < SIZE; i++) {
        current = hash_table[i];
        while (current) {
            printf("%d\n", i);

            printf("\tword: %s\n", current->word);
            current = current->next;
        }
    }
    printf("-----End Table------\n\n");
}

int main(void) {
    int n, i, player;
    static word_node* hash_table[SIZE] = {NULL};

    scanf("%d\n", &n);
    char* current;
    char* previous = "\0";

    current = read_line(WORD_LENGTH);
    while (*current) {
        if (*previous) {
            if (current[0] != previous[strlen(previous) - 1]) {
                printf("Player %d lost\n", (i % 2 == 0) ? 1 : 2);
                return 0;
            }
            if (in_hash_table(current, hash_table)) {
                printf("Player %d lost\n", (i % 2 == 0) ? 1 : 2);
                return 0;
            }
        }
        insert_word(current, hash_table);
        previous = current;
        current = read_line(WORD_LENGTH);
        i++;
    }

    printf("Fair Game\n");
    return 0;
}
