//Kody Fong 1519213
//kbfong
//PA 5
//Header file for Graph.c

#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_	


#define NIL 0
#define UNDEF -1
#include "List.h"


typedef struct GraphObj* Graph;



Graph newGraph(int n);
void freeGraph(Graph* pG);

/*** Access functions ***/

int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);


void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S);


void printGraph(FILE* out, Graph G);
 Graph transpose(Graph G);
 Graph copyGraph(Graph G);
#endif 