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
## PHASE 2: uthread API (Joel and Ali)
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
####    In uthread_yield() we obtain the current running thread by calling 
####    uthread_current(), change its state to READY, and push it to the ready queue.
####    Next, we obtain the 'oldest thread' in the ready queue, change its state to
####    RUNNING, and set the global current thread object to this old thread. Lastly,
####    we do a context switch between the past current thread that is now yielding 
####    and the oldest thread that is now running so that the oldest can start executing.
###   2.5: uthread_exit()
####    In this last function we obtain the current running thread, change its state to 
####    EXIT, and deallocate the memory for the threads context and stack. This essentially 
####    terminates the thread so it won't be executed again. Next, we getthe oldest thread 
####    in the ready queue, change its state to RUNNING, and change the global current 
####    thread object to the oldest thread. Finally, we do a context between the exited 
####    thread and the oldest thread so that it can start running.
###   2.6: uthread_block
####    for this function, I just changed the state of the currently running thread to
####    "BLOCK" and yielded the execution.
###   2.7: uthread_unblock
####    for this function, I changed the state of the passed thread to "READY" and then 
####    placed it to the universal queue to run later.
#### ----------------------------------------------------------------------------
## PHASE 3: semaphore API (Ali)
### 
#### ----------------------------------------------------------------------------
## PHASE 4: preemption (Joel and Ali)
####    Before implementing the functions for PHASE 4 we declared macors to make our code
####    readable. We use Hz, SECS, and USECS to represent frequency and time that will be
####    used for configuring the interval timer of our virtual alarm. Additionally, we
####    we included a global sigaction object that can be used to check whether our signal
####    has a handler attatched to it.
###   4.0: signal_handler() 
####    This function will be executed everytime an alarm signal is sent. It displays,
####    the type of signal it is as an integer and yields the current running thread.
###   4.1: preempt_start()
####    If the start of uthread_run() uses preemption then we have to set up a virtual
####    alarm that sends 100 signal interrupts per second (100 Hz). To do this we provide
####    a handler for our sigaction object which is our signal_handler function and 
####    specify that we want a virtual singal for this object by calling sigaction().
####    Lastly, we enable the virtual alarm to send its first signal after 10000 
####    microseconds and more interrpt signals after every 10000 microseconds by
####    specifying it_value and it_interval to USECS and call setitimer() to register 
####    this configuration.
####
####    In the case that we dont use preepmtion then we don't initialized the sigaction
####    object at all so that its handler data is NULL.
###   4.2: preempt_stop()
####    
###   4.3: preempt_enable()
####    To enable preemption that has a signal handler we enable the alarm by setting it_value to USECS and 
####    enable consecutive interrupts by setting it_interval to USECS.
####    to USECS and call setitimer().
###   4.4: preempt_disable()
####    To disable preemption we disable the alarm by setting it_value to 0 and call setitimer().
###   4.5: other functions such as uthread_block/unblock()
####    
#### ----------------------------------------------------------------------------
## SOURCES:
### (1) 
###
### (2) 
###
### (3) 
