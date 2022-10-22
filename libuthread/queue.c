#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#include "queue.h"

struct queue {
        /* TODO Phase 1 */
        queue_t child;
        void *data;
        int isEmpty;
};

queue_t queue_create(void) {
    /* TODO Phase 1 */
    queue_t queue = (queue_t) malloc(sizeof(queue_t));
    //queue->child = NULL;
    //queue->data = NULL;
    return queue;
}

int queue_destroy(queue_t queue) {
    /* TODO Phase 1 */
    if (queue == NULL || queue->child != NULL) {
        return -1;
    }

    free(queue->data);
    queue->data = NULL;

    free(queue);
    queue = NULL;

    return 0;
}

int queue_enqueue(queue_t queue, void *data) {
    /* TODO Phase 1 */
    if (queue == NULL || data == NULL) {
        return -1;
    }
    
    queue->data = data;
    return 0;
}

int queue_dequeue(queue_t queue, void **data) {
    /* TODO Phase 1 */
    if (queue == NULL || data == NULL) {
        return -1;
    }

}

int queue_delete(queue_t queue, void *data) {
    /* TODO Phase 1 */
}

int queue_iterate(queue_t queue, queue_func_t func) {
    /* TODO Phase 1 */
}

int queue_length(queue_t queue) {
    /* TODO Phase 1 */
}
