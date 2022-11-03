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

struct  itimerval curr_timerValue;
struct  itimerval old_timerValue;

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
		int itimerStatus;

		// Disable alarm interrupts
		curr_timerValue.it_value.tv_sec = 0;
		curr_timerValue.it_value.tv_usec = 0;
		
		// Disable alarm timer interval
		//curr_timerValue.it_interval.tv_sec = 0;
		//curr_timerValue.it_interval.tv_usec = 0;

		itimerStatus = setitimer(ITIMER_VIRTUAL, &curr_timerValue, NULL);

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
		int itimerStatus;

		// Set up alarm timer interval
		curr_timerValue.it_value.tv_sec = 0;
		curr_timerValue.it_value.tv_usec = USECS;

		// Enable alarm for consecutive interrupts after the 1st one
		curr_timerValue.it_interval.tv_sec = 0;
		curr_timerValue.it_interval.tv_usec = USECS;

		itimerStatus = setitimer(ITIMER_VIRTUAL, &curr_timerValue, NULL);

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

		int saStatus, itimerStatus;

		// Set up singal handler
		curr_sa.sa_handler = signal_handler;
		sigemptyset(&curr_sa.sa_mask);
		curr_sa.sa_flags = 0;

		saStatus = sigaction(SIGVTALRM, &curr_sa, &old_sa);

		if (saStatus == -1) {
			perror("preempt_start()");
			printf("Could not complete sigaction!\n");
			exit(-1);
		}

		// Set up alarm timer interval
		curr_timerValue.it_value.tv_sec = 0;
		curr_timerValue.it_value.tv_usec = USECS;

		// Enable alarm for consecutive interrupts after the 1st one
		curr_timerValue.it_interval.tv_sec = 0;
		curr_timerValue.it_interval.tv_usec = USECS;

		itimerStatus = setitimer(ITIMER_VIRTUAL, &curr_timerValue, &old_timerValue);

		if (itimerStatus == -1) {
			perror("preempt_start()");
			printf("Could not set the interval timer!\n");
			exit(-1);
		}
	}
}

void preempt_stop(void)
{
	/* TODO Phase 4 */
	int saStatus, itimerStatus;

	curr_sa = old_sa;
	saStatus = sigaction(SIGVTALRM, &curr_sa, NULL);
	if (saStatus == -1) {
		perror("preempt_stop()");
		printf("Could not complete sigaction!\n");
		exit(-1);
	}

	curr_timerValue = old_timerValue;
	itimerStatus = setitimer(ITIMER_VIRTUAL, &curr_timerValue, NULL);
	if (itimerStatus == -1) {
		perror("preempt_stop()");
		printf("Could not set the interval timer!\n");
		exit(-1);
	}
}

