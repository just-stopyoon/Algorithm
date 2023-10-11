#pragma warning(disable : 4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void swap(int *a, int *b);
void insertItem(int key);
int removeMax();
void upHeap(int i);
void downHeap(int i);
void printHeap();

int H[100], n = 0; //힙, 힙의 크기

int main() {
	char commend;
	int key;

	while (1) {
		scanf("%c", &commend);
		if (commend == 'i') {
			scanf("%d", &key);
			insertItem(key);
			printf("0\n");
		}
		else if (commend == 'd')
			printf("%d\n", removeMax());

		else if (commend == 'p')
			printHeap();

		else if (commend == 'q')
			break;
	}
}

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
void insertItem(int key) {
	n = n + 1; //n 갱신
	H[n] = key; //힙의 초기 삽입 위치는 n
	upHeap(n); //힙 조정
}

int removeMax() {
	int key = H[1]; //루트 키 보관
	H[1] = H[n]; //힙의 마지막 키를 루트로 이동
	n = n - 1; //n 갱신
	downHeap(1); //힙 조정
	return key; //삭제 키 반환
}

void upHeap(int i) {
	if (i == 1) //루트일 때
		return;
	if (H[i] <= H[i / 2]) //i의 키가 부모의 key보다 작같일 때
		return;

	swap(H + i, H + i / 2); //i와 부모의 위치 교환
	upHeap(i / 2); //재귀호출
}

void downHeap(int i) {
	if (i * 2 > n && i * 2 + 1 > n) //외부노드일 때
		return;

	int larger = i * 2; //왼쪽 자식 노드 값 저장

	if (H[i * 2 + 1] > H[larger]) //오른쪽 자식 노드가 더 크다면
		larger = i * 2 + 1; //오른쪽 자식 노드 값 저장

	if (H[i] >= H[larger]) //원하는 자리에 도착했을 때(최대 힙으로 됐을 때)
		return;

	swap(H + i, H + larger); //둘 중 큰 자식 노드와 부모 노드끼리 변경
	downHeap(larger); //재귀적 호출
}

void printHeap() {
	for (int i = 1; i <= n; i++)
		printf(" %d", H[i]);
	printf("\n");
}