/**
Copyright 2019 TheEvilRoot
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
**/

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

typedef struct stacknode {
	int data;
	struct stacknode *next;
} Node;

Node * newNode(int data) {
	Node *n = (Node*) malloc(sizeof(Node));

	n->data = data;
	n->next = NULL;
	
	return n;
}

void push(Node **stack, int data) {
	Node *n = newNode(data);
	n->next = *stack;
	(*stack) = n;
}

int pop(Node **stack) {
	if ((*stack) == NULL) {
		return -1;
	}

	int popped = (*stack)->data;

	(*stack) = (*stack)->next;

	return popped;
}

int peek(Node *stack) {
	if (stack == NULL) {
		return -1;
	}

	return stack->data;
}

int findMin(Node *stack) {
	return stack->next == NULL ? stack->data : min(stack->data, findMin(stack->next));
}

int enterNumber(int *where) {
	cout << "Enter number: ";
	
	int result = scanf("%d", where) == 1;
	
	fflush(stdin);
	fseek(stdin, 0, SEEK_END);

	return result;
}

int search(Node *stack, int query, int i) {

	if (stack == NULL) {
		return -1;
	}

	if (stack->data == query) {
		return i + 1;
	}

	if (stack->next != NULL) {
		return search(stack->next, query, i + 1);
	} else {
		return -1;
	}

}

int search(Node *stack, int query) {
	return search(stack, query, 0);
}

void traverse(Node *stack) {
	if (stack == NULL) {
		cout << endl;
		return;
	}

	cout << stack->data << " ";
	traverse(stack->next);
}

int main() {
	Node *stack = NULL; // newNode(enterNumber(0));

	int num = 0;
	while (enterNumber(&num)) {
		if (stack == NULL) {
			stack = newNode(num);
		} else {
			push(&stack, num);
		}
	}

	if (stack == NULL) {
		cout << "Your stack is empty. Sorry" << endl;
	} else {
		cout << "Your stack: " << endl;
		traverse(stack);
		cout << endl;

		int min = findMin(stack);
	
		cout << "Min = " << min << endl;
		cout << search(stack, min) - 1 << " elements before min element in stack" << endl;	
	}
	cin.get();
	return 0;
}
