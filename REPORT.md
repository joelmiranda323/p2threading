# Project 2 Report by Joel Miranda and Ali
##### ----------------------------------------------------------------------------
## Makefile (Joel)
####   The contents in our Makefile include variables, an 'all' target, and a
####   'clean' target. The variables state the compiler and the compiler flags we
####   use, the c and object files which are required for the API, and the end 
####   targets for the libray and executable name. The 'all' target builds 2 
####   things, the static library named 'libuthread' and the executable. The 
####   executable is created by compiling the c and object files and the static 
####   library is created by using the objects. The 'clean' target removes the 
####   executable, the static library, and all object files.
##### ----------------------------------------------------------------------------
## PHASE 1: queue API (Ali)
####     
##### ----------------------------------------------------------------------------
## PHASE 2: uthread API (Joel)
####    There were a total of 5 functions, uthread_current(), uthread_run(), 
####    uthread_create(), uthread_yield(), and uthread_exit(), implemented in 
####    this phase. But before implementing these functions we needed to declare 
####    2 race conditions, a ready queue to keep track of threads that aren't 
####    running and a tcb object that holds the current running threads tcb data. 
####    Additionally we needed to implement a tcb data structer to organize each 
####    threads data. 
###   struct uthread_tcb
####    Each thread has a tcb which includes the threads state, its context, and 
####    its stack. So in the uthread_tcb data structure we organized its tcb data
####    by using an int data type for the state which will take integer macros of 
####    the state name, uthread_ctx_t structure for the tcb context, and void pointer
####    stack since the stack data type is undetermined.
###   uthread_current()
####  
###   uthread_run()
####    
###   uthread_create()
####    
###   uthread_yield()
####    
###   uthread_exit()
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
