#pragma warning(disable : 4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct bucket{
	int key, c; //c = 충돌횟수
}bucket;

int M, n; //해시테이블 크기, 입력 받을 키 값

void initHash(bucket* H) { //해시 초기화 
	for (bucket* p = H; p < H + M; p++) { //해시테이블 크기만큼
		p->key = 0; //key 값 초기화
		p->c = 0; //충돌횟수 초기화
	}
}

int h(int x) { //해시함수
	return x % M;
}

void insertItem(bucket* H, int x) { //삽입
	int v = h(x); //해시값
	int cnt = 0;

	while (H[v].key) { //비어있는 셀을 발견할 때까지
		v++; //바로 다음 셀에 저장
		cnt++; //충돌횟수 증가
		v = h(v); //해시값 갱신 (공간 초과 방지)
	}

	H[v].c = cnt; //충돌횟수 저장

	H[v].key = x; //빈 셀에 삽입

	for (int i = 0; i < H[v].c; i++) {
		printf("C"); //충돌횟수만큼 C 출력
	}
	printf("%d\n", v); //해시값 (배열 인덱스) 출력
}

void findElement(bucket* H, int x) { //탐색
	int v = h(x); //해시값

	while (H[v].key && H[v].key != x) { //빈 셀이거나, 내가 찾고자 하는 셀이 아니면
		v++; //다음 셀로 넘어가기
		v = h(v); //해시값 갱신 (공간 초과 방지)
	}

	if (H[v].key == 0) { //끝까지 못 찾았으면
		printf("-1\n");
		return 0;
	}
	
	printf("%d %d\n", v, x); //찾았으면, 해당 배열 인덱스와 학번 출력
}

int main() {
	scanf("%d %d", &M, &n);

	bucket* H = (bucket*)malloc(sizeof(bucket) * M);
	initHash(H);
	
	char c;
	int x;

	while (1) {
		getchar();
		scanf("%c", &c);
		if (c == 'i') {
			scanf("%d", &x);
			insertItem(H, x);
		}
		else if (c == 's') {
			scanf("%d", &x);
			findElement(H, x);
		}
		else if (c == 'e') {
			break;
		}
	}
}