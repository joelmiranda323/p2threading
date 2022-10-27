#include <assert.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "private.h"
#include "uthread.h"
#include "queue.h"

#define READY	0
#define	RUNNING	1
#define BLOCKED	2
#define EXIT	3

// Race condtions
// We need to use a lock for these
queue_t qThread;
struct uthread_tcb *currentThread;

struct uthread_tcb {
	/* TODO Phase 2 */
	int state;
	uthread_ctx_t *context;
	void *stack;
};

struct uthread_tcb *uthread_current(void)
{
	/* TODO Phase 2/4 */
	return currentThread;
}

void uthread_yield(void)
{
	/* TODO Phase 2 */

	// Get currrent running thread which change to a READY state
	struct uthread_tcb *prevThread = uthread_current();

	// yield: from RUNNING to READY
	if (prevThread->state == RUNNING) {
		// Currrent running thread is now yielding
		prevThread->state = READY;

		// Add yeilding thread to the queue
		queue_enqueue(qThread, (void *) prevThread);
	}
	else {
		// print the state of the current thread
		perror("uthread_yield(): prevThread");
		printf("State of current thread: %d\n", prevThread->state);
	}

	// Get the oldest thread from queue which will change to a RUNNING state
	struct uthread_tcb *nextThread;
	queue_dequeue(qThread, (void **) &nextThread);

	// Elect oldest thread to run: READY to RUNNING
	if (nextThread->state == READY) {
		// Oldest thread is now the current running thread
		nextThread->state = RUNNING;
		currentThread = nextThread;
	}
	else {
		// print the state of the oldest thread
		perror("uthread_yield(): nextThread");
		printf("State of oldest thread: %d\n", nextThread->state);
	}

	// Save yielding threads context and activate current threads context
	uthread_ctx_switch(prevThread->context, nextThread->context);
}

void uthread_exit(void)
{
	/* TODO Phase 2 */

	// Get currrent running thread
	struct uthread_tcb *prevThread = uthread_current();

	// Exit current running thread
	prevThread->state = EXIT;
	free(prevThread->context);
	free(prevThread->stack);

	// Get the oldest thread from queue which will change to a RUNNING state
	struct uthread_tcb *nextThread;
	queue_dequeue(qThread, (void **) &nextThread);

	// Elect oldest thread to run: READY to RUNNING
	if (nextThread->state == READY) {
		// Oldest thread is now the current running thread
		nextThread->state = RUNNING;
		currentThread = nextThread;
	}
	else {
		// print the state of the oldest thread
		perror("uthread_exit()");
		printf("State of oldest thread: %d\n", nextThread->state);
	}

	// Save yielding threads context and activate current threads context
	uthread_ctx_switch(prevThread->context, nextThread->context);
}

int uthread_create(uthread_func_t func, void *arg)
{
	/* TODO Phase 2 */

	// Create a new thread
	int ctxInitStatus;
	struct uthread_tcb *newThread = (struct uthread_tcb *) malloc(sizeof(struct uthread_tcb));

	if (newThread == NULL) {
		perror("uthread_create()");
		printf("could NOT allocate memory for newThread\n");
		return -1;
	}
	
	newThread->state = READY;
	newThread->context = (struct uthread_ctx_t *) malloc(sizeof(uthread_ctx_t));
	newThread->stack = uthread_ctx_alloc_stack();

	if (newThread->context == NULL) {
		perror("uthread_create()");
		printf("could NOT allocate memory for newThread->context\n");
		return -1;
	}
	else if (newThread->stack == NULL) {
		perror("uthread_create()");
		printf("could NOT allocate memory for newThread->stack\n");
		return -1;
	}

	// Initiate the new threads context
	ctxInitStatus = uthread_ctx_init(newThread->context, newThread->stack, func, arg);

	if(ctxInitStatus == -1) {
		perror("ctxInitStatus in uthread_create()");
		return -1;
	}

	// Add the new thread to the ready queue
	queue_enqueue(qThread, (void *) newThread);

	return 0;
}

int uthread_run(bool preempt, uthread_func_t func, void *arg)
{
	/* TODO Phase 2 */

	// Create an main/idle thread
	struct uthread_tcb *idleThread = (struct uthread_tcb *) malloc(sizeof(struct uthread_tcb));

	if (idleThread == NULL) {
		perror("uthread_run()");
		printf("could NOT allocate memory for idleThread\n");
		return -1;
	}

	idleThread->state = RUNNING;
	
	// Start preemption
	preempt_start(preempt);

	// The main/idle thread is the current running thread
	currentThread = idleThread;

	// Initialize and allocate memory to global queue
	qThread = queue_create();

	// Create first thread
	uthread_create(func, arg);

	while (queue_length(qThread) != 0) {
		uthread_yield();
	}

	return 0;
}

void uthread_block(void)
{
	/* TODO Phase 4 */
}

void uthread_unblock(struct uthread_tcb *uthread)
{
	/* TODO Phase 4 */
}