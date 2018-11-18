
#include "event.h"
#include "queue.h"

/* create cb container */
void* cbq_init(void)
{
    return queue_new();
}

/* delete cb container */
void cbq_del(void* c)
{
    queue_free((Queue *)c);
}
/* cb register*/
void* cbq_push(void* c, void *ev)
{
    queue_push_head((Queue *)c, ev);
}

/* cb remove*/
void* cbq_pop(void* c)
{
    return queue_pop_tail((Queue *)c);
}
/* cb lookup*/
void* cbq_lookup(void* c, unsigned int method)
{
    return 0;
}
/* cb traversal*/
void* cbq_iterator(void* c)
{
    return 0;
}
/* cb sort*/
void* cbq_sort(void* c)
{
    return 0;
}
/* cb queue is empty*/
int cbq_is_empty(void* c)
{
    return queue_is_empty((Queue *)c);
}
