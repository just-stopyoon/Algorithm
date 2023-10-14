#pragma warning(disable : 4996)
#include<stdio.h>

int binarySearch(int *arr, int k, int left, int right);

int main() {
	int n, k;
	scanf("%d %d", &n, &k);
	int* arr = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	printf("%d", binarySearch(arr, k, 0, n - 1));
}

int binarySearch(int* arr, int k, int left, int right) {
	if (left > right){
		return right;
	}

	int mid = (left + right) / 2;

	if (k == arr[mid])
		return mid;

	else if (k < arr[mid]) {
		binarySearch(arr, k, left, mid - 1);
	}

	else if (k > arr[mid]) {
		binarySearch(arr, k, mid + 1, right);
	}
}

