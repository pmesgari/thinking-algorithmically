// https://open.kattis.com/problems/cd

#include <stdio.h>
#include <stdlib.h>

#define SIZE 100000


typedef struct Node {
    int val;
    struct Node *next;
} Node;


void clear_hash_table(Node* hash_table[]) {
    int i;
    for (i = 0; i < SIZE; i++) {
        Node* current = hash_table[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
        hash_table[i] = NULL;
    }
}

void insert_cd(int cd_id, Node* hash_table[]) {
    int hash_id = cd_id % SIZE;
    printf("%p\n", &hash_table);
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(1);
    }

    // insert at the beginning of the linked list
    new_node->val = cd_id;
    new_node->next = hash_table[hash_id];
    hash_table[hash_id] = new_node;
}

int in_hash_table(Node* hash_table[], int cd_id) {
    int hash_id = cd_id % SIZE;
    printf("%p\n", &hash_table);

    Node* current;
    current = hash_table[hash_id];
    while(current) {
        if (current->val == cd_id) {
            return 1;
        }
        current = current->next;
    }

    return 0;
}


int main(void) {
    static Node* hash_table[SIZE] = {NULL};

    int n, m, i, j, val, bucket;
    
    while(scanf("%d %d", &n, &m) == 2 && ((m != 0) && (n != 0))) {
        clear_hash_table(hash_table);
        for(i = 0; i < n; i++) {
            int cd_id;
            scanf("%d", &cd_id);
            insert_cd(cd_id, hash_table);
        }
        int total = 0;
        for(i = 0; i < m; i++) {
            int cd_id;
            scanf("%d", &cd_id);
            if (in_hash_table(hash_table, cd_id)) {
                total++;
            }
        }
        printf("%d\n", total);
    }
    
    return 0;
}