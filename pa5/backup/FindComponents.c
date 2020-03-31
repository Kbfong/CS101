//Kody Fong 1519213
//kbfong
//PA 5
//Runs Graph.c and DFS using input and output files.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"
#include"Graph.h"

int main(int argc, char* argv[]) 
{
    FILE *in; 
    FILE *out;
    int n = 0; // number of vertices
    List L = newList();
     int u;
     int v;


    // first check if there are 3 arguments exactly
     if(argc != 3)
    {
        printf("Invalid number of arguments %s \n", argv[0]);
        exit(1);
    }

    
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");

   if(in == NULL)
    {
        printf("Cannot open file %s \n", argv[1]);
        exit(1);
    }

    if(out == NULL)
    {
        printf("Cannot open file %s\n", argv[2]);
        exit(1);
    }


    //scans in the number of vertices
    fscanf(in, "%d", &n);
    //creates graph with n vertices
    Graph G = newGraph(n);


 // put all vertices into a List
    
    for (int i = 1; i <= n; i++) 
    {
        append(L, i);
    }
    
    //while the file is still valid, addArcs to the graph; make the graph
    while (fgetc(in) != EOF) 
    {
        fscanf(in, "%d", &u); //scans in the first input vertex
        fscanf(in, "%d", &v); //scans in the second input vertex
        if (u == 0 && v == 0) 
        {
            break;
        }
        addArc(G, u, v);
    }

  
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    fprintf(out, "\n");

    //runs DFS on Graph G with List L
    DFS(G, L);

    //creates the transpose of G then runs DFS on it
    Graph trans = transpose(G);
    DFS(trans, L);

    
    int connected = 0; //stores the scc strong connected components

    // increments the number of scc everytime a parent node of the transpose graph is nil
    for (int i = 1; i <= getOrder(trans); i++)
    {
        if(getParent(trans, i) == NIL) 
        {
            connected++; 
        }
    }
    fprintf(out, "G contains %d strongly connected components:\n", connected);

    //creates a new temp list that will be used to get the rest of the components
    //my list was originally printing backwards so start from the back and iterate to the front

    List temp = newList();

    moveBack(L); //move to the back of the original List
    int scc  = 1; //stores found components

    while(index(L) >= 0){ //while the index is still inbounds

    prepend(temp, get(L)); //add to the list

    if(getParent(trans, get(L)) == NIL){ 

        fprintf(out, "Component %d: ", scc);
        printList(out, temp);
        fprintf(out, "\n");
        clear(temp);
        scc++;
    }
        movePrev(L); //moves to the previous node in L
    }

    //free memory from the heap
    freeList(&L);
    freeList(&temp);
    freeGraph(&trans);
    freeGraph(&G);
    fclose(in); 
    fclose(out);
    
    return(0);
}