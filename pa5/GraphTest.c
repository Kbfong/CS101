//Kody Fong 1519213
//kbfong
//PA 5
//GraphTest.c , a test for Graph.c. Just tests the basic functions

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[]) {

Graph G = newGraph(5);

printf("%d\n", getOrder(G));
printf("%d\n", getSize(G));
printf("%d\n", getParent(G, 5));
printf("%d\n", getDiscover(G, 1));
printf("%d\n", getFinish(G,1));



addArc(G,1,5);
printGraph(stdout,G);

addArc(G,2,4);
printGraph(stdout,G);

List L = newList();
for (int i = 1; i <=getOrder(G); i++) {
        append(L, i);
    }

DFS(G, L);
printList(stdout, L);

Graph H = copyGraph(G);
printGraph(stdout,H);

Graph J = transpose(G);
printGraph(stdout, J);

freeList(&L);
freeGraph(&G);
freeGraph(&H);
freeGraph(&J);

return 0;
}
