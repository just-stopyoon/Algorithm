#pragma warning(disable : 4996)
#include<stdio.h>

void mergeSort(int left, int right); 
void merge(int left, int mid, int right);

int arrA[100], arrB[100], n = 0; //arrA 정렬할 배열 저장, arrB 합병 작업 수행, n 배열의 크기

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arrA[i]); //arrA에 n개의 정수 입력 
	}
	mergeSort(0, n-1); //합병 정렬 시작

	for (int i = 0; i < n; i++)
		printf(" %d", arrA[i]); //정렬된 배열 출력
}

void mergeSort(int left, int right) {
	int mid = (left + right) / 2; //배열의 중간 지점 분할

	if (left < right) {
		mergeSort(left, mid); //배열의 왼쪽 부분 재귀적 합병 정렬
		mergeSort(mid + 1, right); //배열의 오른쪽 부분 재귀적 합병 정렬
		merge(left, mid, right); //왼쪽과 오른쪽 배열 합병!
	}
}

void merge(int left, int mid, int right) {
	int i = left, k = left; //i : 왼쪽 배열의 시작 지점, k : 배열을 순회할 변수
	int j = mid + 1; //오른쪽 배열의 시작 지점

	while (i <= mid && j <= right) { //왼쪽 배열, 오른쪽 배열의 끝 지점 전까지
		if (arrA[i] < arrA[j]) //왼쪽 배열이 작으면
			arrB[k++] = arrA[i++]; //arrB에 arrA의 왼쪽 배열 값을 넣고 왼쪽 배열 인덱스 증가
		else  //오른쪽 배열이 작으면
			arrB[k++] = arrA[j++]; //arrB에 arrA의 오른쪽 배열 값을 넣고 오른쪽 배열 인덱스 증가
	}
	while (i <= mid){ //왼쪽 부분에 남아있는 요소가 있을 때
		arrB[k++] = arrA[i++]; //넣어주기
	}
	while (j <= right) { //오른쪽 부분에 남아있는 요소가 있을 때
		arrB[k++] = arrA[j++]; //넣어주기
	}
	for (int i = left; i <= right; i++) { //arrB의 값을 arrA에 복사
		arrA[i] = arrB[i];
	}
}