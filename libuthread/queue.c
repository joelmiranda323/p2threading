#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#include "queue.h"

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
    queue_t q = malloc(sizeof(struct queue));
    q->front = 0;
    q->rear = 0;
    q->size = 0;
    return q;
}

int queue_destroy(queue_t queue)
{
    /* TODO Phase 1 */
    if(queue == NULL) {return -1;}
    free(queue);
    return 0;
}

int queue_enqueue(queue_t queue, void *data)
{
    /* TODO Phase 1 */
    if(queue == NULL || data == NULL) {
        return -1;
    }

    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = 0;

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
    if(queue == NULL || data == NULL) {
        return -1;
    }

    *data = queue->front->data;

    struct node *old = 0;
    old = queue->front;

    queue->front = queue->front->next;
    queue->size = queue->size - 1;
    if(queue->front == NULL) {
        queue->rear = NULL;
    }

    free(old);
    return 0;
}

int queue_delete(queue_t queue, void *data)
{
    /* TODO Phase 1 */
    if(queue->front->data == data) {
        queue->front = queue->front->next;
        queue->size = queue->size -1;
        return 0;
    }
    struct node *current = queue->front->next;
    struct node *previous = queue->front;


    for(int i=0; i < (queue->size - 1);i++){
        if(current->data == data) {
            previous->next = current->next;
            free(current);
            current = NULL;
            queue->size = queue->size - 1;
            return 0;
        }

        if(current->next != 0) {
            current = current->next;
        }
        previous = previous->next;
    }

    return -1;
}

int queue_iterate(queue_t queue, queue_func_t func)
{
     /* TODO Phase 1 */
    if(queue == NULL || func == NULL) {
        return -1;
    }
    int old_size = queue->size;

    struct node *temp = queue->front;
    while(old_size == queue->size) {
        func(queue, temp->data);
        temp = temp->next;
    }

    return 0;

}

int queue_length(queue_t queue)
{
    /* TODO Phase 1 */
    if(queue == NULL) {return -1;}
    return queue->size;
}
