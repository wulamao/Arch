#ifndef EVENT_BEHAVIOR_H_
#define EVENT_BEHAVIOR_H_

/* create event container */
extern void* eq_init(void);
/* delete event container */
extern void eq_del(void *c);
/* cb register*/
extern void* eq_push(void *c, Event_pair_t *ev);
/* cb remove*/
extern void* eq_pop(void *c);
/* event lookup*/
extern void* eq_lookup(void *c, unsigned int method);
/* event traversal*/
extern void* eq_iterator(void *c);
/* event queue is empty*/
int eq_is_empty(void* c);

#endif
