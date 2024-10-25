/*
BONUS QUESTION: 
Implement a circular queue as an First-Class ADT through the files queue.h and queue.c, and instantiate 3 queues for each message of size 10. 
In addition to printing, store the data in the corresponding queues. 
In order to get the size of GPGGA_Info_t, GNS_Info_t and GPRMC_Info_t (they are structs), use the function size(). 
Assume that you can use the heap, so you can use the malloc, free ecc.
*/

//IT IMPLEMENTS A CIRCULAR QUEUE AS A FIRST-CLASS ADT
//CIRCULAR QUEUE = FIFO QUEUE BUT REAR AND FRONT ARE CONNECTED

#include <stdio.h>
#include <stdlib.h>
#inclide "gnss_parser.h"

//circular queue structure
typedef struct Queue *Queue;

//function to create a new queue
Queue *createQueue(int size);

//function to insert an element in the queue
bool enqueue(Queue *queue, void  *data);

//function to remove an element from the queue
void *dequeue(Queue *queue);

//function to get (but without removing) the first element of the queue
void *peek(Queue *queue);

//function to check if the queue is empty
bool isEmpty(Queue *queue);

//function to check if the queue is full
bool isFull(Queue *queue);

//function to print the queue
void printQueue(Queue *queue);

//function to de-allcoate the queue
void freeQueue(Queue *queue);

//function to get the total count of the queue
int getCount(Queue *queue);