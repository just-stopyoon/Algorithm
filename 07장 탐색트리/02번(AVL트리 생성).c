#pragma warning(disable : 4996)
#include<stdio.h>
#include<stdlib.h>

typedef struct treeNode {
	int key;
	int height; //추가
	struct treeNode* left;
	struct treeNode* right;
	struct treeNode* parent;
}treeNode;

typedef struct Root {
	struct treeNode* root;
}Root;

void initTree(Root *T) { //트리노드 초기화
	treeNode* root = (treeNode*)malloc(sizeof(treeNode));
	root->left = NULL;
	root->right = NULL;
	root->parent = NULL;

	T->root = root;
}

int isExternal(treeNode* w) { //외부노드인지
	return w->left == NULL || w->right == NULL;
}

int isInternal(treeNode* w) { //내부노드인지
	return w->left != NULL && w->right != NULL;
}

treeNode* treeSearch(treeNode* v, int k) {
	if (isExternal(v)) //외부노드이면
		return v; //반환
	if (k == v->key) //내가 찾던 노드면
		return v; //반환
	else if (k < v->key) //더 작으면
		return treeSearch(v->left, k); //왼쪽으로 재탐색
	else if (k > v->key) //더 크면
		return treeSearch(v->right, k); //오른쪽으로 재탐색
}

void expandExternal(treeNode* w) { //외부노드 확장
	treeNode* Left = (treeNode*)malloc(sizeof(treeNode)); //왼쪽 외부노드
	treeNode* Right = (treeNode*)malloc(sizeof(treeNode)); //오른쪽 외부노드

	Left->left = NULL;
	Left->right = NULL;
	Left->parent = w;

	Right->left = NULL;
	Right->right = NULL;
	Right->parent = w;

	w->left = Left;
	w->right = Right;
	w->height = 1; //추가
}

//(추가)
int updateHeight(treeNode* z) {
	int h;
	if (z->left->height > z->right->height)
		h = z->left->height + 1;
	else
		h = z->right->height + 1;
	if (h != z->height) {
		z->height = h;
		return 1;
	}
	else
		return 0;
}

//(추가)
int isBalanced(treeNode* z) {
	treeNode* zl = z->left;
	treeNode* zr = z->right;
	return(zl->height - zr->height > -2 && zl->height - zr->height < 2);
}

//(추가)
treeNode* restructure(Root* T, treeNode* x, treeNode* y, treeNode* z) {
	treeNode* a, * b, * c, * T0, * T1, * T2, * T3;
	//설정하는 과정
	//(1회전)
	if (z->key < y->key && y->key < x->key) {
		//z < y < x
		a = z;
		b = y;
		c = x;
		T0 = a->left;
		T1 = b->left;
		T2 = c->left;
		T3 = c->right;
	}
	else if (x->key < y->key && y->key < z->key) {
		//x < y < z
		a = x;
		b = y;
		c = z;
		T0 = a->left;
		T1 = a->right;
		T2 = b->right;
		T3 = c->right;
	}
	else if (z->key < x->key && x->key < y->key) {
		//z < x < y
		a = z;
		b = x;
		c = y;
		T0 = a->left;
		T1 = b->left;
		T2 = b->right;
		T3 = c->right;
	}
	else {
		//y < x < z
		a = y;
		b = x;
		c = z;
		T0 = a->left;
		T1 = b->left;
		T2 = b->right;
		T3 = c->right;
	}
	//교환하는 과정
	if (T->root == z) { //루트노드에서 이뤄졌던 거라면
		T->root = b;
		b->parent = NULL;
	}

	else if (z->parent->left == z) { //왼쪽에서 이뤄졌던 거라면
		z->parent->left = b;
		b->parent = z->parent;
	} 
	else { //오른쪽에서 이뤄졌던 거라면
		z->parent->right = b;
		b->parent = z->parent;
	}

	a->left = T0;
	a->right = T1;
	T0->parent = a;
	T1->parent = a;
	updateHeight(a);

	c->left = T2;
	c->right = T3;
	T2->parent = c;
	T3->parent = c;
	updateHeight(c);

	b->left = a;
	b->right = c;
	a->parent = b;
	c->parent = b;
	updateHeight(b);
	
	return b;
}

//(추가)
void searchAndFixAfterInsertion(Root* T, treeNode* w) {
	w->left->height = 0;
	w->right->height = 0;
	w->height = 1;

	if (T->root == w)
		return;
	
	treeNode* z = w->parent; //T의 루트를 향해 올라가다가 처음 만나는 불균형 노드
	while (updateHeight(z) && isBalanced(z)) {
		if (T->root == z) //불균형 노드가 없다면
			return;
		z = z->parent;
	}
	if (isBalanced(z)) //전부 균형을 갖추고 있다면
		return;

	treeNode* x, * y;
	//z의 높은 자식
	if (z->left->height > z->right->height)
		y = z->left;
	else
		y = z->right;
	//y의 높은 자식
	if (y->left->height > y->right->height)
		x = y->left;
	else
		x = y->right;

	restructure(T, x, y, z);
}

void insertItem(Root* T, int k) { //원소 삽입
	treeNode* w = treeSearch(T->root, k); //원하는 위치 찾기
	if (isInternal(w)) //내부노드면 (이미 있는 경우)
		return; //안 넣음
	else { //외부노드면
		w->key = k; //원소 삽입하고
		expandExternal(w); //내부노드로 만들기
		searchAndFixAfterInsertion(T, w); //(추가) 균형 점검
	}
}

treeNode* sibling(treeNode* z) { //형제 찾기
	if (z->parent->left == z) //내가 엄마의 왼쪽이면
		return z->parent->right; //엄마의 오른쪽 반환

	else if (z->parent->right == z) //내가 엄마의 오른쪽이면
		return z->parent->left; //엄마의 왼쪽 반환
}

treeNode* reduceExternal(Root *T, treeNode* z) { //외부노드 삭제
	treeNode* w = z->parent; //z의 엄마
	treeNode* zs = sibling(z); //z의 형제

	if (w == T->root) { //엄마가 뿌리면
		T->root = zs; //뿌리를 형제로 바꾸고
		zs->parent = NULL; //엄마 초기화
	}
	else { //아니면
		treeNode* g = w->parent; //할머니
		zs->parent = g; //형제의 엄마를 할머니로
		if (w == g->left) //엄마가 할머니의 왼쪽이었으면
			g->left = zs; //할머니의 왼쪽에 형제
		else if (w == g->right) //엄마가 할머니의 오른쪽이었으면
			g->right = zs; //할머니의 오른쪽에 형제
	}
	free(z); //나 초기화
	free(w); //엄마 초기화

	return (zs); //형제 노드 반환
}

treeNode* inOrderSucc(treeNode* w) { //중위순회후계자 찾기
	w = w->right; //오른쪽으로 한 칸 가고
	while (isInternal(w->left) == 1) { //제일 마지막 왼쪽까지
		w = w->left; //왼쪽으로 이동
	}
	return w; //중위순회후ㅖ자 반환
}

//(추가)
void searchAndFixAfterRemoval(Root* T, treeNode* z) {
	if (T->root == z) //루트 노드면 종료
		return;

	z = z->parent; //T의 루트로 향해 가는 중 처음 만나는 불균형 노드

	while (updateHeight(z) && isBalanced(z)) {//균형을 맞췄는지
		if (T->root == z) //없으면
			return;
		z = z->parent; //계속 위로 
	}
	if (isBalanced(z)) //없으면
		return;

	treeNode* x, * y;
	//z의 높은 자식 y
	if (z->left->height > z->right->height)
		y = z->left;
	else
		y = z->right;
	//y의 높은 자식
	if (y->left->height > y->right->height)
		x = y->left;

	else if (y->left->height < y->right->height)
		x = y->right;
	//자식간의 높이가 같으면 둘 중 y와 같은 쪽의 자식을 선택
	else {
		if (z->left == y)
			x = y->left;
		else
			x = y->right;
	}

	treeNode* b = restructure(T, x, y, z);

	if (T->root == b)
		return;

	//b의 부모부터 루트까지 계속 개조
	searchAndFixAfterRemoval(T, b->parent);
}

int removeElement(Root* T, int k) { //원소 삭제
	treeNode* w = treeSearch(T->root, k); //찾고자하는 노드 찾기

	if (isExternal(w)) //찾고자 하는게 없으면
		return 0; //0 반환

	int e = w->key; //찾은 노드의 키값 저장
	treeNode* z = w->left; //노드의 왼쪽 자식
	treeNode* zs; //자식 노드 반환

	if (isInternal(z)) //내부노드일 경우
		z = w->right; //일단 오른쪽 자식으로
	if (isExternal(z)) //(내부+외부) 또는 (외부+외부)이면
		zs = reduceExternal(T, z); //외부노드랑 나 삭제하고 형제 반환

	else { //(내부+내부)일 경우
		treeNode* y = inOrderSucc(w); //중위순회후계자 찾기
		z = y->left; //중위 순휘 후계자를 엄마로 만들기
		w->key = y->key; //중위순회 후계자로 바꿔주기
		zs = reduceExternal(T, z); //나랑 엄마 삭제하기
	}
	searchAndFixAfterRemoval(T, zs); //(추가) 균형 점검
	return e;
}

int findElement(Root* T, int k) {
	treeNode* w = treeSearch(T->root, k); //노드 찾기

	if (isExternal(w)) //찾고자 하는게 없으면
		return 0; //0반환
	
	return w->key; //찾은 값 반환
}

void preOrder(treeNode* p) { //중위순회
	if (isExternal(p)) //마지막까지 
		return;

	printf(" %d", p->key); //출력
	preOrder(p->left); //왼쪽
	preOrder(p->right); //오른쪽
}

void print(Root* T) { //출려
	preOrder(T->root); //중위순회 시작
	printf("\n");
}

int main() {
	Root* T;
	initTree(&T);

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
		else if (c == 'p') {
			print(&T);
		}
		else if (c == 'q')
			break;
		getchar();
	}
}