#pragma warning(disable : 4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void swap(int* a, int* b);
void rBuildHeap(int i);
void downHeap(int i);
void printHeap();

int H[100], n = 0; //힙, 힙의 크기

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &H[i]);
	}
	rBuildHeap(1);
	printHeap();
}

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void rBuildHeap(int i) {
	if (i > n)
		return;
	rBuildHeap(i * 2); //현재 부트리의 좌 부트리를 힙 생성
	rBuildHeap(i * 2 + 1); //현제 부트리의 우 부트리를 힙 생성
	downHeap(i); //현재 부트리의 루트와 좌우 부트리를 합친 힙 생성
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