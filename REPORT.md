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
####    state to RUNNING because its the main thread currently running. Upon successfully 
####    allocating space we initialize the global current thread object with the idle 
####    thread since its running. Then we initialize the global ready queue with 
####    queue_create() from PHASE 1 and create a new thread using uthread_create(). 
####    Lastly, we yield the current thread (by calling uthread_yield()) unit the ready 
####    queue is empty.
###   2.3: uthread_create()
####    For uthread_create we create a new thread by allocating space (similar to the 
####    idle thread in uthread_run()) and initializing its state to READY and its 
####    context by using uthread_ctx_init(). Once we successfully allocate space and
####    finish initializing the thread we push it to the ready queue.
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
