//Tadas Verbyla
//Priority Queue library
//Contains following functions:
//initializeList - prepares the priority queue for further functions
//addElement - inserts a provided int value to the queue according to the provided int priority from smallest to highest
//takeFirst - returns the value of the first element of the queue, while removing it from the queue
//readFirst - returns the value of the first element of the queue, while keeping it in front of the queue
//printQueue - for testing purposes, it prints out the values of all elements in the queue
//checkEmpty - returns 1 if the queue has no elements and 0 if not
//checkFull - returns 1 if the queue reached the defined maxValue of elements or if there is not enough memory for a new element, 0 if neither
//deleteQueue - frees the allocated memory to the queue and thus deletes its elements (queue remains initialized)

//Usage:
//To use this library, you must #include "pQueueHead.h", its header file, and <stdio.h>, <stdlib.h> standard C libraries
//The queue is used via created Struct node variable, that has to be provided to the functions along with other values if necessary

#include <stdio.h>
#include <stdlib.h>
#include "pQueueHead.h"
void initializeList(struct Node **start)
{
    *start = NULL;
}
void addElement(struct Node **start, int value, int priority)
{
    struct Node *elemK;
    struct Node *elem = (struct Node*) malloc(sizeof(struct Node));
    elem -> data = value;
    elem -> prio = priority;
    elem -> next = NULL;
    if ((*start) == NULL)
    {
        (*start) = elem;
        return;
    }
    if (priority < (*start) -> prio)
    {
        elem -> next = *start;
        *start = elem;
        return;
    }
    elemK = *start;
    int k = 1;
    while ((priority > elemK -> prio) && (elemK != NULL))
    {
        elemK = elemK -> next;
        ++k;
        if (elemK == NULL)
        {
            break;
        }
    }
    if (k == 1)
    {
        elem -> next = (*start) -> next;
        (*start) -> next = elem;
        return;
    }
    else
    {
        elemK = *start;
        for (int i = 1; i < k - 1; ++i)
        {
            elemK = elemK -> next;
        }
    }
    elem -> next = elemK -> next;
    elemK -> next = elem;
    return;
}
int takeFirst(struct Node **start)
{
    int first = (*start) -> data;
    *start = (*start) -> next;
    return first;
}
int readFirst(struct Node **start)
{
    int first = (*start) -> data;
    return first;
}
void printQueue(struct Node *start)
{
    struct Node *elem;
    elem = start;
    while (elem != NULL)
    {
        printf("%d ", elem -> data);
        elem = elem -> next;
    }
    printf("\n");
    return;
}
int checkEmpty(struct Node **start)
{
    if (*start == NULL)
    {
        return 1;
    }
    return 0;
}
int checkFull(struct Node **start)
{
    struct Node *elemK;
    void* ptr = malloc(sizeof(struct Node));
    if (ptr == NULL)
    {
        return 1;
    }
    else
    {
        free(ptr);
    }
    int elCount = 0;
    elemK = *start;
    while (elemK != NULL)
    {
        ++elCount;
        elemK = elemK -> next;
    }
    if (elCount >= maxValue)
    {
        return 1;
    }
    return 0;
}
void deleteQueue(struct Node **start)
{
    struct Node *elem = (*start);
    struct Node *elemK;
    while (elem != NULL)
    {
        elemK = elem -> next;
        free(elem);
        elem = elemK;
    }
    (*start) = NULL;
    return;
}
