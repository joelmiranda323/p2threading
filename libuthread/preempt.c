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

struct sigaction curr_sa;
struct sigaction old_sa;

void signal_handler(int signum)
{
	printf("signal_handler(%d)\n", signum);
    uthread_yield();
}

void preempt_disable(void)
{
	/* TODO Phase 4 */
	if (curr_sa.sa_handler != NULL) {

		// Disable alarm timer for 100 HZ
		struct  itimerval timerValue;
		int itimerStatus;

		// Disable alarm timer interval
		timerValue.it_value.tv_sec = 0;
		timerValue.it_value.tv_usec = 0;
		
		// Disable alarm interrupts
		timerValue.it_interval.tv_sec = 0;
		timerValue.it_interval.tv_usec = 0;

		itimerStatus = setitimer(ITIMER_VIRTUAL, &timerValue, NULL);
		if (itimerStatus == -1) {
			perror("preempt_disable()");
			printf("Could not set the interval timer!\n");
			exit(-1);
		}
	}
}

void preempt_enable(void)
{
	/* TODO Phase 4 */
	if (curr_sa.sa_handler != NULL) {

		// Set up the timer value for 100 HZ
		struct  itimerval timerValue;
		int itimerStatus;

		// Set up alarm timer interval
		timerValue.it_value.tv_sec = 0;
		timerValue.it_value.tv_usec = USECS;

		// Enable alarm for consecutive interrupts after the 1st one
		timerValue.it_interval.tv_sec = 0;
		timerValue.it_interval.tv_usec = USECS;

		itimerStatus = setitimer(ITIMER_VIRTUAL, &timerValue, NULL);

		if (itimerStatus == -1) {
			perror("preempt_enable()");
			printf("Could not set the interval timer!\n");
			exit(-1);
		}
	}
}

void preempt_start(bool preempt)
{
	/* TODO Phase 4 */
	if (preempt == true) {

		int saStatus;

		// Set up singal handler
		curr_sa.sa_handler = signal_handler;
		sigemptyset(&curr_sa.sa_mask);
		curr_sa.sa_flags = 0;

		saStatus = sigaction(SIGVTALRM, &curr_sa, NULL);

		if (saStatus == -1) {
			perror("preempt_start()");
			printf("Could not complete sigaction!\n");
			exit(-1);
		}
		preempt_enable();
	}
}

void preempt_stop(void)
{
	/* TODO Phase 4 */
	int itimerStatus, saStatus;
	struct  itimerval old_timerValue;

	saStatus = sigaction(SIGVTALRM, NULL, &old_sa);

	if (saStatus == -1) {
		perror("preempt_stop()");
		printf("Could not complete sigaction!\n");
		exit(-1);
	}

	itimerStatus = setitimer(ITIMER_VIRTUAL, NULL, &old_timerValue);

	if (itimerStatus == -1) {
		perror("preempt_enable()");
		printf("Could not set the interval timer!\n");
		exit(-1);
	}
}

