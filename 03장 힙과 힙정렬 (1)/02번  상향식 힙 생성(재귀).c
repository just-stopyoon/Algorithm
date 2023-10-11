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