#pragma warning(disable : 4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define INF 10000

int graph[100][100]; //
int numV; //방문해야 할 정점
int isvisit[100]; //방문여부 : 노방문 0, 방문 1
int d[100]; //거리 일단 10000을 넣고, 정점들이 추가되면서 초기화됨
int p[100]; //정점의 부모 역할을 하는게 정점 몇 번인지 
int n, m; //문제에서 주어진 입력

void buildGraph() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		graph[u - 1][v - 1] = w; //u번과 v번 사이에 연결되는 노드 가중치가 w
		graph[v - 1][u - 1] = w;
	}
}

int removeMin(int* isvisit, int* d) {
	int current = INF;
	int min = 0;
	
	for (int i = 0; i < n; i++) {
		if (isvisit[i] == 0 && d[i] < current) {
			current = d[i];
			min = i;
		}
	}

	isvisit[min] = 1;
	numV -= 1;
	return min;
}

void Prim() {
	for (int i = 0; i < n; i++) {
		isvisit[i] = 0;
		d[i] = INF;
		p[i] = -1;
	}
	numV = n;

	d[0] = 0; //1번 정점까지 간 거리
	p[0] = 0; //1번의 부모는 자기 자신이다

	while (numV != 0) {
		int u = removeMin(isvisit, d);
		printf(" %d", u + 1); //배열의 인덱스는 0부터 시작하기 때문

		for (int i = 0; i < n; i++) {
			int z = 0;
			if (graph[u][i] != 0)
				z = i;
			if (isvisit[i] == 0 && (graph[u][z] < d[z])) {
				d[z] = graph[u][z];
				p[z] = u; //나중에 거리를 출력할 때 거리를 알기 위해서 
			}
		}
	}
	printf("\n");

	int totalweight = 0;
	for (int i = 0; i < n; i++) {
		totalweight += graph[p[i]][i];
	}
	printf("%d", totalweight);
}


int main() {

	buildGraph();
	Prim();
}