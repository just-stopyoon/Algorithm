#pragma warning(disable : 4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct IncidentEdge {
	int aName;
	struct IncidentEdge* next;
}IncidentEdge;

typedef struct Vertex {
	int vName;
	int isVisit;
	IncidentEdge* iHead;
	struct Vertex* next;
}Vertex;

typedef struct Graph {
	Vertex* vHead;
}Graph;

void init(Graph* G) {
	G->vHead = NULL;
}

void makeVertex(Graph *G, int vName){
	Vertex* v = (Vertex*)malloc(sizeof(Vertex));
	v->vName = vName;
	v->iHead = NULL;
	v->next = NULL;
	v->isVisit = FALSE;

	Vertex* p = G->vHead;
	if (p == NULL)
		G->vHead = v;
	else {
		while (p->next != NULL)
			p = p->next;
		p->next = v;
	}
}

Vertex* findVertex(Graph* G, int vName) {
	Vertex* v = G->vHead;
	while (v->vName != vName)
		v = v->next;
	return v;
}

void makeIncidentEdge(Vertex* v, int aName) {
	IncidentEdge *i = (IncidentEdge*)malloc(sizeof(IncidentEdge));
	i->aName = aName;
	i->next = NULL;
	
	IncidentEdge* r = v->iHead;
	if (r == NULL)
		v->iHead = i;
	else {
		while (r->next != NULL && aName > r->next->aName)
			r = r->next;
		if (r->aName > aName) {
			i->next = r;
			v->iHead = i;
		}
		else {
			i->next = r->next;
			r->next = i;
		}
	}
}

void insertEdge(Graph* G, int v1, int v2) {
	Vertex* v = findVertex(G, v1);
	makeIncidentEdge(v, v2);
	
	v = findVertex(G, v2);
	makeIncidentEdge(v, v1);

}

void rdfs(Graph* G, int vName) {
	Vertex* p = findVertex(G, vName);
	if (p->isVisit == FALSE) {
		printf("%d\n", p->vName);
		p->isVisit = TRUE;
	}

	IncidentEdge* q;
	for (q = p->iHead; q != NULL; q = q->next) {
		p = findVertex(G, q->aName);
		if (p->isVisit == FALSE)
			rdfs(G, p->vName);
	}
}

int main() {
	Graph G;
	init(&G);

	int n, m, s;
	scanf("%d %d %d", &n, &m, &s);

	for (int i = 1; i <= n; i++) {
		makeVertex(&G, i);
	}
	
	int v1, v2;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &v1, &v2);
		insertEdge(&G, v1, v2);
	}

	rdfs(&G, s);
}