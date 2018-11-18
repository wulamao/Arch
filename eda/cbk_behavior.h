#ifndef CBK_BEHAVIOR_H_
#define CBK_BEHAVIOR_H_


void* cbq_init(void);
void cbq_del(void* c);
void* cbq_push(void* c, void *ev);
void* cbq_pop(void* c);
void* cbq_lookup(void* c, unsigned int method);
void* cbq_iterator(void* c);
void* cbq_sort(void* c);
int cbq_is_empty(void* c);


#endif

