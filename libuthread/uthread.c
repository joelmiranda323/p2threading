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
#define ZOMBIE	3

// Race condtions
// We need to use a lock (preempt disable/enable functions) for these
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

	preempt_disable();
	// Get currrent running thread
	struct uthread_tcb *currThread = uthread_current();

	// yield: from RUNNING to READY
	if (currThread->state == RUNNING) {
		// Currrent running thread is now yielding
		currThread->state = READY;

		// Add yeilding thread to the queue
		queue_enqueue(qThread, (void *) currThread);
	}
	else {
		// print the state of the current thread
		printf("In uthread_yield(): currThread\n");
		printf("State of current thread: %d\n", currThread->state);
	}

	// Get the oldest thread from the queue
	struct uthread_tcb *oldThread;
	queue_dequeue(qThread, (void **) &oldThread);

	// Elect oldest thread to run: READY to RUNNING
	if (oldThread->state == READY) {
		// Oldest thread is now the current running thread
		oldThread->state = RUNNING;
		currentThread = oldThread;
	}
	else {
		// print the state of the oldest thread
		printf("In uthread_yield(): oldThread\n");
		printf("State of oldest thread: %d\n", oldThread->state);
	}

	// Save yielding threads context and activate current threads context
	uthread_ctx_switch(currThread->context, oldThread->context);
	preempt_enable();
}

void uthread_exit(void)
{
	/* TODO Phase 2 */
	preempt_disable();
	// Get currrent running thread
	struct uthread_tcb *currThread = uthread_current();

	// Exit current running thread
	currThread->state = ZOMBIE;
	free(currThread->context);
	free(currThread->stack);

	// Get the oldest thread from the queue
	struct uthread_tcb *oldThread;
	queue_dequeue(qThread, (void **) &oldThread);

	// Elect oldest thread to run: READY to RUNNING
	if (oldThread->state == READY) {
		// Oldest thread is now the current running thread
		oldThread->state = RUNNING;
		currentThread = oldThread;
	}
	else {
		// print the state of the oldest thread
		printf("In uthread_exit(): oldThread\n");
		printf("State of oldest thread: %d\n", oldThread->state);
	}

	// Save yielding threads context and activate current threads context
	uthread_ctx_switch(currThread->context, oldThread->context);
	preempt_enable();
}

int uthread_create(uthread_func_t func, void *arg)
{
	/* TODO Phase 2 */
	int ctxInitStatus;
	struct uthread_tcb *newThread = (struct uthread_tcb *) malloc(sizeof(struct uthread_tcb));
	
	newThread->state = READY;
	newThread->context = (struct uthread_ctx_t *) malloc(sizeof(uthread_ctx_t));
	newThread->stack = uthread_ctx_alloc_stack();

	ctxInitStatus = uthread_ctx_init(newThread->context, newThread->stack, func, arg);

	if(ctxInitStatus == -1) {
		perror("ctxInitStatus == -1 in uthread_create()");
		return -1;
	}

	preempt_disable();
	queue_enqueue(qThread, (void *) newThread);
	preempt_enable();

	return 0;
}

int uthread_run(bool preempt, uthread_func_t func, void *arg)
{
	/* TODO Phase 2 */

	// Start preemption
	preempt_start(preempt);

	// Initialize and allocate memory to global queue
	preempt_disable();
	qThread = queue_create();
	preempt_enable();

	// Create first thread
	uthread_create(func, arg);
}

void uthread_block(void)
{
	/* TODO Phase 4 */
}

void uthread_unblock(struct uthread_tcb *uthread)
{
	/* TODO Phase 4 */
}
