#ifndef EM_BEHAVIOR_H_
#define EM_BEHAVIOR_H_


void* eq_init(void);
void eq_del(void* c);
void* eq_push(void* c, void *ev);
void* eq_pop(void* c);
void* eq_iterator(void* c);
int eq_is_empty(void* c);


#endif
