#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "private.h"
#include "uthread.h"

/*
 * Frequency of preemption
 * 100Hz is 100 times per second
 */
#define HZ 100
#define SECS 1/HZ
#define MSECS 1000*SECS
#define USECS 1000000*SECS

void signal_handler(int signum)
{
	printf("singla_handler(%d)\n", signum);
	uthread_yield();
}

void preempt_disable(void)
{
	/* TODO Phase 4 */

	// Disable alarm timer for 100 HZ
	struct  itimerval timerValue;
	struct  timeval enableInt = {0, 0};
	struct  timeval timerInterval = {0, 0};

	timerValue.it_value = enableInt;
	timerValue.it_interval = timerInterval;

	if (setitimer(ITIMER_VIRTUAL, &timerValue, NULL) == -1) {
		perror("preempt_disable()");
		printf("Could not set the interval timer!\n");
		exit(-1);
	}
}

void preempt_enable(void)
{
	/* TODO Phase 4 */

	// Set up the timer value for 100 HZ
	struct  itimerval timerValue;

	// Enable alarm for consecutive interrupts after the 1st one
	struct  timeval enableInt = {0, USECS};

	// set up alarm timer interval
	struct  timeval timerInterval = {0, USECS};

	timerValue.it_value = enableInt;
	timerValue.it_interval = timerInterval;
	
	if (setitimer(ITIMER_VIRTUAL, &timerValue, NULL) == -1) {
		perror("preempt_enable()");
		printf("Could not set the interval timer!\n");
		exit(-1);
	}
}

void preempt_start(bool preempt)
{
	/* TODO Phase 4 */

	if (preempt == true) {
		struct sigaction sa;

		// Set up singal handler
		sa.sa_handler = signal_handler;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		sigaction(SIGVTALRM, &sa, NULL);
		preempt_enable();
	}
	else {
		preempt_disable();
	}

}

void preempt_stop(void)
{
	/* TODO Phase 4 */
}

