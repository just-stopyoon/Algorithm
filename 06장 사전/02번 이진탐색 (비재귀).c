#pragma warning(disable : 4996)
#include<stdio.h>

int binarySearch(int* arr, int k, int left, int right);

int n;

int main() {
	int k;
	scanf("%d %d", &n, &k);
	int* arr = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	printf("%d", binarySearch(arr, k, 0, n - 1));
}

int binarySearch(int* arr, int k, int left, int right) {
	int i = 0;
	int result = n;

	while (1) {
		if (left > right) {
			break;
		}

		int mid = (left + right) / 2;

		if (k == arr[mid])
			return mid;
		else if (k < arr[mid])
			right = mid - 1;
		else if (k > arr[mid])
			left = mid + 1;
	}
	return left;
}