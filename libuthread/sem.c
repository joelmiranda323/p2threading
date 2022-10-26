#include <stddef.h>
#include <stdlib.h>

#include "queue.h"
#include "sem.h"
#include "private.h"

struct semaphore {
	/* TODO Phase 3 */
    size_t counter;
    queue_t queue;
};

sem_t sem_create(size_t count)
{
	/* TODO Phase 3 */
    //create a semaphore
    struct semaphore *sem = malloc(sizeof(struct semaphore));
    sem->counter = count;
    sem->queue = queue_create();

    return sem;
}

int sem_destroy(sem_t sem)
{
	/* TODO Phase 3 */
    if(sem == NULL || queue_length(sem->queue) > 0) {
        return -1;
    } else {
        free(sem);
        return 0;
    }
}

int sem_down(sem_t sem)
{
	/* TODO Phase 3 */
    //check if there is any resources available
    if(sem == NULL) {
        return -1;
    }
    
    if(sem->counter <= 0) {
        // if there is no resources available, get the current thread and add it to the queue and block it
        struct uthread_tcb *current = uthread_current();
        queue_enqueue(sem->queue,current);
        uthread_block();
    } else {
        //else decrement that the resource is being used
        sem->counter--;
        return 0;
    }

}

int sem_up(sem_t sem)
{
	/* TODO Phase 3 */

    //check if there is a thread in the queue waiting
    if(queue_length(sem->queue) > 0) {
        // get it from the queue and unblock it
        queue_dequeue(sem->queue, (void**)uthread_current());
        uthread_unblock(uthread_current());
    }

    //make the resource available again
    sem->counter++;
    return 0;

}

