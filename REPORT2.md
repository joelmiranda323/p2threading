REPORT:
Intro: Project was started the weekend that the it was published. we splitted
the work 50/50 and started working on it right away. 

Phase 1: Qeueu Implementation

it was straightforward, but since it was my first time implementing a Queue 
API, I needed to read an online tutorial to have an general idea of what a 
queue structure looks like and how I can implement it. I decided to use a linked 
list data structure for our queue implementation. I didn't choose an array since it always needed a fixed size. for our linked list, I wrote a node struct with a pointer that points to the data, and a node pointer that points to the next node. Ihen, in my queue struct, I had a front and a rear nodes, and an int to keep track of the size of the queue. 

1.1-1.2: queue_create and queue_destroy
for queue_create, we allocated memory, make the front and rear node point to null, and assign size to zero. for destroing the queue, first check if the queue is not null or if it is empty, then destroy it. 

1.3: queue_enqueue
for enqueueing, there was two cases to consider. case 1: if the the queue is empty. 
case 2: if it is not empty. we check it by checking the size of the queue. if it is empty, we make the front and rear node of the queue point to the new data and increase the size by one. if the queue is not empty, we add it to back of the queue and make the rear node pointer points to it. 

1.4: queue_dequeue
Dequeuing was fairly simple since I only had to remove the item from the front of the queue. first, I saved the front node by making a node pointer that points to it. then, I made the front node pointer points to the next node. then, since I made the the front points to the next node, I had to check if the next is not NULL. if it is, make the rear points to NULL. 

1.5: queue_delete
Implementing this function was a little bit hard since I was deleting a specific node. for this, I watched a video that explained a way to delete a specific node from a linked list. the idea was to make two nodes, one points to the current node and the other points to the previos node. I used a for loop that iterated through the queue items, and in the for loop I checked if the current is the node I am looking for. if yes, I made the previous node points to next node that the current node points to, and then delete the current node. If the current is not the node I am looking for, I increment the previous and current node by 1 and so on till I find it. 


1.6: queue_iterate
This function was the hardest since I had to make it delete operation proof. I made a temp pointer for iteration and ran the function on each data. if any data was deleted, I just made it broke out of the loop. 

1.7: queueu_length 
It was simple to implement. If the queue is not null, I returned the size of the queue;

1.8: Testing
For testing, I used unit testing method. For each function in queue.c, I made a funtion to test it. All functions successfully passed the test cases. 


Phase 3: Semaphores API

intro: Professor's lecture about Semaphores and how they manage resources was super clear, but I still needed a review of it before I was ready to implement it. According the video, a semaphores will have counter for the resource and it has s queue to put the blocked threads in it when the resource is not available. so for sem struct, I added a queue and a counter. The video is cited. 

3.1-3.2: sem_create and sem_destroy
for sem create, I allocated memory. then, checked if the memory allocation was successful and the sem is not null. if it is succesfull, assign the counter to the passed count, creat the queue and return the semaphores. for destroy, I only destroyed it when there was not threads in the queue and the sem is not null. 

3.3 sem_down 
for this part, the project explanation and the corner case helped a lot. the basic idea is to first check if the resource is available by checking the counter. If the couter is zero, then the resource is not available. therefore, the thread that requested this resource should be blocked and should be put in the queue till the resource become available again. if the counter is not zero, it means the resource is available. in that case, we just decrement the counter meaning it is assign to requested thread and it is no longer available. in both case we return zero. 

3.4 sem_up
this function was a little bit more complicated but with a little bit more time, trying different scenarios, and using the testers, I was able to make it work. The idea is to first check if the there is any thread in the queue and waiting for resources. if yes, first, I made thread struct pointer that will point to the dequeued thread and then, I ublocked it. otherwise, if there is no threads waiting for the resource, we just increment the counter meaning the resource is available. 







