#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "Graph.h"

#define MAX_LEN 255

int main(int argc, char * argv[])
{
    
    char line[MAX_LEN];

    FILE *in;
    FILE *out;
    int source = 0;
    int destination = 0;
    int BFSsource = 0;
    int BFSdestination = 0;
    int numVertices =  0;
    


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


   
   fgets(line, MAX_LEN, in);
   //creates a graph with the input file amount of vertices
   sscanf(line, "%d", &numVertices);
   Graph G = newGraph(numVertices);

   //while the file is not null
   while( fgets(line, MAX_LEN, in) != NULL)
   {
      
      
      sscanf(line, "%d %d", &source, &destination); //scans the input file

      //if the input files source and destination is 0 break else add the edge to the graph
      if(source == 0 && destination == 0){


         break;
      }
      else{

        addEdge(G, source, destination); //adds the edge from the source to the destination vertex
      }
      
   }

   printGraph(out, G); //prints the graph
  

   //while the file is not null loop but does BFS on the graph
   while( fgets(line, MAX_LEN, in) != NULL)
   {
       

       sscanf(line, "%d %d", &BFSsource, &BFSdestination); //scans the input file

       if(BFSdestination == 0 && BFSsource == 0)
       {
           break;
       }
      
       

    List list = newList();
    BFS(G, BFSsource);
    getPath(list,G,BFSdestination);
   

     //if the distance is infinity
     //then print distance is infinity
    if(getDist(G,BFSdestination) == INF){

        fprintf(out, "The distance from %d to %d is infinity\n", BFSsource, BFSdestination);
    }

    else{

        fprintf(out, "The distance from %d to %d is %d\n", BFSsource, BFSdestination, getDist(G,BFSdestination));
        
    }
    
     //if the cursor element at the front of the list is nil then theres no such path
     moveFront(list);
     if(get(list) == NIL){

        fprintf(out, "No %d-%d path exists\n", BFSsource, BFSdestination);
    }
    //else print the shortest path
    else{

        fprintf(out, "A shortest %d-%d path is: ", BFSsource, BFSdestination);
        printList(out, list);
        fprintf(out, "\n");
    
    }
    
    freeList(&list);
   }

   freeGraph(&G);
   fclose(in);
   fclose(out);
   return (0);


}