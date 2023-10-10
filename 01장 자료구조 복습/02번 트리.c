#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node* left;
	struct Node* right;
}Node;

Node* makeNode(int data);
Node* findNode(Node* N, int data);
void connectNode(Node* N, int leftData, int rightData);
void search(Node* N, char* str);

int main() {
	int n;
	scanf("%d", &n);

	Node* N;

	for (int i = 0; i < n; i++) {
		int data, left, right;
		scanf("%d %d %d", &data, &left, &right);
		if (i == 0)
			N = makeNode(data);
		Node* tmp = findNode(N, data);
		connectNode(tmp, left, right);
	}

	int m;
	scanf("%d", &m);

	for (int i = 0; i < m; i++) {
		char str[101];
		scanf("%s", str);
		search(N, str);
		printf("\n");
	}
}

Node* makeNode(int data) {
	Node* N = (Node*)malloc(sizeof(Node));
	N->data = data;
	N->left = NULL;
	N->right = NULL;
}

Node* findNode(Node* N, int data) {
	if (N == NULL)
		return NULL;
	if (N->data == data)
		return N;

	Node* tmp = findNode(N->left, data);
	if (tmp != NULL)
		return tmp;
	return (findNode(N->right, data));
}

void connectNode(Node* N, int leftData, int rightData) {
	Node* left = makeNode(leftData);
	Node* right = makeNode(rightData);
	N->left = left;
	N->right = right;
}

void search(Node* N, char* str) {
	printf(" %d", N->data);
	if (*str == 'L')
		search(N->left, str + 1);
	else if (*str == 'R')
		search(N->right, str + 1);
}