#pragma warning(disable : 4996)
#include<stdio.h>

int main() {
	int a, b, N;
	scanf("%d %d %d", &a, &b, &N);
	char* arr = (char*)malloc(sizeof(char) * (N+1));
	scanf("%s", arr);

	int mid = 0;
	
	for (int i = 0; i < N; i++) {
		mid = (a + b) / 2;

		if (arr[i] == 'Y') {
			a = mid + 1;
		}
		else if (arr[i] == 'N') {
			b = mid;
		}

	}
	printf("%d", a);
}