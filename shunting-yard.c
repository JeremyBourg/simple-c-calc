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
    Token data;
    struct Node* next;
} Node;

int is_empty(Node** head) { return *head == NULL; }

void push(Node** head, Token data) {
    Node* new = malloc(sizeof(Node));

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

Token pop(Node** head) {
    Node* popped = *head;
    Token data = popped->data;
    *head = (*head)->next;
    free(popped);
    return data;
}

int precedence(char operator) {
    if(operator == '+' || operator == '-') {
        return 1;
    }
    else if(operator == '*' || operator == '/') {
        return 2;
    }
    else if(operator == '^') {
        return 3;
    }

    return -1;
}

// Returns true if both operators have the same precedence or if o2 has greater precendence than o1
int precedencecmp(char o1, char o2) {
    int o1_p = precedence(o1);
    int o2_p = precedence(o2);

    if (o1_p == -1 || o2_p == -1) {
        printf("Error calculating precedence\n");
        return 0;
    }

    if(o1_p <= o2_p) {
        return 1;
    }
    return 0;
}

int main() {
    char input[MAX_INPUT];
    Token token_array[MAX_INPUT];
    int token_count = 0;

    Node* output = NULL;
    Node* operators = NULL;

    printf("Enter expression:");
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
            token_array[token_count].is_operator = 1;
            token_array[token_count].op = input[i];
        }
        i++;
        token_count++;
    }

	if (token_count == 0) {
		printf("Empty expression\n");
		return 0;
	}

    for(int i=0; i<token_count; i++) {
        if (token_array[i].is_operator == 0) {
            push(&output, token_array[i]);
        }
        else if (token_array[i].op == '(') {
            push(&output, token_array[i]);
        }
        else if (token_array[i].op == ')') {
            while (operators->data.op != '(') {
                if (is_empty(&operators)) {
                    printf("Mismatched parentheses\n");
                    return 1;
                }
                Token t = pop(&operators);
                push(&output, t);
            }
            if (operators->data.op == '(') {
                pop(&operators);
            }
            else {
                printf("Error parsing tokens\n");
                return 1;
            }
        }
        else {
			while (operators != NULL && operators->data.op != '(' && precedencecmp(token_array[i].op, operators->data.op) == 1) {
				Token t = pop(&operators);
				push(&output, t);
			}
            push(&operators, token_array[i]);
        }
    }
    while(operators != NULL) {
        if (operators->data.op == '(' || operators->data.op == ')') {
            printf("Mismatched parentheses\n");
            return 1;
        }
        Token t = pop(&operators);
        push(&output, t);
    }

	Node* expr = NULL;

	while(output != NULL) {
		push(&expr, pop(&output));
	}

    Node* head = NULL;

	while (expr != NULL) {
        if (expr->data.is_operator == 0) {
            push(&head, pop(&expr));
        }
        else {
            if (head == NULL) {
                printf("Invalid expression\nErroneous token: %c\n", pop(&expr).op);
                return -1;
            }
			if (head->next == NULL) {
				pop(&expr);
				if(expr != NULL) {
					printf("Invalid expression\nErroneous token: %c\n", pop(&expr).op);
					return -1;
				}
				continue;
			}

            int b = pop(&head).value;
            int a = pop(&head).value;

            if (expr->data.op == '+') {
				Token res;
				res.is_operator = 0;
				res.value = a + b;
                push(&head, res);
            }
            else if (expr->data.op == '-') {
				Token res;
				res.is_operator = 0;
				res.value = a - b;
                push(&head, res);
            }
            else if (expr->data.op == '*') {
				Token res;
				res.is_operator = 0;
				res.value = a * b;
                push(&head, res);
            }
            else if (expr->data.op == '/') {
                if (b == 0){
                    printf("Cannot divide by 0\n");
                    return -1;
                }
				Token res;
				res.is_operator = 0;
				res.value = a / b;
                push(&head, res);
            }
            else {
                printf("Error parsing tokens\n");
                return -1;
            }
        }
    }

    if (head != NULL && head->next == NULL) {
        printf("Result: %d\n", head->data.value);
    }
    else {
        printf("Error evaluating expression\n");
    }
    return 0;
}
