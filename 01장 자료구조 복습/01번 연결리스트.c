#pragma warning(disable : 4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node {
	char data;
	struct Node* prev, * next;
}Node;

typedef struct List {
	Node* header;
	Node* trailer;
}List;

void initNode(List* L);
void addNode(List* L, int r, int e);
void deleteNode(List* L, int r);
char getNode(List* L, int r);
void print(List* L);

int main() {
	List L;
	initNode(&L);
	int n;
	scanf("%d", &n);
	getchar();
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		int r;
		char com, data;
		scanf("%c", &com);
		getchar();
		if (com == 'A') {
			scanf("%d %c", &r, &data);
			getchar();
			if (r > cnt + 1) {
				printf("invalid position");
				continue;
			}
			addNode(&L, r, data);
			cnt++;
		}
		if (com == 'D') {
			scanf("%d", &r);
			getchar();
			if (r > cnt) {
				printf("invalid position");
				continue;
			}
			deleteNode(&L, r);
			cnt--;
		}
		if (com == 'G') {
			scanf("%d", &r);
			getchar();
			if (r > cnt) {
				printf("invalid position");
				continue;
			}
			printf("%c", getNode(&L, r));
		}
		if (com == 'P') {
			print(&L);
		}
	}
}

void initNode(List* L) {
	L->header = (Node*)malloc(sizeof(Node));
	L->trailer = (Node*)malloc(sizeof(Node));
	L->header->next = L->trailer;
	L->trailer->prev = L->header;
}

void addNode(List* L, int r, int e) {
	Node* N = (Node*)malloc(sizeof(Node));
	N->data = e;
	N->prev = NULL;
	N->next = NULL;
	Node* tmp = L->header;
	for (int i = 1; i < r; i++) {
		tmp = tmp->next;
	}
	N->prev = tmp;
	N->next = tmp->next;
	tmp->next = N;
	N->next->prev = N;
}

void deleteNode(List* L, int r) {
	Node* N = L->header;
	for (int i = 0; i < r; i++) {
		N = N->next;
	}
	N->next->prev = N->prev;
	N->prev->next = N->next;
}

char getNode(List* L, int r) {
	Node* N = L->header;
	for (int i = 0; i < r; i++) {
		N = N->next;
	}
	return(N->data);
}

void print(List* L) {
	Node* N = L->header;
	while (1) {
		N = N->next;
		if (N == L->trailer) {
			break;
		}
		printf("%c", N->data);
	}
}
