#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


#include "queue.h"

#define TEST_ASSERT(assert)				\
do {									\
	printf("ASSERT: " #assert " ... ");	\
	if (assert) {						\
		printf("PASS\n");				\
	} else	{							\
		printf("FAIL\n");				\
		exit(1);						\
	}									\
} while(0)

/* Create */
void test_create(void)
{
    TEST_ASSERT(queue_create() != NULL);
}

void test_queue_enqueue(void) {
    int array[10] = {1,2,-88,34,17,0,324,32,6,8};
    int *ptr;
    queue_t q;
    q = queue_create();

    for(int i =0; i < 10; i++) {
        int enqueue = queue_enqueue(q, &array[i]);
        TEST_ASSERT(enqueue == 0);
    }

    TEST_ASSERT(queue_length(q) == 10);

    for(int i =0; i < 10; i++) {
        if(queue_dequeue(q, (void**)&ptr) == 0) {
            TEST_ASSERT(ptr == &array[i]);
        }
    }

}

void delete_test(void ) {
    int array[10] = {1,2,-88,34,17,0,324,32,6,8};
    int notFound = 9999;
    queue_t q;
    q = queue_create();
    for(int i =0; i < 10; i++) {
        queue_enqueue(q, &array[i]);
    }

    for(int i = 0; i < 5; i++) {
        int delete = queue_delete(q, &array[i]);
        TEST_ASSERT(delete == 0);
    }

    for(int i = 0; i < 5; i++) {
        int delete = queue_delete(q, &notFound);
        TEST_ASSERT(delete == -1);
    }
}

//void test_destroy() {
//    int array[10] = {1,2,-88,34,17,0,324,32,6,8};
//    queue_t q;
//    q = queue_create();
//    for(int i =0; i < 10; i++) {
//        queue_enqueue(q, &array[i]);
//    }
//
//    int destroyed = queue_destroy(q);
//    TEST_ASSERT(destroyed == 0);
//}

static void iterator_inc(queue_t q, void *data)
{
    int *a = (int*)data;

    if (*a == 42)
        queue_delete(q, data);
    else {
        *a += 1;
        //printf("%d ", *a);
    }
}


void test_iterator(void)
{
    queue_t q;
    int data[] = {1, 2, 3, 4, 5, 42, 6, 7, 8, 9};
    size_t i;

    /* Initialize the queue and enqueue items */
    q = queue_create();
    for (i = 0; i < sizeof(data) / sizeof(data[0]); i++)
        queue_enqueue(q, &data[i]);

    /* Increment every item of the queue, delete item '42' */
    queue_iterate(q, iterator_inc);

    printf("\ntesting iterator: \n");
    TEST_ASSERT(data[0] == 2);
    TEST_ASSERT(queue_length(q) == 9);
    printf("iterator test done!\n\n");
}

int main(void)
{
    test_create();
    test_iterator();
    test_queue_enqueue();
    delete_test();
    //test_destroy();

    return 0;
}
