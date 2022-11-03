# Project 2 Report by Joel Miranda and Ali
#### ----------------------------------------------------------------------------
## Makefile (Joel)
####   The contents in our Makefile include variables, an 'all' target, and a
####   'clean' target. The variables state the compiler and the compiler flags we
####   use, the c and object files which are required for the API, and the end 
####   targets for the libray and executable name. The 'all' target builds 2 
####   things, the static library named 'libuthread' and the executable. The 
####   executable is created by compiling the c and object files and the static 
####   library is created by using the objects. The 'clean' target removes the 
####   executable, the static library, and all object files.
#### ----------------------------------------------------------------------------
## PHASE 1: queue API (Ali)
####     
#### ----------------------------------------------------------------------------
## PHASE 2: uthread API (Joel)
####    There were a total of 5 functions, uthread_current(), uthread_run(), 
####    uthread_create(), uthread_yield(), and uthread_exit(), implemented in 
####    this phase. But before implementing these functions we needed to declare 
####    2 race conditions, a ready queue to keep track of threads that aren't 
####    running and a tcb object that holds the current running threads tcb data. 
####    Additionally we needed to implement a tcb data structer to organize each 
####    threads data. 
###   2.0: struct uthread_tcb
####    Each thread has a tcb which includes the threads state, its context, and 
####    its stack. So in the uthread_tcb data structure we organized its tcb data
####    by using an int data type for the state which will take integer macros of 
####    the state name, a uthread_ctx_t object for the tcb context, and a void pointer
####    stack since the stacks data type is undetermined.
###   2.1: uthread_current()
####    Implementing this function was simple. All we had to do was return the
####    global tcb object which is the current thread. 
###   2.2: uthread_run()
####    In this functions we first create an idle thread by allocating space for
####    itself (the tcb object), its context, and its stack. We also initialize its 
####    state to running because its the main thread currently running. Since the 
####    idle thread is RUNNING we initialize the global current thread object with 
####    the idle thread. Then we initialize the global ready queue with the queue_create() 
####    function in PHASE 1 and create a new thread using the uthread_create() function.
####    Lastly, we yield the current thread (by calling uthread_yield()) until there 
####    are no more threads in the global ready queue.
###   2.3: uthread_create()
####    
###   2.4: uthread_yield()
####    
###   2.5: uthread_exit()
####   
#### ----------------------------------------------------------------------------
## PHASE 3: semaphore API (Ali)
### 
#### ----------------------------------------------------------------------------
## PHASE 4: preemption (Joel and Ali)
### 
#### ----------------------------------------------------------------------------
## SOURCES:
### (1) 
###
### (2) 
###
### (3) 
