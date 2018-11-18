#ifndef EVENT_MANAGER_H_
#define EVENT_MANAGER_H_

//typedef void* (*em_init)(void);
//typedef void (*em_del)(void *c);
//typedef void* (*em_push)(void *c, void *cb);
//typedef void* (*em_pop)(void *c);
//typedef void* (*em_iterator)(void *c);
//typedef int (*em_is_empty)(void *c);

typedef struct _Event_manager_t Event_manager_t;

Event_manager_t *new_em(void *init,
                        void *del,
                        void *push,
                        void *pop,
                        void *iterator,
                        void *is_empty
                        );
void delete_em(void *em);
void *em_init(void);
void em_push(void *em, void *event);
void *em_pop(void *em);
void em_iterator(void *em); 
#endif
