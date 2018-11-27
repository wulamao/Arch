#ifndef EVENT_MANAGER_H_
#define EVENT_MANAGER_H_

 
int em_push_event(void *event);
int em_register(void *event, void *cbf); 
int em_iterator(void);
#endif
