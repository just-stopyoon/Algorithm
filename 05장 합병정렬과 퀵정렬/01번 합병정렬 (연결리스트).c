#pragma warning(disable : 4996)
#include<stdio.h>
#include<stdlib.h>

typedef struct listNode {
	int element;
	struct List* next;
}listNode;

typedef struct listType {
	listNode* header;
}listType;

void init(listType* L);
int size(listType* L);
void push(listType* L, int element);
int pop(listType* L);

void mergeSort(listType* L);
void merge(listType* L1, listType* L2);
listType* partition(listType* L, int k);

void printList(listType* L);

int main() {
	listType* L = (listType*)malloc(sizeof(listType));
	int n;
	scanf("%d", &n);

	init(L);

	for (int i = 0; i < n; i++) {
		int element;
		scanf("%d", &element);
		push(L, element);
	}

	mergeSort(L);
	printList(L);
}

void init(listType* L) {
	L->header = NULL;
}

int size(listType* L) {
	int s = 0;
	listNode* p = L->header;

	while (p) {
		p = p->next;
		s++;
	}
	return s;
}

void push(listType* L, int element) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->element = element;
	node->next = NULL;

	listNode* p = L->header;

	if (!p) {
		L->header = node;
	}
	else {
		while (p->next) {
			p = p->next;
		}
		p->next = node;
	}
}
int pop(listType* L) {
	int element = L->header->element;
	listNode* p = L->header;

	L->header = p->next;
	free(p);

	return element;
}

void mergeSort(listType* L) {
	if (size(L) > 1) {
		listType* L1 = partition(L, size(L) / 2);
		mergeSort(L);
		mergeSort(L1);
		merge(L, L1);
	}
}

void merge(listType* L1, listType* L2) {
	listType* tmp = (listType*)malloc(sizeof(listType));
	init(tmp);

	while (L1->header && L2->header) {
		if (L1->header->element < L2->header->element) {
			push(tmp, pop(L1));
		}
		else {
			push(tmp, pop(L2));
		}
	}

	while (L1->header) {
		push(tmp, pop(L1));
	}
	while (L2->header) {
		push(tmp, pop(L2));
	}
	while (tmp->header) {
		push(L1, pop(tmp));
	}
}

listType* partition(listType* L, int k) {
	listType* list = (listType*)malloc(sizeof(listType));
	init(list);

	for (int i = 0; i < k; i++) {
		push(list, pop(L));
	}
	return list;
}

void printList(listType* L) {
	for (listNode* p = L->header; p; p = p->next) {
		printf(" %d", p->element);
	}
	printf("\n");
}