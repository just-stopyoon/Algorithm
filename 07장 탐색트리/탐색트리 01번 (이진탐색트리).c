#pragma warning(disable : 4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct treeNode {
	int key;
	struct treeNode* parent;
	struct treeNode* left;
	struct treeNode* right;
}treeNode;

typedef struct Root {
	treeNode* root;
}Root;

void initTree(Root* T) {
	treeNode* root = (treeNode*)malloc(sizeof(treeNode));
	root->left = NULL;
	root->right = NULL;
	root->parent = NULL;
	T->root = root;
}

int isExternal(treeNode* w) {
	return (w->left == NULL || w->right == NULL);
}

int isInternal(treeNode* w) {
	return (w->left != NULL && w->right != NULL);
}

treeNode* treeSearch(treeNode* v, int k) {
	if (isExternal(v))
		return v;
	if (k == v->key)
		return v;
	else if (k < v->key)
		return treeSearch(v->left, k);
	else if (k > v->key)
		return treeSearch(v->right, k);
}

void expandExternal(treeNode* w) {
	treeNode* Left = (treeNode*)malloc(sizeof(treeNode));
	treeNode* Right = (treeNode*)malloc(sizeof(treeNode));

	//좌 자식노드 초기화
	Left->left = NULL;
	Left->right = NULL;
	Left->parent = w;

	//우 자식노드 초기화
	Right->left = NULL;
	Right->right = NULL;
	Right->parent = w;

	w->left = Left; //좌 자식 연결
	w->right = Right; //우 자식 연결
}

void insertItem(Root* T, int key) {
	treeNode* w = treeSearch(T->root, key);
	if (isInternal(w))
		return;
	else {
		w->key = key;
		expandExternal(w);
	}
}

treeNode* sibling(treeNode* z) {
	if (z->parent->left == z)
		return z->parent->right;
	else if (z->parent->right == z)
		return z->parent->left;
}

void reduceExternal(Root* T, treeNode * z) {
	treeNode* w = z->parent;
	treeNode* zs = sibling(z);
	if (T->root == w) {
		T->root = zs;
		zs->parent = NULL;
	}
	else {
		treeNode* g = w->parent;
		zs->parent = g;
		if (w == g->left)
			g->left = zs;
		else if (w == g->right)
			g->right = zs;
	}
	free(z);
	free(w);
}

treeNode* inOrderSucc(treeNode* w) {
	w = w->right;

	while (isInternal(w->left) == 1)
		w = w->left;
	return w;
}

int removeElement(Root* T, int key) {
	treeNode* w = treeSearch(T->root, key);
	if (isExternal(w))
		return 0;
	int e = w->key;

	treeNode* z = w->left;

	if (isInternal(z))
		z = w->right;
	if (isExternal(z))
		reduceExternal(T, z);
	else {
		treeNode* y = inOrderSucc(w);
		z = y->left;
		w->key = y->key;
		reduceExternal(T, z);
	}
	return e;
}

int findElement(Root* T, int key) {
	treeNode* w = treeSearch(T->root, key);
	if (isExternal(w))
		return 0;
	else
		return w->key;
}

void preOrder(treeNode* p) {
	if (isExternal(p))
		return;
	printf(" %d", p->key);
	preOrder(p->left);
	preOrder(p->right);
}

void print(Root* T) {
	preOrder(T->root);
	printf("\n");
}

int main() {
	Root T;
	initTree(&T);
	char c;
	int key;

	while (1) {
		scanf("%c", &c);
		if (c == 'i') {
			scanf("%d", &key);
			insertItem(&T, key);
		}
		else if (c == 'd') {
			scanf("%d", &key);
			int e = removeElement(&T, key);
			if (e)
				printf("%d\n", e);
			else
				printf("X\n");
		}
		else if (c == 's') {
			scanf("%d", &key);
			int e = findElement(&T, key);
			if (e)
				printf("%d\n", e);
			else
				printf("X\n");
		}
		else if (c == 'p') {
			print(&T);
		}
		else if (c == 'q')
			break;
		getchar();
	}
}