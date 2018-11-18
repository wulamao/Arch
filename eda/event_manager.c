#include "event_manager.h"
#include "em_behavior.h"
#include "event.h"

/**
 * define event manager structure.
 */
typedef struct _Event_manager_t
{
    void* container; // 事件容器指针

    /* create event container */
    void* (*init)(void);
    /* delete event container */
    void (*del)(void* c);
    /* cb register*/
    void* (*push)(void* c, void *cb);
    /* cb remove*/
    void* (*pop)(void* c);
    /* event traversal*/
    void* (*iterator)(void* c);
    /* event container is empty */
    int (*is_empty)(void* c);
} Event_manager_t;


Event_manager_t *new_em(void *init,
                        void *del,
                        void *push,
                        void *pop,
                        void *iterator,
                        void *is_empty
                        )
{
    Event_manager_t *em = (Event_manager_t*)malloc(sizeof(Event_manager_t));
    em->init     = init;
    em->del      = del;
    em->push     = push;
    em->pop      = pop;
    em->iterator = iterator;
    em->is_empty = is_empty;

    em->container = em->init();
    return em;
}

void delete_em(void *em)
{
    free(em);
}

void* em_init(void)
{
    Event_manager_t * em = new_em(eq_init,
                                  eq_del,
                                  eq_push,
                                  eq_pop,
                                  eq_iterator,
                                  eq_is_empty
                                  );
    return em;
}

void em_push(void *em, void *event)
{
    Event_manager_t *em_ = em;
    em_->push(em_->container, event);
}

void* em_pop(void *em)
{
    Event_manager_t *em_ = em;
    return em_->pop(em_->container);
}

//
#include "callback_manager.h"

void em_iterator(void *em)
{
    Event_manager_t *em_ = em;
    while(!em_->is_empty(em_->container))
    {
        printf(" @@@ \n");
        Event_t *event = em_pop(em_);
        printf("event_type : %d ==== \n", get_event_type(event));
        cb_iterator_event(event);
    }
}
