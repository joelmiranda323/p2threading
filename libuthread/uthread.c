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

queue_t queueT;
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

	// Get currrent running thread
	struct uthread_tcb *currThread = uthread_current();

	// yield: from RUNNING to READY
	if (currThread->state == RUNNING) {
		// Currrent running thread is now yielding
		currThread->state = READY;

		// Add yeilding thread to the queue
		queue_enqueue(queueT, currThread);
	}
	else {
		perror("uthread_yield() currThread");
		// print the state of the current thread
		printf("state of current thread: %d", currThread->state);
	}

	// Get the oldest thread from the queue
	struct uthread_tcb *oldThread;
	queue_dequeue(queueT, &oldThread);

	// Elect oldest thread to run: READY to RUNNING
	if (oldThread->state == READY) {
		// Oldest thread is now the current running thread
		oldThread->state = RUNNING;
		currentThread = oldThread;
	}
	else {
		perror("uthread_yield() oldThread");
		// print the state of the oldest thread
		printf("state of oldest thread: %d", oldThread->state);
	}

	// Save yielding threads context and activate current threads context
	uthread_ctx_switch(currThread->context, oldThread->context);
}

void uthread_exit(void)
{
	/* TODO Phase 2 */

}

int uthread_create(uthread_func_t func, void *arg)
{
	/* TODO Phase 2 */
	int ctxInitStatus;
	struct uthread_tcb *uthread = (struct uthread_tcb *) malloc(sizeof(struct uthread_tcb));
	
	uthread->state = READY;
	uthread->context = (struct uthread_ctx_t *) malloc(sizeof(uthread_ctx_t));
	uthread->stack = uthread_ctx_alloc_stack();

	ctxInitStatus = uthread_ctx_init(uthread->context, uthread->stack, func, arg);

	if(ctxInitStatus == -1) {
		perror("uthread_ctx_init() in uthread_create()");
		return -1;
	}

	queue_enqueue(queueT, uthread);

	return 0;
}

int uthread_run(bool preempt, uthread_func_t func, void *arg)
{
	/* TODO Phase 2 */
}

void uthread_block(void)
{
	/* TODO Phase 4 */
}

void uthread_unblock(struct uthread_tcb *uthread)
{
	/* TODO Phase 4 */
}