#pragma warning (disable : 4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct Edge { //간선 구조체
	int v1, v2; //간선의 두 끝점
	int weight; //간선의 가중치
	struct Edge* next; //다음 간선을 가리키는 포인터
}Edge;

typedef struct IncidentEdge { //각 정점의 인접간선 구조체
	int aName; //인접한 정점의 이름
	Edge* e; //해당 간선에 대한 포인터
	struct IncidentEdge* next; //다음 인접간선을 가리키는 포인터
}IncidentEdge;

typedef struct Vertex { //정점 구조체
	int vName; //정점의 이름
	IncidentEdge* iHead; //인접간선 리스트를 가리키는 포인터
	struct Vertex* next; //다음 정점을 가리키는 포인터
}Vertex;

typedef struct Graph { //그래프 구조체
	Vertex* vHead; //정점들의 리스트를 가리키는 포인터
	Edge* eHead; //간선들의 리스트를 가리키는 포인터
}Graph;

void initGraph(Graph* G) { //그래프 초기화
	G->vHead = NULL; //정점 초기화
	G->eHead = NULL; //간선 초기화
}

void insertVertex(Graph* G, int i) { //그래프에 새로운 정점을 추가
	Vertex* v = (Vertex*)malloc(sizeof(Vertex)); //새로운 정점 초기화
	v->vName = i; //정점 이름 설정
	v->iHead = NULL; //인접간선 초기화
	v->next = NULL; //다음 주소 초기화

	Vertex* p = G->vHead; //그래프의 정점리스트
	if (p == NULL) { //정점이 없으면
		G->vHead = v; //정점 추가
	}
	else { //정점이 있으면
		while (p->next) { //정점 끝까지 이동
			p = p->next;
		}
		p->next = v; //제일 마지막에 추가
	}
}

void insertIncidentEdge(Vertex* v, int aName, Edge* e) { //인접간선 추가
	IncidentEdge* i = (IncidentEdge*)malloc(sizeof(IncidentEdge)); //인접간성 초기화
	i->aName = aName; //정점 이름
	i->e  = e; //간선 이름
	i->next = NULL; //다음 주소 초기화

	IncidentEdge* p = v->iHead; //정점의 인접간선리스트의 시작 주소
	if (p == NULL) { //인접간선리스트가 없으면
		v->iHead = i; //인접간선 추가
	}
	else { //인접간선리스트가 있으면
		if (p->aName > i->aName) { //들어있는 인접간선보다 내가 먼저면
			i->next = p;  //내 다음 인접간선을 기존 인접간선으로 넣고 
			v->iHead = i; //대가리 대체
		}
		else { //뒤로 가야하면
			while (p->next && p->next->aName < i->aName) { //끝에 도다르고, 내가 더 커질 때까지
				p = p->next; //계속 이동
			}
			i->next = p->next; //뒤에 삽입
			p->next = i;
		}
	}
}

Vertex* findVertex(Graph* G, int vName) {
	Vertex* v = G->vHead; //그래프의 정점 리스트의 첫 번째
	while (v && v->vName != vName) { //끝에 도다르거나, 내가 원하는 걸 찾을 때까지
		v = v->next; //이동
	}
	return v;
}

void insertEdge(Graph* G, int v1, int v2, int weight) {
	Edge* e = (Edge*)malloc(sizeof(Edge)); //넣은 간선 초기화
	e->v1 = v1; //시작 정점
	e->v2 = v2; //끝 정점 
	e->weight = weight; //가중치
	e->next = NULL; //다음 주소 초기화

	Edge* p = G->eHead; //그래프의 간선 리스트의 대가리
	if (p == NULL) //만약 없었으면
		G->eHead = e; //그대로 삽입
	else { //있으면
		while (p->next) { //끝에 도달할 때까지
			p = p->next; //이동
		}
		p->next = e; //끝에 삽입
	}
	insertIncidentEdge(findVertex(G, v1), v2, e); //인접간선 리스트에도 삽입

	if (v1 != v2) { 
		insertIncidentEdge(findVertex(G, v2), v1, e); //인접간선 리스트에 삽입
	}
}

void print(Graph* G, int vName) { //특정 정점과 인접 간선을 출력
	Vertex* v = findVertex(G, vName); //원하는 정점 찾기

	if (v == NULL) { //찾는 정점이 없으면
		printf("-1\n");
		return;
	}
	
	for (IncidentEdge* p = v->iHead; p; p = p->next) { //내가 찾는 정점의 인접간선리스트
		printf(" %d %d", p->aName, p->e->weight); //원하는 정보 출력
	}
	printf("\n");
}

Edge* findEdge(Graph* G, int v1, int v2) { //특정 정점을 연결하는 간선 찾기
	Vertex* v = findVertex(G, v1); //찾고자 하는 정점 찾기

	for (IncidentEdge* p = v->iHead; p; p = p->next) { //정점의 인접간선리스트
		if (p->aName == v2) { //내가 원하는 간선일 경우
			return p->e; //해당 간선 반환
		}
	}
	return NULL;
}

void removeIncidentEdge(Vertex* v, IncidentEdge* i) { //인접간선 지우기
	IncidentEdge* p = v->iHead; //해당 정점의 인접간선리스트
	if (p == i) { //내가 찾고자하는 인접간선이 제일 앞에 있었으면
		v->iHead = i->next; //그거 옮겨버리기
	}
	else { //아니면
		while (p->next != i) { //내가 찾고자하는 거까지
			p = p->next; //이동
		}
		p->next = i->next; //그리고 그리고 앞에꺼랑 뒤에꺼랑 연결
	}
	free(i); //지워버리기
}

IncidentEdge* findIncidentEdge(Vertex* v, int aName) { //인접간선 찾기
	IncidentEdge* i = v ->iHead; //내가 찾고자하는 정점의 인접리스트
	while (i && i->aName != aName) { //끝까지 도달하고, 내가 원하는 걸 찾을 때까지
		i = i->next; //이동
	}
	return i; //반환
}


void removeEdge(Graph* G, Edge* e) { //간선 지우기
	Vertex* v1 = findVertex(G, e->v1); //시작 정점 찾기
	Vertex* v2 = findVertex(G, e->v2); //도착 정점 찾기

	removeIncidentEdge(v1, findIncidentEdge(v1, v2->vName)); //인접 간선 지우기
	if (v1 != v2) {
		removeIncidentEdge(v2, findIncidentEdge(v2, v1->vName)); //인접 간선 지우기
	}

	Edge* p = G->eHead; //그래프의 간선 리스트
	if (p == e) { //내가 찾고자 하는 게 첫번째에 있으면
		G->eHead = e->next; //옮겨버리기
	}
	else { //아니며 
		while (p->next != e) { //내가 찾고자하는 거까지
			p = p->next; //이동
		}
		p->next = e->next; //앞에 꺼랑 뒤에 꺼랑 연결
	}
	free(e); //지워버리기
}

void modifyWeight(Graph* G, int v1, int v2, int weight) { //가중치 수정
	if (findVertex(G, v1) == NULL || findVertex(G, v2) == NULL) { //내가 찾고자하는 게 없으면
		printf("-1\n"); //-1 반환
		return;
	}
	Edge* e = findEdge(G, v1, v2); //내가 바꾸고 하는 간선 찾기

	if (e == NULL) { //없으면
		insertEdge(G, v1, v2, weight); //새롭게 간선 추가
	}
	else if (weight == 0) { //넣고자 하는 가중치가 0이면
		removeEdge(G, e); //해당 간선 삭제해버리기
	}
	else { //만약에 제대로 찾으면
		e->weight = weight; //가중치 수정
	}
}

int main() {
	Graph* G = (Graph*)malloc(sizeof(Graph));
	initGraph(G);

	for (int i = 0; i <= 6; i++) {
		insertVertex(G, i);
	}

	insertEdge(G, 1, 2, 1);
	insertEdge(G, 1, 3, 1);
	insertEdge(G, 1, 4, 1);
	insertEdge(G, 1, 6, 2);
	insertEdge(G, 2, 3, 1);
	insertEdge(G, 3, 5, 4);
	insertEdge(G, 5, 5, 4);
	insertEdge(G, 5, 6, 3);

	while (1) {
		char c;
		scanf("%c", &c);
		if (c == 'a') {
			int vName;
			scanf("%d", &vName);
			print(G, vName);
		}
		else if (c == 'm') {
			int v1, v2, weight;
			scanf("%d %d %d", &v1, &v2, &weight);
			modifyWeight(G, v1, v2, weight);
		}
		else if (c == 'q') {
			break;
		}
	}
}