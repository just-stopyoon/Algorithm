#pragma warning(disable : 4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct hashNode {
	struct hashNode* next;
	int key;
}hashNode;

typedef struct hashHead {
	hashNode* head;
}hashHead;

int M; //할당된 공간 수

void initHash(hashHead* H) { //hash 생성

	for (hashHead* p = H; p < H + M; p++) { //테이블 공간 처음부터 끝까지
		hashNode* head = (hashNode*)malloc(sizeof(hashNode*)); //테이블 외부에 추가적인 노드 생성
		head->next = NULL;
		p->head = head; //테이블과 외부 공간 연결
	}
}

int h(int x) { //h2 함수
	return x % M;
}

void insertItem(hashHead* H, int k) { //원소 삽입
	int v = h(k); //해시값

	hashNode* N = (hashNode*)malloc(sizeof(hashNode));
	hashNode* p = H[v].head; //해시값에 해당하는 테이블 외부 공간

	N->key = k; //새롭게 할당한 공간에 key를 저장하고
	N->next = p->next; //기존에 할당되어 있는 외부 공간 앞에 공간(원소) 삽입
	p->next = N; //p를 N으로 대체
}

int findElement(hashHead* H, int k) {
	int v = h(k); //해시값
	int cnt = 1; //키가 존재할 경우, 최소 순위 1

	hashNode* p = H[v].head->next; //원하는 배열의 첫 번째 외부 공간

	while (p) { //외부 공간 전체 탐색
		if (p->key == k) //찾으면
			return cnt; //cnt 값 반환
		p = p->next; //한 칸씩 다음 공간으로
		cnt++; //cnt 추가
	}
	return 0; //못 찾은 경우
}

int removeElement(hashHead* H, int k) {
	int v = h(k); //해시 값
	int cnt = 1; //키가 존재할 경우, 최소 순위 1

	hashNode* p = H[v].head; //원하는 배열 (revmove의 경우, 나중에 해제해줘야하기 때문에 한 칸 앞에서 판단)

	while (p->next) { //한 칸 앞에서 판단해야하므로
		if (p->next->key == k) { //원하는 공간을 찾았을 경우,
			hashNode* q = p->next; //해당 공간을 해제 시키기 위해
			p->next = q->next; //해제할 공간에 다음 공간 하나씩 땡기기
			free(q); //공간 해제 (삭제)
			return cnt; //순위
		}
		p = p->next;
		cnt++;
	}
	return 0; //못 찾았을 경우
}

void print(hashHead* H) { //해시 출력
	for (hashHead* p = H; p < H + M; p++) { //할당한 해시테이블에서
		for (hashNode* q = p->head->next; q; q = q->next) { //해시테이블의 외부 공간 부터 끝까지
			printf(" %d", q->key); //출력
		}
	}
	printf("\n");
}

int main() {
	char c;
	int x;

	scanf("%d", &M);

	hashHead *H = (hashHead*)malloc(sizeof(hashHead) * M); //테이블 공간 할당
	initHash(H);


	while (1) {
		scanf("%c", &c);

		if (c == 'i') {
			scanf("%d", &x);
			insertItem(H, x);
		}
		else if (c == 's') {
			scanf("%d", &x);
			printf("%d\n", findElement(H, x));
		}
		else if (c == 'd') {
			scanf("%d", &x);
			printf("%d\n", removeElement(H, x));
		}
		else if (c == 'p') {
			print(H);
		}
		else if (c == 'e')
			break;
		getchar();
	}
}