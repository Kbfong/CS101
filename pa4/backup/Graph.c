//Kody Fong 1519213
//kbfong
//PA 4
//Graph ADT in C

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

#define WHITE 1
#define GRAY 2
#define BLACK 3


typedef struct GraphObj{

	List *adjacent; //neighbors/adjacent lists
	int *color;     //color array
	int *parent;    //parent array
	int *distance;  //distance array

	int order;   //num vertices
	int size;    //num edges
	int source; //source for BFS

}GraphObj;

typedef GraphObj* Graph;

//creates a new graph with n vertices and no edges
Graph newGraph(int n){

	Graph G = malloc(sizeof(GraphObj)); 
	G->adjacent = calloc(n+1,sizeof(List));	
	G->color = calloc(n+1, sizeof(int));
	G->parent = calloc(n+1, sizeof(int));
	G->distance = calloc(n+1, sizeof(int));

	G->order = n;
	G->size = 0;
	G->source = NIL;
	for(int i = 0; i < n + 1; i++){

		G->adjacent[i] = newList();
		G->color[i] = WHITE;
		G->parent[i] = NIL;
		G->distance[i] = INF;
	}
	return G;
} 

//frees the memory from the graph, following the structure from List.c
void freeGraph(Graph* pG){

	if(pG != NULL && *pG !=NULL){
		Graph temp = *pG;
		for(int i = 0; i <(temp->order + 1); i++ ){

			freeList(&(temp->adjacent[i]));

		}

	free(temp->adjacent);
    free(temp->parent);
    free(temp->distance);
    free(temp->color);
    free(*pG);
    *pG = NULL;
	}


}


//returns the num of vertices
int getOrder(Graph G){

	if(G == NULL){

		printf("Graph Error: called getOrder() on NULL graph");
		exit(1);
	}

	return G->order;
}

//returns the number of edges
int getSize(Graph G){


	if(G == NULL){

		printf("Graph Error: called getSize() on NULL graph");
		exit(1);
	}

	return G->size;
}

//returns the source vertex
int getSource(Graph G){

	if(G == NULL){

		printf("Graph Error: called getSource() on NULL graph");
		exit(1);
	}

	return G->source;
}

//returns the parent u
int getParent(Graph G, int u) {

	if(G == NULL){

		printf("Graph Error: called getParent() on NULL graph");
		exit(1);
	}
	 if(u < 1 || u > getOrder(G))
    {
        printf("Graph Error: cannot call getParent(), u is out of bounds ");
        exit(1);
    }
	return G->parent[u];
}

//returns the distance from the parent u
int getDist(Graph G, int u){

	if (G == NULL) 
    {
        printf("Graph error: called getDist() on NULL Graph");
        exit(1);
    }

     if(u < 1 || u > getOrder(G))
    {
        printf("Graph Error: cannot call getDist(), u is out of bounds ");
        exit(1);
    }

    if(getSource(G) == NIL){

    	return INF;
    }

    return G->distance[u];
}

//gets the shortest path from G to U if possible
void getPath(List L, Graph G, int u){

	if (G == NULL) 
    {
        printf("Graph error: called getPath() on NULL Graph");
        exit(1);
    }

     if(u < 1 || u > getOrder(G))
    {
        printf("Graph Error: cannot call getPath(), u is out of bounds ");
        exit(1);
    }

    if(u == getSource(G)){

    	append(L, getSource(G)); //appends the shortest path from G to u into the list
    }

    else if( G->parent[u] == NIL){

    	append(L, NIL); //if the parent source is nil, append Nil into the list

    }

    else{ //get the path

    	getPath(L, G, G->parent[u]);
    	append(L,u);
    }

}

//empties the graph
void makeNull(Graph G) {

	if (G == NULL) 
    {
        printf("Graph error: called makeNull() on NULL Graph");
        exit(1);
    }

    for(int i = 0; i < (G->order + 1); i++){

    	clear(G->adjacent[i]); //rids the graph of the adjacent lists

    }
    G->size = 0; //sets the number of edges back to 0

}

//adds a directed edge from u to v
void addArc(Graph G, int u, int v){


   if(G == NULL)
    {
        printf("Graph Error: called addArc() on NULL Graph");
        exit(1);
    }
     if(u < 1 || u > getOrder(G))
    {
        printf("Graph Error: cannot call addArc(), u is out of bounds ");
        exit(1);
    }
         if(v < 1 || v > getOrder(G))
    {
        printf("Graph Error: cannot call addArc(), v is out of bounds ");
        exit(1);
    }

    moveFront(G->adjacent[u]); //moves to front of the adjacent list

    //a loop that constantly checks that the cursor is not off the adjacent list
    //and the value of v is greater than the value at the  indices of the adjacent list

    while(index(G->adjacent[u]) >= 0 && v > get(G->adjacent[u])){

    	moveNext(G->adjacent[u]); //constantly moves through the adjacent list

    }

    if(index(G->adjacent[u]) == -1) {

    	append(G->adjacent[u], v ); //once the cursor hits the end of the list append v onto the list
    }

    else{

    	insertBefore(G->adjacent[u], v); //if the cursor isn't off the list, insert v before the current cursor at u in the adjacent list
    }

	G->size++; 
}


//adds an edge that connects u to v
void addEdge(Graph G, int u, int v) {

	if(G == NULL)
    {
        printf("Graph Error: called addArc() on NULL Graph");
        exit(1);
    }
     if(u < 1 || u > getOrder(G))
    {
        printf("Graph Error: cannot call addArc(), u is out of bounds ");
        exit(1);
    }
         if(v < 1 || v > getOrder(G))
    {
        printf("Graph Error: cannot call addArc(), v is out of bounds ");
        exit(1);
    }

    addArc(G, u, v); //joins the directed edge
    addArc(G, v, u); //joins the directed edge

    G->size--; //since the edges are now connected/joined into one, we must decrement the amount of edges

}

//BFS algorithm from class implemented onto the Graph
void BFS(Graph G, int s){


	for(int i = 1; i < (G->order + 1); i++){

		G->color[i] = WHITE; 
		G->distance[i] = INF;
		G->parent[i] = NIL;
	}

	List L = newList();
	G->source = s; //the graph's source vertex becomes s
	G->color[s] = GRAY; //the color of the source vertex is gray
	G->distance[s] = 0; //distance becomes 0 since it is the parent
	G->parent[s] = NIL; //parent becomes nil because it is the parent

	append(L, s); //insert the vertex into the list

	while(length(L) > 0){

		moveFront(L); //move to the front of the list
		int u = get(L); //stores u as the cursor element of L
		delete(L); //deletes the cursor element in L
		moveFront(G->adjacent[u]); //moves to the front of the adjacent list at u

		while(index(G->adjacent[u]) >= 0) { //while the cursor is not off the list

			int v = get(G->adjacent[u]); //stores v as the cursor element of the adjacent list at u

			if(G->color[v] == WHITE){ //if the node in the list is unvisited

				G->color[v] = GRAY; //the node becomes visited and the color becomes gray
				G->distance[v] = G->distance[u] + 1; //increment distance
				G->parent[v] = u; //the parent node now becomes u
				
				append(L, v);
			}

			moveNext(G->adjacent[u]); //move to the next node in the list

		}

		G->color[u] = BLACK;

	}
	freeList(&L); //frees the list at the end
}


//prints the graph
void printGraph(FILE* out, Graph G){


	if(out == NULL || G == NULL){

		printf("Graph error: printGraph() called on NULL graph or NULL out file");
	}

	for(int i = 1; i < (G->order + 1); i++){

		fprintf(out, "%d: ", i);
		printList(out, G->adjacent[i]); 
		fprintf(out, "\n");

	}
}