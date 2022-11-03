#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#include "queue.h"

/* node struct for the queue */
struct node{
    void *data;
    struct node *next;
};

struct queue {
    /* TODO Phase 1 */
    int size;
    struct node *front;
    struct node *rear;
};

queue_t queue_create(void)
{
    /* TODO Phase 1 */
    
    /* allocate memory */
    queue_t q = malloc(sizeof(struct queue));
    
    /* front and end points to null and assign the queue size to zero */
    q->front = 0;
    q->rear = 0;
    q->size = 0;
    return q;
}

int queue_destroy(queue_t queue)
{
    /* TODO Phase 1 */
    
    /* if the queue is null or if it is not empty return -1, else destroy it */
    if(queue == NULL || queue->size != 0) {return -1;}
    free(queue);
    return 0;
}

int queue_enqueue(queue_t queue, void *data)
{
    /* TODO Phase 1 */
    
    /* if the data or queue is null return -1 */
    if(queue == NULL || data == NULL) {
        return -1;
    }
    
    /* allocate and create a new node to add to the queue*/
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    
    /* assign the passed data to the new node and it will point to null since it will be added to the end of the queue */
    new_node->data = data;
    new_node->next = 0;
    
    /* if the queue is empty, make the front node pointer of the queue point to the new node. else, add it to the of the queue, and also increase the size */
    if(queue->size == 0) {
        queue->front = new_node;
        queue->rear = new_node;
        queue->size += 1;
    } else {
        queue->rear->next = new_node;
        queue->rear = new_node;
        queue->size += 1;
    }

    return 0;
}

int queue_dequeue(queue_t queue, void **data)
{
    /* TODO Phase 1 */
    
    // check if the queue or data is NULL
    if(queue == NULL || data == NULL) {
        return -1;
    }
    
    // make the passed pointer to point to the memory address of the data pointer of the front node
    *data = queue->front->data;
    
    // create a node named old that will point to the front. we save it here so we can destro it later
    struct node *old = 0;
    old = queue->front;
    
    // removing the front by make the next node the front. basically, remove the first node from the queue and decrease the size by one
    queue->front = queue->front->next;
    queue->size = queue->size - 1;
    
    // if there was only one node in the queue the front will be pointing to NULL after we remove it, so, we will also make the rear points to NULL
    if(queue->front == NULL) {
        queue->rear = NULL;
    }
    
    //destroy the node that was removed from the queue
    free(old);
    return 0;
}

int queue_delete(queue_t queue, void *data)
{
    /* TODO Phase 1 */
    
    // if the passed data is on the front of the queue, just remove it, decrement the size, and return 0. 
    if(queue->front->data == data) {
        queue->front = queue->front->next;
        queue->size = queue->size -1;
        return 0;
    }
    
    // the idea is to create two nodes current and previous to find the passed data
    struct node *current = queue->front->next;
    struct node *previous = queue->front;

    
    // go thought the each node of the queue using current and previous, check if the current points to the passed data? 
    for(int i=0; i < (queue->size - 1);i++){
        
        // if the current pointer points to passed data, remove and destry it and return 0;
        if(current->data == data) {
            previous->next = current->next;
            free(current);
            current = NULL;
            queue->size = queue->size - 1;
            return 0;
        }
        
        // looking for the pointer that points to the passed data
        if(current->next != 0) {
            current = current->next;
        }
        previous = previous->next;
    }
    
    // if not found, return -1.
    return -1;
}

int queue_iterate(queue_t queue, queue_func_t func)
{
     /* TODO Phase 1 */
    if(queue == NULL || func == NULL) {
        return -1;
    }
    
    // store size of the queue
    int actual = queue->size;
    
    // make a temp pointer to iterate through the queue
    struct node *temp = queue->front;
    
    //iterate through
    while(temp->next != NULL) {
        func(queue, temp->data);
        if(queue->size != actual ) {
            break;
        }

        temp = temp->next;
    }
    return 0;

}

int queue_length(queue_t queue)
{
    /* TODO Phase 1 */
    if(queue == NULL) {return -1;}
    
    // return the size if the queue is not null
    return queue->size;
}
