#pragma warning(disable : 4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int M, n, q; //해시테이블 크기, 입력 받을 키 값, M보다 조금 작은 소수

int h1(int x) { //첫 번째 해시함수
	return x % M;
}

int h2(int x) { //두 번째 해시함수 (이중해싱)
	return q - (x % q);
}

int getNextBucket(int v, int i, int x) { //이중해싱
	return (v + i * h2(x)) % M;
}

int insertItem(int* H, int x) { //삽입
	int v = h1(x); //해시값
	int i = 0;

	while (i < n) { //아직 입력 받을 수 있을 때
		int b = getNextBucket(v, i, x); //이중해싱 값 저장
		if (H[b] == 0) { //빈 셀이면
			H[b] = x; //key값 저장

			for (int c = 0; c < i; c++) //충돌횟수만큼 출력
				printf("C");

			return b; //저장 셀 주소 반환
		}
		i++; //삽입한 원소 개수 증가
	}
	return -1; //입력이 제대로 안됐을 경우
}

int findElement(int* H, int x) { //탐색
	int v = h1(x); //해시값
	int i = 0;

	while (i < n) {
		int b = getNextBucket(v, i, x); //이중해싱 값
		if (H[b] == 0) //빈셀이면
			return -1; //없음 출력

		else if (H[b] == x) //찾았으면
			return b; //해당 셀의 주소 반환

		else
			i++; //i 값 증가
	}
	return -1;
}

void print(int* H) {
	for (int* p = H; p < H + M; p++) {
		printf(" %d", *p); //해시테이블의 원소 출력
	}
	printf("\n");
}

int main() {
	scanf("%d %d %d", &M, &n, &q);

	int* H = (int*)malloc(sizeof(int) * M); //크기가 M인 배열로 동적할당

	char c;
	int x;

	while (1) {
		getchar();
		scanf("%c", &c);

		if (c == 'i') {
			scanf("%d", &x);
			printf("%d", insertItem(H, x)); //x의 주소 (해시값) 출력
		}
		else if (c == 's') {
			scanf("%d", &x);
			int i = findElement(H, x);

			if (i != -1) //x가 있을 때, 
				printf("%d %d\n", i, x); //주소, 키 출력
			else
				printf("-1"); //없으면 -1 출력
		}

		else if (c == 'p') {
			print(H);
		}

		else if (c == 'e') {
			print(H);
			break;
		}
	}
}