#include <stdio.h>
#include <stdlib.h>
#include "pQueueLib.c"
int main()
{
    struct Node *start;
    int control = 1;
    while(control != 9)
    {
        printf("Press [1] to insert an element to the queue\n");
        printf("Press [2] to take out the first element from the queue\n");
        printf("Press [3] to read the first element of the queue\n");
        printf("Press [4] to print out the queue\n");
        printf("Press [5] to check if the queue is empty\n");
        printf("Press [6] to check if the queue is full\n");
        printf("Press [7] to delete the queue\n");
        printf("Press [8] to initialize the priority queue\n");
        printf("Press [9] to close the program\n");

        scanf("%d", &control);
        int value;
        int priority;
        switch (control)
        {
            case 1:
                if (checkFull(&start) != 1)
                {
                    printf("Enter a number to add to the queue:\n");
                    scanf("%d", &value);
                    printf("Enter the priority of the number:\n");
                    scanf("%d", &priority);
                    addElement(&start, value, priority);
                }
                else
                {
                    printf(ERROR1);
                }
                break;
            case 2:
                printf("Taking out the first element...:\n");
                printf("First element: %d\n", takeFirst(&start));
                break;
            case 3:
                printf("Reading the first element...:\n");
                printf("First element: %d\n", readFirst(&start));
                break;
            case 4:
                printf("Printing queue...\n");
                printQueue(start);
                break;
            case 5:
                if (checkEmpty(&start) == 1)
                {
                    printf(ERROR2);
                }
                else
                {
                    printf(ERROR4);
                }
                break;
            case 6:
                if (checkFull(&start) == 1)
                {
                    printf(ERROR1);
                }
                else
                {
                    printf(ERROR3);
                }
                break;
            case 7:
                printf("Deleting queue...\n");
                deleteQueue(&start);
                break;
            case 8:
                printf("Initializing the queue...\n");
                initializeList(&start);
                break;
            case 9:
                printf("Program closing...\n");
                return 0;
        }
    }
}

