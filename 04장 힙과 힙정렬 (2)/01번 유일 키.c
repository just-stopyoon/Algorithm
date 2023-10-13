#pragma warning(disable : 4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void swap(int* a, int* b);
void downHeap(int i);
void rBuildHeap(int i);
void inPlaceHeapSort();
void printArray();

int H[100], n = 0;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &H[i]);
	}

	inPlaceHeapSort();
	printArray();
}

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void inPlaceHeapSort() {
	rBuildHeap(1);

	int N = n;

	while (n != 1) {
		swap(H + n, H + 1);
		n--;
		downHeap(1);
	}
	n = N;
}

void downHeap(int i) {
	int larger = i * 2; //왼쪽 자식 노드

	if (larger > n)
		return;

	else if (larger + 1 <= n && H[larger + 1] > H[larger])
		larger = larger + 1;

	if (H[larger] > H[i]) {
		swap(H + i, H + larger);

		downHeap(larger);
	}
}

void rBuildHeap(int i) {
	if (i >= n)
		return;

	rBuildHeap(i * 2); //현재 부트리의 좌 부트리를 힙 생성
	rBuildHeap(i * 2 + 1); //현제 부트리의 우 부트리를 힙 생성
	downHeap(i); //현재 부트리의 루트와 좌우 부트리를 합친 힙 생성
}

void printArray() {
	for (int i = 1; i <= n; i++) {
		printf(" %d", H[i]);
	}
}
