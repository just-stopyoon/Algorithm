#pragma warning(disable : 4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct Node {
	int key;
	struct Node* parent;
	struct Node* left;
	struct Node* right;
}Node;

typedef struct Root {
	Node* root;
}Root;

void initTree(Root *T);
int findElement(Root *T, int k);
Node* treeSearch(Node* v, int k);
int isExternal(Node* w);
int isInternal(Node* w);
void insertItem(Root* T, int k);
void expandExternal(Node* w);
int removeElement(Root* T, int k);
void reduceExternal(Root* T, Node *z);
Node* inOrderSucc(Node* w);
Node* sibling(Node* z);

void print(Root* T);
void preOrder(Node* p);

int NoSuchKey = 0;

int main() {
	Root T;
	initTree(&T); //루트노드 생성
	char c;
	int k;
	
	while (1) {
		scanf("%c", &c);
		if (c == 'i') {
			scanf("%d", &k);
			insertItem(&T, k);
		}
		else if (c == 'd') {
			scanf("%d", &k);
			int e = removeElement(&T, k);
			if (e)
				printf("%d\n", e);
			else
				printf("X\n");
		}
		else if (c == 's') {
			scanf("%d", &k);
			int e = findElement(&T, k);
			if (e)
				printf("%d\n", e);
			else
				printf("X\n");
		}
		else if (c == 'p')
			print(&T);
		else if (c == 'q')
			break;
		getchar();
	}
}

void initTree(Root *T) {
	Node* root = (Node*)malloc(sizeof(Node)); //루트 노드 생성
	//루트 노드 초기화
	root->left = NULL;
	root->right = NULL;
	root->parent = NULL;
	T->root = root; //루트 노드 연결
}

int findElement(Root *T, int k) {
	Node* w = treeSearch(T->root, k);
	if (isExternal(w)) //없을 경우
		return NoSuchKey; //key 값 없음
	else //외부노드가 아닐 경우 (찾았을 경우))
		return w->key; //찾은 w의 key값 반환
}

Node* treeSearch(Node* v, int k) {
	if (isExternal(v)) //없을 경우
		return v; //외부노드 반환
	if (k == v->key) //찾은 경우
		return v; //찾은 노드 반환
	else if (k < v->key) //찾으려는 k가 더 작은 경우
		return treeSearch(v->left, k); //좌 자식노드로 이동
	else if (k > v->key) //찾으려는 k가 더 큰 경우
		return treeSearch(v->right, k); //우 자식노드로 이동
}

int isExternal(Node* w) {
	return (w->left == NULL && w->right == NULL); //양쪽 자식이 없는 경우
}

int isInternal(Node* w) {
	return(w->left != NULL || w->right != NULL); //양쪽 자식 중 하나라도 있는 경우
}

void insertItem(Root *T, int k) {
	Node* w = treeSearch(T->root, k);
	if (isInternal(w)) //이미 key가 존재하면 기각
		return;

	else {
		w->key = k; //노드 w에 key 저장
		expandExternal(w); //외부노드로 확장
	}
}

void expandExternal(Node* w) {
	Node* Left = (Node*)malloc(sizeof(Node)); //좌 자식 노드 생성
	Node* Right = (Node*)malloc(sizeof(Node)); //우 자식 노드 생성

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

int removeElement(Root *T, int k) {
	Node* w = treeSearch(T->root, k);

	if (isExternal(w)) //key가 없는 경우
		return NoSuchKey;
	
	int e = w->key; //반환해줄 w의 key값 저장
	
	Node* z = w->left; //좌 자식노드

	//(case #1)
	if (!isExternal(z)) //좌 자식노드가 외부노드가 아니라면
		z = w->right; //우 자식노드로 이동

	if (isExternal(z)) //한쪽 자식 노드가 외부노드라면
		reduceExternal(T, z); //외부노드 삭제

	else { //둘 다 내부노드라면 (case #2)
		Node* y = inOrderSucc(w); //중위순회후계자 찾기
		z = y->left; //중위순회후계자의 왼쪽자식(외부노드)
		w->key = y->key; //w 위치에 y값 넣기
		reduceExternal(T, z); //z(외부노드)와 w 삭제
	}

	return e; //반환
}

void reduceExternal(Root *T, Node* z) { //z는 외부노드
	Node* w = z->parent; //삭제하려는 노드의 부모노드 (이것도 삭제)
	Node* zs = sibling(z); //zs와 z는 동일 (좌/우노드인지만 판별)

	if (T->root == w) { //루트노드라면
		T->root = zs; //루트 자리에 z 넣기
		zs->parent = NULL; //z가 루트노드이므로 부모 초기화
	}

	else {
		Node* g = w->parent; //w의 부모노드 (z의 할머니노드)
		zs->parent = g; //w에 wp 넣기
		if (w == g->left) //w가 wp의 좌 자식노드였다면
			g->left = zs; //wp의 좌 자식노드에 z 연결
		else if (w == g->right) //w가 wp의 우 자식노드였다면
			g->right = zs; //wp의 우 자식노드에 z연결
	}

	free(z); //z노드 삭제
	free(w); //w노드 삭제
}

Node* inOrderSucc(Node* w) {
	w = w->right; //우 자식노드로 한 칸 이동 (w보다 큰 값 중)

	while (isInternal(w->left) == 1) //내부노드일 때까지
		w = w->left; //좌 자식노드로 이동 (가장 작은 값)
	return w; //중위수식후계자 반환
}

Node* sibling(Node* z) {
	if (z->parent->left == z) //z가 좌 형제노드라면
		return z->parent->right;
	else if (z->parent->right == z) //z가 우 형제노드라면
		return z->parent->left;
}

void print(Root *T) {
	preOrder(T->root);
	printf("\n");
}

void preOrder(Node* p) {
	if (isExternal(p))
		return;
	printf(" %d", p->key);
	preOrder(p->left);
	preOrder(p->right);
}
