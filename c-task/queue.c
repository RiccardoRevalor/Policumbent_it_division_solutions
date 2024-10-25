#include "queue.h"

//the queue structure
tyoedef struct Queue {
    void **data; //Array of void* pointers. I use void ** because the data can be of type GPGGA_Info_t, GNS_Info_t, GPRMC_Info_t
    int front;
    int rear;
    int size; //maxSize of the array
    int count;
} Queue;

//function to create a new queue
Queue *createQueue(int size) {
    /*Arguments
    size: the size of the queue
    Returns
    a pointer to the queue
    */
    Queue *queue = (Queue *)malloc(sizeof(struct Queue));
    queue->data = (void **)malloc(sizeof(void  *) * size);
    queue->front = -1; //front is -1 because the queue is empty
    queue->rear = -1;
    queue->size = size; //max size of the queue
    queue->count = 0; //number of elements in the the array
    return queue;
}

int getCount(Queue *queue){
    return queue->count; //return the number of elements in the queue
}

bool isEmpty(Queue *queue){
    if (queue->count == 0) {
        return true; //return true if the queue is empty
    }
}

bool isFull(Queue *queue){
    if (queue->count == queue->size) {
        return true; //return true if the queue is full
    }
}

//function to insert an element in the queue
bool enqueue(Queue *queue, void  *data){
    /*Arguments
    queue: the queue
    data: the data to be inserted
    Returns
    true if the data is inserted, false otherwise
    */

    //COMPLEXITY: O(1) - CONSTANT TIME

    //check if queue is full
    if (isFull(queue)) {
        return false; //return false if the queue is full -> no space to insert the data
    }

    //if the queue is empty, set front to 0
    if (isEmpty(queue)) {
        queue->front = 0;
    }

    //insert the data
    // Add the data to the queue at the rear pointer and move the rear pointer
    int maxSize = queue->size;
    queue->rear = (queue->rear + 1) % maxSize;
    queue->data[queue->rear] = data;

    //increment the count
    queue->count++;

    return true; //return true if the data is inserted
    
}

//function to remove an element from the queue
void *dequeue(Queue *queue){
    if (isEmpty(queue)) {
        return NULL; //return NULL if the queue is empty
    }

    //COMPLEXITY: O(1) - CONSTANT TIME

    //remove the data from the front of the queue
    void  *data = queue->data[queue->front];

    //update pointers
    //if front and rear are equal, the queue is empty
    //so, reset front and rear to -1
    if (queue->front == queue->rear) {
        queue->front = -1;
        queue->rear = -1;
        //empty queue
    } else {
        //move the front pointer
        int maxSize = queue->size;
        queue->front = (queue->front + 1) % maxSize;
    }

    //decrement the count
    queue->count--;

    return data; //return the data


}

//function to get (but without removing) the first element of the queue
void *peek(Queue *queue){
    if (isEmpty(queue)) {
        return NULL; //return NULL if the queue is empty
    }

    //COMPLEXITY: O(1) - CONSTANT TIME

    return queue->data[queue->front]; //return the data at the front of the queue
}


//function to print the queue
void printQueue(Queue *queue){
    if (isEmpty(queue)) {
        printf("Queue is empty\n"); //print "Queue is empty" if the queue is empty
        return;
    }

    //COMPLEXITY: O(n) - LINEAR TIME

    //print the queue
    //since the queue is circular, the print is performed from front to rear
    //front doiesn't always need to be zero
    int i = queue->front;
    int count = queue->count;
    for (int j = 0; j < count; j++) {
        printf("%d ", queue->data[i]);
        i = (i + 1) % queue->size;
    }
    printf("\n");
}


//function to de-allocate the queue
void freeQueue(Queue *queue){
    if (queue == NULL) {
        return; //return if the queue is NULL
    }

    for (int i = 0; i < queue->size; i++){
        if (queue->data[i] != NULL) {
            free(queue->data[i]); //free the data
        }
    }

    if (queue->data != NULL) {
        free(queue->data); //free the array
    }
}