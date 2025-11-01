#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int is_operator;
    union {
        char op;
        int value;
    };
} Token;

typedef struct Node {
    Token data;
    struct Node* next;
} Node;

void push(Node** head, Token data);
Token pop(Node** head);

#endif
