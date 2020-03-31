//Kody Fong 1519213
//kbfong
//PA 4
//GraphTest.c , a test for Graph.c. Just tests the basic functions

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"


int main(int argc, char* argv[]) {

Graph G = newGraph(5);

printf("%d\n", getOrder(G));
printf("%d\n", getSize(G));
printf("%d\n", getSource(G));
printf("%d\n", getParent(G, 5));
printf("%d\n", getDist(G,5));

addEdge(G,1,3);
printGraph(stdout, G);

addArc(G,1,5);
printGraph(stdout,G);

BFS(G, 3);
printf("%d\n", getParent(G, 5));
printf("%d\n", getDist(G, 2));

return 0;
}