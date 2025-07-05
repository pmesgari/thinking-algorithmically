// https://atcoder.jp/contests/abc187/tasks/abc187_c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100000

typedef struct str_node {
    char str[12];
    struct str_node* next;
} str_node;

unsigned long hash(char* password) {
    unsigned long hash = 0, i;
    for (i = 0; i < strlen(password); i++)
        hash = hash * 26 + (password[i] - 'a');

    return hash % SIZE;
}

int in_hash_table(char* str, str_node* hash_table[]) {
    long hash_id = hash(str);
    str_node* current;
    current = hash_table[hash_id];
    while (current) {
        if (strcmp(current->str, str) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void insert_str(char* str, str_node* hash_table[]) {
    int hash_id;
    hash_id = hash(str);

    str_node* strnode;
    strnode = malloc(sizeof(str_node));
    if (strnode == NULL) {
        puts("malloc error");
        exit(1);
    }

    strcpy(strnode->str, str);
    strnode->next = hash_table[hash_id];
    hash_table[hash_id] = strnode;
}

char* negate_str(char* str) {
    size_t len = strlen(str);
    char* negated_s;

    if (str[0] == '!') {
        // Remove '!' prefix: !abc -> abc
        negated_s =
            (char*)malloc(len * sizeof(char));  // len-1 actual chars + '\0'
        if (negated_s == NULL) {
            exit(EXIT_FAILURE);
        }
        strcpy(negated_s, str + 1);
    } else {
        // Add '!' prefix: abc -> !abc
        negated_s =
            (char*)malloc((len + 2) * sizeof(char));  // '!' + len chars + '\0'
        if (negated_s == NULL) {
            exit(EXIT_FAILURE);
        }
        negated_s[0] = '!';
        strcpy(negated_s + 1, str);
    }
    return negated_s;
}

void print_hash_table(str_node* hash_table[]) {
    str_node* current;
    int i;
    printf("-----Begin Table------\n");
    for (i = 0; i < SIZE; i++) {
        current = hash_table[i];
        while (current) {
            printf("%d\n", i);

            printf("\tstr: %s\n", current->str);
            current = current->next;
        }
    }
    printf("-----End Table------\n\n");
}

char* get_base_form(char* s) {
    if (s[0] == '!') {
        return strdup(s + 1);
    }
    return strdup(s);
}

int main(void) {
    int n, i;
    char str[12];
    char* nstr;
    static str_node* hash_table[SIZE] = {NULL};

    scanf("%d\n", &n);
    for (i = 0; i < n; i++) {
        scanf("%s", str);
        nstr = negate_str(str);
        if (in_hash_table(nstr, hash_table)) {
            puts(get_base_form(nstr));
            return 0;
        }
        insert_str(str, hash_table);
        free(nstr);
    }
    printf("satisfiable");
    return 0;
}