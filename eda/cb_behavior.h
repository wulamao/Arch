#ifndef CB_BEHAVIOR_H_
#define CB_BEHAVIOR_H_

/* create cb container */
extern void* cbq_init(void);
/* delete cb container */
extern void cbq_del(void *c);
/* cb register*/
extern void* cbq_push(void *c, Event_pair_t *ev);
/* cb remove*/
extern void* cbq_pop(void *c);
/* cb lookup*/
extern void* cbq_lookup(void *c, unsigned int method);
/* cb traversal*/
extern void* cbq_iterator(void *c);
/* cb sort*/
extern void* cbq_sort(void *c);
/* cb queue is empty*/
int cbq_is_empty(void* c);

#endif
