#ifndef PQUE_H
#define PQUE_H
#include <stdio.h>
#include <stdlib.h>

//Error codes:
#define ERROR1 "Queue is full!\n"
#define ERROR2 "Queue is empty!\n"
#define ERROR3 "Queue isn't full\n"
#define ERROR4 "Queue isn't empty\n"

//Change this define to adjust maximum queue capacity
#define maxValue 10

struct Node
{
    int data;
    int prio;
    struct Node *next;
};
void initializeList(struct Node **start);
void addElement(struct Node **start, int value, int priority);
int takeFirst(struct Node **start);
int readFirst(struct Node **start);
void printQueue(struct Node *start);
int checkEmpty(struct Node **start);
int checkFull(struct Node **start);
void deleteQueue(struct Node **start);
#endif
