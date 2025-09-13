#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT 100

typedef struct {
    int is_operator;
    union {
        char op;
        int value;
    };
} Token;

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void push(Node** head, int data) {
    Node* new = (Node*)malloc(sizeof(Node));

    if(new == NULL) {
        printf("Failed to allocate memory\n");
        return;
    }

    new->data = data;

    // If stack is empty, set the new node as the head
    if(*head == NULL){
        *head = new;
        return;
    }

    new->next = *head;
    *head = new;
}

int pop(Node** head) {
    if (*head == NULL) {
        printf("Stack underflow\n");
        return 0;
    }
    Node* popped = *head;
    int data = popped->data;
    *head = (*head)->next;
    free(popped);
    return data;
}

int main() {
    char input[MAX_INPUT];
    Token token_array[100];
    int token_count = 0;

    printf("Enter RPN expression:");
    fgets(input, MAX_INPUT, stdin);

    for (int i = 0; input[i] != '\0'; ) {
        if (isspace(input[i])) {
            i++;
            continue;
        }

        if (isdigit(input[i])) {
            int num = 0;
            while (isdigit(input[i])) {
                num = num * 10 + ((input[i]) - '0');
                i++;
            }
            token_array[token_count].is_operator = 0;
            token_array[token_count].value = num;
            token_count++;
            continue;
        }
        else {
            if (input[i] == '+') {
                token_array[token_count].is_operator = 1;
                token_array[token_count].op = '+';
            }
            else if (input[i] == '/') {
                token_array[token_count].is_operator = 1;
                token_array[token_count].op = '/';
            }
            else if (input[i] == '*') {
                token_array[token_count].is_operator = 1;
                token_array[token_count].op = '*';
            }
            else if (input[i] == '-') {
                token_array[token_count].is_operator = 1;
                token_array[token_count].op = '-';
            }
            else {
                printf("Invalid characters in input string, please use only '+', '-', '*' or '/'.\n");
                return 1;
            }
        }
        i++;
        token_count++;
    }
    token_array[token_count].is_operator = -1;

    Node* head = NULL;

    for (int i=0; token_array[i].is_operator != -1; ) {
        if (token_array[i].is_operator == 0) {
            push(&head, token_array[i].value);
        }
        else {
            if (token_array[i].op == '+') {
                int res = pop(&head) + pop(&head);
                push(&head, res);
            }
            else if (token_array[i].op == '-') {
                int b = pop(&head);
                int a = pop(&head);
                int res = a - b;
                push(&head, res);
            }
            else if (token_array[i].op == '*') {
                int res = pop(&head) * pop(&head);
                push(&head, res);
            }
            else if (token_array[i].op == '/') {
                int b = pop(&head);
                int a = pop(&head);
                if (!b){
                    printf("Cannot divide by 0\n");
                    return -1;
                }
                int res = a / b;
                push(&head, res);
            }
            else {
                printf("Error parsing tokens\n");
                return -1;
            }
        }
        i++;
    }

    if (head != NULL && head->next == NULL) {
        printf("Result: %d\n", head->data);
    }
    else {
        printf("Error evaluating expression\n");
    }
    return 0;
}
