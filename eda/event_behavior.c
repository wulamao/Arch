
#include "event.h"
#include "queue.h"

/* create event container */
void* eq_init(void)
{
    return queue_new();
}

/* delete event container */
void eq_del(void* c)
{
    queue_free((Queue *)c);
}
/* cb register*/
void* eq_push(void* c, void *ev)
{
    queue_push_head((Queue *)c, ev);
}

/* cb remove*/
void* eq_pop(void* c)
{
    return queue_pop_tail((Queue *)c);
}
/* event lookup*/
void* eq_lookup(void* c, unsigned int method)
{
    return 0;
}
/* event traversal*/
void* eq_iterator(void* c)
{
    return 0;
}
/* event queue is empty*/
int eq_is_empty(void* c)
{
    return queue_is_empty((Queue *)c);
}
