#include <ctype.h>
#include <stdio.h>

#define MAX_INPUT 100
#define MAX_STACK_SIZE 100

typedef struct {
    int is_operator;
    union {
        char op;
        int value;
    };
} Token;

typedef struct {
    int arr[MAX_STACK_SIZE];
    int top;
} Stack;

void initialize(Stack *stack) {
    stack->top = -1;
}

int pop(Stack *stack) {
    if (stack->top == -1) {
        printf("Stack underflow\n");
        return -1;
    }
    int popped = stack->arr[stack->top--];
    return popped;
}

void push(Stack *stack, int value) {
    if (stack->top == MAX_STACK_SIZE - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack->arr[++stack->top] = value;
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

    Stack stack;
    initialize(&stack);

    for (int i=0; token_array[i].is_operator != -1; ) {
        if (token_array[i].is_operator == 0) {
            push(&stack, token_array[i].value);
        }
        else {
            if (token_array[i].op == '+') {
                int res = pop(&stack) + pop(&stack);
                push(&stack, res);
            }
            else if (token_array[i].op == '-') {
                int b = pop(&stack);
                int a = pop(&stack);
                int res = a - b;
                push(&stack, res);
            }
            else if (token_array[i].op == '*') {
                int res = pop(&stack) * pop(&stack);
                push(&stack, res);
            }
            else if (token_array[i].op == '/') {
                int b = pop(&stack);
                int a = pop(&stack);
                int res = a / b;
                push(&stack, res);
            }
            else {
                perror("Error parsing tokens\n");
                return -1;
            }
        }
        i++;
    }

    if (stack.top == 0) {
        printf("Result: %d\n", stack.arr[stack.top]);
    }
    else {
        printf("Error evaluating expression\n");
    }
    return 0;
}
