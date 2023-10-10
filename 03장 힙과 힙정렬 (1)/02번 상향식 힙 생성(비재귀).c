#pragma warning(disable : 4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void swap(int* a, int* b);
void buildHeap();
void downHeap(int i);
void printHeap();

int H[100], n = 0; //힙, 힙의 크기

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &H[i]);
	}
	buildHeap();
	printHeap();
}

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void buildHeap() {
	for (int i = n / 2; i > 0; i--)
		downHeap(i);
}

void downHeap(int i) {
	if (i * 2 > n) //왼쪽 자식이 외부노드면
		return;

	int larger = i * 2; //왼쪽 자식을 larger로 초기화

	if (i * 2 + 1 <= n) { //오른쪽 자식이 내부노드면서
		if (H[i * 2 + 1] > H[larger]) //왼쪽 자식보다 큰 노드면
			larger = i * 2 + 1; //larger에 오른쪽 자식 넣기
	}

	if (H[i] >= H[larger]) //현재 노드가 larger보다 커지면
		return;

	swap(H + i, H + larger); //교환
	downHeap(larger);
}

void printHeap() {
	for (int i = 1; i <= n; i++)
		printf(" %d", H[i]);
	printf("\n");
}