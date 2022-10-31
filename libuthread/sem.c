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

	//check if the allocation was successful
	if(sem == NULL) {
		return NULL;
	}

	//assign the counter and create the queue for blocked threads
	sem->counter = count;
	sem->queue = queue_create();

	return sem;
}

int sem_destroy(sem_t sem)
{
	/* TODO Phase 3 */
    
	// fails if there is any thread in the queue waiting for resources available or sem is NULL
	if(sem == NULL || queue_length(sem->queue) > 0) {
		return -1;
	} else {
		//else destroy the queue and semaphore
		queue_destroy(sem->queue);
		free(sem);
    		return 0;
    	}
}

int sem_down(sem_t sem)
{
	/* TODO Phase 3 */

	if(sem == NULL) {
		return -1;
	}

	//if resource not available, put the current thread in the waiting queue and block it
	if(sem->counter == 0) {
		queue_enqueue(sem->queue,uthread_current());
		uthread_block();
		return 0;
	} else {
		//else decrement that the resource is being used
		sem->counter--;
		return 0;
	}
}

int sem_up(sem_t sem)
{
	/* TODO Phase 3 */
	
	// fails if sem is NULL
	if(sem == NULL) {
        	return -1;
	}
	
	//check if there is a thread in the queue waiting for resources
	if(queue_length(sem->queue) > 0 && sem->counter == 0) {
        	//if yes, get the first thread in the queue and unblock it
        	struct uthread_tcb *first;
        	queue_dequeue(sem->queue, (void**) &first);
        	uthread_unblock(first);
		return 0;
    	} else {
		// else, increment the counter indicating that the resource is available
        	sem->counter++;
		return 0;
    	}
}

