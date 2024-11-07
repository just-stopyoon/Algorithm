#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Queue {
	int arr[100];
	int head, tail;
}Queue;

typedef struct Edge {
	int to;
	struct Edge* next;
}Edge;

int N, M;

int in[100];
char vertices[100];
Edge* edges[100];
Queue q;

//O(n)
int getIndex(char ch) {
	for (int i = 0; i < N; i++) {
		if (vertices[i] == ch)
			return i;
	}
}

Edge* getEdge(int to) {
	Edge* ret = (Edge*)malloc(sizeof(Edge));
	ret->next = NULL;
	ret->to = to;
	return ret;
}

//n < 100, m < 1000
//isEmpty(), push(), pop()

const int FAIL = -1, SUCCESS = 1e8;

int qisEmpty() {
	if (q.head == q.tail)
		return SUCCESS;
	return FAIL;
}


int qPush(int elem) {
	q.arr[q.tail] = elem;
	q.tail = (q.tail + 1) % 101;
	return SUCCESS;
}

int qPop() {
	int ret = q.arr[q.head];
	q.head = (q.head + 1) % 101;
	return ret;
}

int main() {
	scanf("%d", &N);
	getchar();

	for (int i = 0; i < N; i++) {
		scanf("%c", vertices + i);
		getchar();
	}

	scanf("%d", &M);
	getchar();

	//1000 * 2 * 100
	char cfrom, cto;
	for (int i = 0; i < M; i++) {
		scanf("%c %c", &cfrom, &cto);
		getchar();

		int from = getIndex(cfrom);
		int to = getIndex(cto);

		Edge *tmp = getEdge(to);
		tmp->next = edges[from];
		edges[from] = tmp;

		in[to]++;
	}
	q.head = 0;
	q.tail = 0;

	for (int i = 0; i < N; i++) {
		if (in[i] == 0)
			qPush(i);
	}

	int output[100], outIdx = 0;

	while (qisEmpty() != SUCCESS) {
		int now = qPop();
		output[outIdx] =now;
		outIdx++;
	
		Edge* cur = edges[now];
		while (cur != NULL) {
			in[cur->to]--;

			if (in[cur->to] == 0)
				qPush(cur->to);

			cur = cur->next;
		}
	}

	if (outIdx == N) {
		for (int i = 0; i < N; i++) {
			int idx = output[i];
			printf("%c ", vertices[idx]);
		}
	}
	else {
		printf("0");
	}
}