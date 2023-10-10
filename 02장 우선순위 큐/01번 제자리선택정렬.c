#pragma warning(disable : 4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void swap(int* a, int* b);
int findMax(int* arr, int n);

int main() {
	int n;
	scanf("%d", &n);
	int* arr = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	for (int i = n-1; i > 0; i--) {
		int maxIndex = findMax(arr, i+1);
		swap(arr + i, arr + maxIndex);
	}
	for (int i = 0; i < n; i++) {
		printf(" %d", arr[i]);
	}
}

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int findMax(int* arr, int n) {
	int maxIndex = 0;
	for (int i = 0; i < n; i++) {
		if (arr[maxIndex] < arr[i])
			maxIndex = i;
	}
	return maxIndex;
}