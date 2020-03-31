//Kody Fong 1519213
//kbfong
//PA 2
//List ADT but in C. Follows the structure of List.java but implemented in C

#include <stdio.h>
#include <stdlib.h>
#include "List.h"



typedef struct NodeObj{
    int data;  
    struct NodeObj* prev;  
    struct NodeObj* next;  
} NodeObj;

typedef NodeObj* Node;


typedef struct ListObj {
    Node front;  
    Node back;  
    Node cursor;
    int index;  
    int length;  
} ListObj;


//creates a new node object and initializes the data, prev, and next
Node newNode(int value) {
    Node temp = malloc(sizeof(NodeObj));
    temp->data = value;
    temp->prev = NULL;
    temp->next = NULL;
    return(temp);
}

//frees the memory from the heap for the node then sets it to null
void freeNode(Node* pN)
{
    if( pN!=NULL && *pN!=NULL )
    {
        free(*pN);
        *pN = NULL;
    }
}


//creates new empty list
List newList(void) {
  List newList; 
  newList = malloc(sizeof(struct ListObj)); //allocates memory
  newList->front = NULL;
  newList->back = NULL;
  newList->cursor = NULL;
  newList->length = 0;
  newList->index = -1;
  return newList;
}

//frees the memory from the heap for the list and sets it to null
void freeList(List* pL)
{
    if(pL != NULL && *pL != NULL)
    {
        
        while ( length(*pL) > 0 ) 
        {
            deleteFront(*pL);  // delete front node in List
        }
        free(*pL); //frees the memory from the list.
        *pL = NULL; //sets pL to null.
    }
    
}


// Returns the number of elements in this List.
int length(List L)
{
    return (L->length); //returns the length


}

// If cursor is defined, returns the index of the cursor element, otherwise returns -1.
int index(List L)
{
    if(L->cursor == NULL)
    {
        return -1;
    }
    return L->index; //returns the index
}

// Returns front element. Pre: length()>0
int front(List L)
{
   if(L->length == 0)
   {
    printf("List Error: Calling front() on empty List");
    exit(1);
   }
   return (L->front->data); //returns the front 
}

// Returns back element. Pre: length()>0
int back(List L)
{
   if(L->length == 0)
   {
    printf("List Error: Calling back() on empty List");
    exit(1);
   }
   return (L->back->data); //returns the back
}

// Returns cursor element. Pre: length()>0, index()>=0
int get(List L)
{
    if (L->length ==0)
    {
        printf("List Error: Calling get() on empty List");
        exit(1);
    }
    if(L->cursor == NULL)
    {
        printf("List Error: Calling get() on cursor that is off the list");
        exit(1);
    }
    return (L->cursor->data); //returns the data at the cursor
}

//// Returns 1(true) if and only if  List A and B are the same integer sequence. Else return 0(false).
int equals(List A, List B)
{
    int isEqual = 1; //stores the return value after checking if the lists are equal
    Node aFront = A->front; //sets a temp node for the front node of List A
    Node bFront = B->front; //sets a temp node for the front node of List B
    if(A->length == B-> length) 
    {
        while( isEqual == 1 && aFront != NULL && bFront != NULL) //while the values are equal and the nodes aren't null
        {
            if (aFront->data == bFront->data) //if the data is the same go to the next node and check 
            {
                aFront = aFront->next; 
                bFront = bFront->next;
            }
            else
            {
                isEqual = 0; //if they're not equal then return 0 (false) and the loop ends.
            }
        }
        return isEqual;
    }
    else //the Lists aren't the same length therefore they cannot be equivalent so return 0.
    {
        isEqual = 0;
        return isEqual;
    }
}

// Manipulation procedures ----------------------------------------------------

// Resets this List to its original empty state.
void clear(List L)
{
   while (L->length > 0) {
        deleteFront(L);  // delete front node in List
    }
   L->front = NULL;
   L->back = NULL;
   L->cursor = NULL;
   L->length = 0;
   L->index = -1;
}

// If List is non-empty, places the cursor under the front element, otherwise does nothing.
void moveFront(List L)
{
   if(L->length !=0)
   {
    L->cursor = L->front;
    L->index = 0; //cursor will be at the front
   }
}

// If List is non-empty, places the cursor under the back element, otherwise does nothing.
void moveBack(List L)
{
    if(L->length !=0)
    {
        L->cursor = L->back;
        L->index = L->length - 1; //cursor will be at the back
    }
}

// If cursor is defined and not at front, moves cursor one step toward front of this List, if cursor is defined and at front, cursor becomes undefined, if cursor is undefined does nothing.
void movePrev(List L)
{
    if(L->cursor != NULL)
    {
        if(L->cursor == L->front)
        {
            L->cursor = NULL;
            L->index = -1;
        }
        else
        {
            L->cursor = L->cursor->prev; //moves cursor towards front of the list
            L->index--; //decrements the index
        }
    }
}

void moveNext(List L)
{
    if(L->cursor != NULL)
    {
        if(L->cursor == L->back)
        {
            L->cursor = NULL;
            L->index = -1;

        }
        else
        {
            L->cursor = L->cursor->next; //moves cursor towards the back of the list
            L->index++; //increments the index
        }
    }
}

// Insert new element into this List. If List is non-empty, insertion takes place before front element.
void prepend(List L, int data) 
{
    Node temp = newNode(data);
    if (L->length != 0) 
    {
        L->front->prev = temp; //the front of the list's previous becomes the temp node making the temp node first in the list
        temp->next = L->front; //the temp nodes next will be the original front of the list
        L->front = temp;       //the new front of the list becomes the temp node
        L->index++;
        L->length++;
    }
    else //the list is empty so just add to the list
    {  
        L->front = L->back = L->cursor = temp; 
        L->index = 0;
        L->length++;
    }
 
}

// Insert new element into this List. If List is non-empty, insertion takes place after back element.
void append(List L, int data) 
{
    Node temp = newNode(data);
    if (L->length != 0) 
    {
        temp->prev = L->back; //sets the temp node's previous value to the original back of the list
        L->back->next = temp; //the back of the list's next value will be the temp node
        L->back = temp;       //the new back of the list becomes the temp node
        L->length++;
        
    } 
    else 
    {  // the list is empty so just add to the list
        L->front = L->back = L->cursor = temp;
        L->index = 0;
        L->length++;
    }
    
}

// Insert new element before cursor. Pre: length()>0, index()>=0
void insertBefore(List L, int data)
{
    
    if(L->length == 0)
    {
        printf("List Error: Cannot call insertbefore() on empty list");
        exit(1);
    }

    if(L->cursor == NULL)
    {
        printf("List Error: Cannot call insertbefore() on cursor that is off the list");
        exit(1);
    }

    if(L->cursor == L->front)
    {
        prepend(L, data); //if the cursor is at the front of the list, you can just call prepend since you will be inserting the element before the front element 
    }
    else
    {
        Node temp = newNode(data);
        temp->prev = L->cursor->prev; //the temp nodes previous will become the cursor's previous
        temp->next = L->cursor;       //the temp nodes next will be the cursor
        L->cursor->prev->next = temp;  //cursors previous next element will be temp
        L->cursor->prev = temp;        //cursors previous will be temp
        L->length++;
        L->index++;
    }
}   

// Inserts new element after cursor. Pre: length()>0, index()>=0
void insertAfter(List L, int data)
{
    
    if(L->length == 0)
    {
        printf("List Error: Cannot call insertAfter() on empty list");
        exit(1);
    }

    if(L->cursor == NULL)
    {
        printf("List Error: Cannot call insertAfter() on cursor that is off the list");
        exit(1);
    }

    if(L->cursor == L-> back)
    {
        append(L, data); //if the cursor is at the back of the list then you can just all append since you will be inserting the element into the back element
    }

    else
    {
        Node temp = newNode(data); 
        temp->next = L->cursor->next; //the new node temp's next will be the cursor's next
        temp->prev = L->cursor;       //the new node temp's previous will become the cursor
        L->cursor->next->prev = temp; //cursor's next previous element becomes temp
        L->cursor->next = temp;       //cursor's next becomes temp
        L->length++;
    }

}

// Deletes the front element. Pre: length()>0
void deleteFront(List L) 
{
    if(L->length == 0 )
    {
        printf("List Error: Cannot call deleteFront() on empty list");
        exit(1);
    }
    if (L->length== 1) 
    {
        Node temp = L->front; //temp node becomes equal to the front
        L->front = L->cursor = L->back = NULL;
        L->index = -1;
        L->length = 0;
        freeNode(&temp);
    } 
    else 
    {
        if (L->cursor == L->front) 
        {
             L->cursor = NULL;
             L->index = -1;
        } 
       
    Node temp = L->front; //creates a node and sets it equal to the front of the list
    L->front = L->front->next; //the front of the list becomes the next value within the list
    L->front->prev = NULL; //the previous element in the front becomes null , the temp node becomes null 
    L->length--;
    L->index--;
    freeNode(&temp); //frees the memory from the temp nodes
        
    }
}

// Deletes the back element. Pre: length()>0
void deleteBack(List L) 
{
    if(L->length ==0)
    {
        printf("List Error: Cannot call deleteBack() on empty list");
        exit(1);
    }
    if (L->length == 1) 
    {
         Node temp = L->back; //temp nodes becomes equal to the back
         L->front = L->cursor = L->back = NULL;
         L->index= -1;
         L->length = 0;
         freeNode(&temp);
    } 
    else 
    {
        if (L->cursor == L->back)
         {
            L->cursor = NULL;
            L->index = -1;
         }
            Node temp = L->back; //creates  a node and sets it equal to the back of the list
            L->back = L->back->prev; //the new back of the list becomes the previous value within the list
            L->back->next = NULL; //the next element in the back of the list becomes null, the temp node becomes null
            L->length--;
            freeNode(&temp);
        }
    
}

// Deletes cursor element, making cursor undefined. Pre: length()>0, index()>=0
void delete(List L) 
{
    if(L->length == 0 )
    {
        printf("List Error: Cannot call delete() on empty list");
        exit(1);
    }

    if(L->cursor == NULL)
    {
        printf("List Error: Cannot call delete() on cursor that is off the list");
        exit(1);
    }
    
    if(L->cursor == L->front)
    {
        deleteFront(L); //deletes the front if the cursor is at the front
    }

    else if(L->cursor == L->back)
    {
        deleteBack(L); //deletes the back if the cursor is at the back
    }
    else
    {
        Node temp = L->cursor; //sets temp node to the cursor
        L->cursor->prev->next = L->cursor->next; //the cursors previours next becomes the cursors next
        L->cursor->next->prev = L->cursor->prev; //the cursors next's previous becomes the cursors previous
        L->cursor = NULL;
        L->index = -1;
        L->length--;
        freeNode(&temp);

    }
    
}


// Prints List
void printList(FILE* out, List L)
{
    Node temp = L->front; //sets a temp node equal to the front of the list
    int i = 0; //counter
    while(temp != NULL)   //while the temp node isn't null print the values within the list
    {
        if(i !=0){
         fprintf(out, " %d", temp->data); //print out the value of the node's data within the list
        }
      else{

        fprintf(out, "%d", temp->data);
        

      }
      temp = temp->next;  //move on to the next value within the list
      i++;
        
    }     
}

// Returns a new List representing the same integer sequence as this List. The cursor in the new list is undefined, regardless of the state of the cursor in this List. This List is unchanged.
List copyList(List L)
{
    List n = newList(); //creates a new list
    Node temp = L->front; //creates a node and sets it equal to the front of the list
    while(temp!= NULL) //while the temp node isn't null copy the values into the list
    {
        append(n,temp->data); //appends the data from the current node onto the list
        temp = temp->next; //move to the next value within the list
    }
    return n; //returns the new list after being copied
}
