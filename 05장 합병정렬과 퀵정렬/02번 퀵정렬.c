#pragma warning(disable : 4996)
#include<stdio.h>
#include<stdlib.h>

void swap(int* a, int* b);
int findPivot(int left, int right);
int inPlacePartition(int left, int right, int k);
void inPlaceQuickSort(int left, int right);

int* arr, n = 0;

int main() {
	scanf("%d", &n);
	
	arr = (int*)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	inPlaceQuickSort(0, n - 1);

	for (int i = 0; i < n; i++) {
		printf(" %d", arr[i]);
	}
}

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int findPivot(int left, int right) {
	return left + rand() % (right - left +1);
}

int inPlacePartition(int left, int right, int k) {
	int pivot = arr[k];
	
	swap(arr + k, arr + right);

	int i = left;
	int j = right - 1;

	while (i <= j) {
		while (i <= j && arr[i] <= pivot)
			i++;				   
		while (i <= j && arr[j] >= pivot)
			j--;
		if (i < j)
			swap(arr + i, arr + j);
	}
	swap(arr + i, arr + right);

	return i;
}

void inPlaceQuickSort(int left, int right) {
	if (left < right) {
		int k = findPivot(left, right);
		int pivot = inPlacePartition(left, right, k);
		inPlaceQuickSort(left, pivot - 1);
		inPlaceQuickSort(pivot + 1, right);
	}
}