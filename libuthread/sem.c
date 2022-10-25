#include <stddef.h>
#include <stdlib.h>

#include "queue.h"
#include "sem.h"
#include "private.h"

struct semaphore {
	/* TODO Phase 3 */
    size_t counter;
    queue_t queue;
};

sem_t sem_create(size_t count)
{
	/* TODO Phase 3 */
    struct semaphore *sem = malloc(sizeof(struct semaphore));
    sem->counter = count;
    sem->queue = queue_create();

    return sem;
}

int sem_destroy(sem_t sem)
{
	/* TODO Phase 3 */
}

int sem_down(sem_t sem)
{
	/* TODO Phase 3 */
}

int sem_up(sem_t sem)
{
	/* TODO Phase 3 */
}

