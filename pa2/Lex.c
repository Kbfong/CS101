/*
 *  Kody Fong (1519213)
 *  kbfong
 *  PA 2
 *  Lex.java is a program that utilizes list.java to sort out a List lexicographically. Utilizes insertion sort as the core sorting method for the List. Same thing as PA 1 but done in C
 */ 
#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include <string.h>

#define MAX_LEN 255 //max num of characters possible in a line
int main(int argc, char *argv[])
{
    int count = 0; 
    int n = 0; 
    FILE *in;
    FILE *out;

    char line[MAX_LEN]; //an array that stores the line

    if(argc != 3) //if the amount of arguments isnt equal to 3, exit the program. Required, %Lex, <input> <output>
    {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    in = fopen(argv[1], "r"); //reads the input file
    out = fopen(argv[2], "w"); //writes the output file


    while(fgets(line, MAX_LEN, in) != NULL) //reads the lines from the file and increases the count until null is reached
    {
        count++;
    }

    rewind(in);//reset cursor to the start of file stream. https://www.tutorialspoint.com/c_standard_library/c_function_rewind.htm

    char lines[count][MAX_LEN];  //stores the lines
    

    while(fgets(line, MAX_LEN, in) != NULL)
    {
        strcpy(lines[n], line); //copies the strings from the lines and stores them into the array
        n++; //increments the count
    }

    List list = newList(); // create a new List

    append(list, 0); // appends the list

    //Insertion sort. Same as PA1 Insertion sort but in C
    for(int i = 1; i < count; i++)
    {
        char *temp = lines[i];
        int j = i - 1;
        moveBack(list);
        

        while(j >= 0 && strcmp(temp, lines[get(list)])<= 0)
        {
            
             movePrev(list);
             j--;
        }
        if(index(list) >= 0)
        {
            insertAfter(list, i);

        } 
        else
        {
          prepend(list, i); //prepends the list
        }
    }
    //Move the cursor back to the front of the list
    moveFront(list);
   
    //print out the list
    while(index(list) >= 0)
    {
        fprintf(out, "%s", lines[get(list)]);
        moveNext(list);
    }

    //close both files
    fclose(in);
    fclose(out);

    //free the list
    freeList(&list);

    //end program
    return 0;

}