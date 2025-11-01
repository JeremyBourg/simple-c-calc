#include <ctype.h>

#include "common.h"

#define MAX_INPUT 100

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
            token_array[token_count].is_operator = 1;
            token_array[token_count].op = input[i];
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
            if (head == NULL || head->next == NULL) {
                printf("Invalid expression\nErroneous token: %c\n", token_array[i].op);
                return -1;
            }

            int b = pop(&head).value;
            int a = pop(&head).value;

            if (token_array[i].op == '+') {
                push(&head, a + b);
            }
            else if (token_array[i].op == '-') {
                push(&head, a - b);
            }
            else if (token_array[i].op == '*') {
                push(&head, a * b);
            }
            else if (token_array[i].op == '/') {
                if (b == 0){
                    printf("Cannot divide by 0\n");
                    return -1;
                }
                push(&head, a / b);
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
	// Node* expr = NULL;
	//
	// while(output != NULL) {
	// 	push(&expr, pop(&output));
	// }
	//
	//    Node* head = NULL;
	//
	// while (expr != NULL) {
	//        if (expr->data.is_operator == 0) {
	//            push(&head, pop(&expr));
	//        }
	//        else {
	//            if (head == NULL) {
	//                printf("Invalid expression\nErroneous token: %c\n", pop(&expr).op);
	//                return -1;
	//            }
	// 		if (head->next == NULL) {
	// 			pop(&expr);
	// 			if(expr != NULL) {
	// 				printf("Invalid expression\nErroneous token: %c\n", pop(&expr).op);
	// 				return -1;
	// 			}
	// 			continue;
	// 		}
	//
	//            int b = pop(&head).value;
	//            int a = pop(&head).value;
	//
	//            if (expr->data.op == '+') {
	// 			Token res;
	// 			res.is_operator = 0;
	// 			res.value = a + b;
	//                push(&head, res);
	//            }
	//            else if (expr->data.op == '-') {
	// 			Token res;
	// 			res.is_operator = 0;
	// 			res.value = a - b;
	//                push(&head, res);
	//            }
	//            else if (expr->data.op == '*') {
	// 			Token res;
	// 			res.is_operator = 0;
	// 			res.value = a * b;
	//                push(&head, res);
	//            }
	//            else if (expr->data.op == '/') {
	//                if (b == 0){
	//                    printf("Cannot divide by 0\n");
	//                    return -1;
	//                }
	// 			Token res;
	// 			res.is_operator = 0;
	// 			res.value = a / b;
	//                push(&head, res);
	//            }
	//            else {
	//                printf("Error parsing tokens\n");
	//                return -1;
	//            }
	//        }
	//    }
	//
	//    if (head != NULL && head->next == NULL) {
	//        printf("Result: %d\n", head->data.value);
	//    }
	//    else {
	//        printf("Error evaluating expression\n");
	//    }
