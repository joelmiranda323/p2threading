# Project 2 Report by Joel Miranda and Ali Osmani
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
###   INTRO
####   It was straightforward, but since it was my first time implementing a Queue
####   API, I needed to read an online tutorial to have an general idea of what a
####   queue structure looks like and how I can implement it. I decided to use a 
####   linked list data structure for our queue implementation. I didn't choose an
####   array since it always needed a fixed size. for our linked list, I wrote a node 
####   struct with a pointer that points to the data, and a node pointer that points
####   to the next node. Ihen, in my queue struct, I had a front and a rear nodes, and 
####   an int to keep track of the size of the queue.
###   1.1-1.2: queue_create and queue_destroy   
####   for queue_create, we allocated memory, make the front and rear node point to 
####   null, and assign size to zero. for destroing the queue, first check if the
####   queue is not null or if it is empty, then destroy it.
###   1.3: queue_enqueue
####   for enqueueing, there was two cases to consider. case 1: if the the queue is 
####   empty. case 2: if it is not empty. we check it by checking the size of the
####   queue. if it is empty, we make the front and rear node of the queue point to 
####   the new data and increase the size by one. if the queue is not empty, we add it 
####   to back of the queue and make the rear node pointer points to it. 
###   1.4: queue_dequeue
####   Dequeuing was fairly simple since I only had to remove the item from the front 
####   of the queue. first, I saved the front node by making a node pointer that 
####   points to it. then, I made the front node pointer points to the next node.
####   then, since I made the the front points to the next node, I had to check if the
####   next is not NULL. if it is, make the rear points to NULL.
###   1.5: queue_delete 
####   Implementing this function was a little bit hard since I was deleting a
####   specific node. for this, I watched a video that explained a way to delete a 
####   specific node from a linked list. the idea was to make two nodes, one points to 
####   the current node and the other points to the previos node. I used a for loop 
####   that iterated through the queue items, and in the for loop I checked if the
####   current is the node I am looking for. if yes, I made the previous node points 
####   to next node that the current node points to, and then delete the current node. 
####   If the current is not the node I am looking for, I increment the previous and 
####   current node by 1 and so on till I find it. 
###   1.6: queue_iterate
####   This function was the hardest since I had to make it delete operation proof. I
####   made a temp pointer for iteration and ran the function on each data. if any 
####   data was deleted, I just made it broke out of the loop. 
###   1.7: queueu_length 
####   It was simple to implement. If the queue is not null, I returned the size of 
####   the queue.
###   1.8: Testing
####   For testing, I used unit testing method. For each function in queue.c, I made a
####   funtion to test it. All functions successfully passed the test cases.    
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
### INTRO
####    Professor's lecture about Semaphores and how they manage resources was super
####    clear, but I still needed a review of it before I was ready to implement it. 
####    According to the video, a semaphores will have counter for the resource and it has 
####    a queue to put the blocked threads in it when the resource is not available. so 
####    for sem struct, I added a queue and a counter.
###    3.1-3.2: sem_create and sem_destroy
####    For sem create, I allocated memory. Then, checked if the memory allocation was
####    successful and the sem is not null. if it is succesfull, assign the counter to 
####    the passed count, creat the queue and return the semaphores. For destroy, I 
####    only destroyed it when there was not threads in the queue and the sem is not 
####    null. 
###    3.3 sem_down 
####    For this part, the project explanation and the corner case helped me a lot. The 
####    basic idea is to first check if the resource is available by checking the 
####    counter. If the couter is zero, then the resource is not available. Therefore, 
####    the thread that requested this resource should be blocked and should be put in 
####    the queue till the resource become available again. If the counter is not zero, 
####    it means the resource is available. In that case, we just decrement the counter 
####    meaning it is assign to requested thread and it is no longer available. In both 
####    case we return zero. 
###    3.4 sem_up
####    This function was a little bit more complicated but with a little bit more 
####    time, trying different scenarios, and using the testers, I was able to make it 
####    work. The idea is to first check if there is any thread in the queue and 
####    waiting for resources. If yes, first, I made thread struct pointer that will 
####    point to the dequeued thread, and then, I ublocked it. Otherwise, if there is no 
####    threads waiting for the resource, we just increment the counter meaning the 
####    resource is available.
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
####    To stop preemption we take the old sigaction object and old itimerval object 
####    from before we called preempt_start() and set them as the current sigaction and 
####    itimerval objects. We essentially set the signal action and interval timer 
####    values to what we had before we started configuring the interrupts to produce 
####    100 signal interrupts per second.  
###   4.3: preempt_enable()
####    To enable preemption that has a signal handler we enable the alarm by setting it_value to USECS and 
####    enable consecutive interrupts by setting it_interval to USECS.
####    to USECS and call setitimer().
###   4.4: preempt_disable()
####    To disable preemption we disable the alarm by setting it_value to 0 and call setitimer().
####    
#### ----------------------------------------------------------------------------
## SOURCES:
### (1) https://www.geeksforgeeks.org/queue-linked-list-implementation/?ref=lbp
###
### (2) https://www.youtube.com/watch?v=f1r_jxCyOl0
###
### (3) https://www.youtube.com/watch?v=jF-1eFhyz1U
###
### (4) https://www.youtube.com/watch?v=XDIOC2EY5JE&t=827s
### 
### (5) https://slideplayer.com/slide/14907779/
