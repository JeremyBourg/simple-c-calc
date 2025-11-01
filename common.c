#include "common.h"

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
