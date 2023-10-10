#pragma warning(disable : 4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main() {
	int n;
	scanf("%d", &n);
	
	int* arr = (int*)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	for (int i = 1; i < n; i++) { //첫번째 원소는 이미 정렬된 상태로 가정
		int save = arr[i]; //현재 탐색하는 위치의 값을 save에 저장
		int j = i - 1; //현재 검사 중인 변수의 왼쪽

		while ((j >= 0) && (arr[j] > save)) { //현재 검사 중인 arr[i]와 이전요소를 비교
			arr[j + 1] = arr[j]; //정렬할 공간 생성
			j -= 1; //검사를 왼쪽으로
		}
		arr[j + 1] = save;
	}

	for (int i = 0; i < n; i++) {
		printf(" %d", arr[i]);
	}
}