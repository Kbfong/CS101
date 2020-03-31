//Kody Fong 1519213
//kbfong
//PA 5
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
	int *discover;  //discover
	int *finish; //finish

	int order;   //num vertices
	int size;    //num edges
	

}GraphObj;

typedef GraphObj* Graph;

//creates a new graph with n vertices and no edges
Graph newGraph(int n){

	Graph G = malloc(sizeof(GraphObj)); 
	G->adjacent = calloc(n+1,sizeof(List));	
	G->color = calloc(n+1, sizeof(int));
	G->parent = calloc(n+1, sizeof(int));
	G->discover = calloc(n+1, sizeof(int));
	G->finish = calloc(n+1, sizeof(int));

	G->order = n;
	G->size = 0;

	for(int i = 0; i < n + 1; i++){

		G->adjacent[i] = newList();
		G->color[i] = WHITE;
		G->parent[i] = NIL; // 0
		G->discover[i] = UNDEF; //-1
		G->finish[i] = UNDEF; //-1
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
    free(temp->color);
    free(temp->discover);
    free(temp->finish);

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

/*
//returns the source vertex
int getSource(Graph G){

	if(G == NULL){

		printf("Graph Error: called getSource() on NULL graph");
		exit(1);
	}

	return G->source;
}

*/


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

//returns the discover from the parent u
int getDiscover(Graph G, int u){

	if (G == NULL) 
    {
        printf("Graph error: called getDiscover() on NULL Graph");
        exit(1);
    }

     if(u < 1 || u > getOrder(G))
    {
        printf("Graph Error: cannot call getDiscover(), u is out of bounds ");
        exit(1);
    }

    

    return G->discover[u];
}

//returns finish from parent u
int getFinish(Graph G, int u){

	if (G == NULL) 
    {
        printf("Graph error: called getFinish() on NULL Graph");
        exit(1);
    }

     if(u < 1 || u > getOrder(G))
    {
        printf("Graph Error: cannot call getFinish(), u is out of bounds ");
        exit(1);
    }

    

    return G->finish[u];
}

/*
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

*/
	

/*
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

*/



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

// helper function for DFS()		 Following the pa5 pdf instructions
void visit(Graph G, List S, int u, int *time) 
{
    
    G->discover[u] = ++*time; //when the vertex is just discovered increment time
    G->color[u] = GRAY; //the color will become gray after being visited
    moveFront(G->adjacent[u]); //move to the front of the adjacent list at u

    while (index(G->adjacent[u]) >= 0) //while index still inbounds
    {
        int temp = get(G->adjacent[u]);
        
        if (G->color[temp] == WHITE) //if undiscovered, discover it
        {
            G->parent[temp] = u; //the parent node of the vertex becomes u
            visit(G, S, temp, time);
        }
        moveNext(G->adjacent[u]);
    }
    G->color[u] = BLACK; //finished the visit
    G->finish[u] = ++*time ; //increment time again
    prepend(S, u); //add to the list
}


void DFS(Graph G, List S) 
{
    
    //makes all nodes undiscovered
    for (int i = 1; i <= getOrder(G); i++) 
    {
        G->color[i] = WHITE; 
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
    	G->finish[i] = UNDEF;
    }
    int time = 0; //set the time to 0
    moveFront(S); //move to the front of the list

    while (index(S) >= 0) //while the index is still inbounds
    {
        int u = get(S);
        //if the color of u is white, its undiscovered so visit it

        if (G->color[u] == WHITE) 
        {
            visit(G, S, u, &time);
        }
        moveNext(S); //move to the next node in the list
    }

    //delete the contents from the list
    for (int i = 1; i <= getOrder(G); i++) 
    {
        deleteBack(S);
    }
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

//returns the transpose of the graph
Graph transpose(Graph G) 
{
    Graph transpose = newGraph(getOrder(G));
    for (int i = 1; i <= getOrder(G); i++) 
    {
        moveFront(G->adjacent[i]); //move to front of the adjacent list
        while (index(G->adjacent[i]) >= 0)  //while the index is still inbounds
        {
                addArc(transpose, get(G->adjacent[i]), i); //swaps the locations of the adjacent list and i within the graph creating the transpose
                moveNext(G->adjacent[i]); //moevs to the next value in the adjacent list
        }
        
    }
    return transpose;
}

//returns a copy of the graph
Graph copyGraph(Graph G) 
{
    Graph copy = newGraph(getOrder(G));
    for (int i = 1; i <= getOrder(G); i++) 
    {
        moveFront(G->adjacent[i]); //move to front of the adjacent list
        while (index(G->adjacent[i]) >= 0)  //while the index is still inbounds add an arc to the copy graph at indices i of the adjacent list
        {
              addArc(copy, i, get(G->adjacent[i]));
              moveNext(G->adjacent[i]); //move to the next value in the adjacent list
        }
        
    }
    return copy;
}