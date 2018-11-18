#include "callback_manager.h"
#include "cbk_behavior.h"
#include "callback.h"

/**
 * define callback manager structure.
 */
typedef struct _Cbk_manager_t
{
    /* max size */
    unsigned int max_size;
    /* size */
    unsigned int size;

    void *container;

    /* create cb queue */
    void * (*create)(void);
    /* delete cb queue */
    void (*destroy)(void * c);
    /* cb push */
    void * (*push)(void * c, void* data);
    /* cb pop */
    void * (*pop)(void * c);
    /* lookup */
    void * (*lookup)(void * c, unsigned int method);
    /* cb queue traversal */
    void * (*iterator)(void * c);
    /* sort */
    void (*sort)(void * c);
    /* is empty */
    int (*is_empty)(void * c);
} Cbk_manager_t;


Cbk_manager_t *new_cbkm(void *create,
                        void *destroy,
                        void *push,
                        void *pop,
                        void *lookup,
                        void *iterator,
                        void *sort,
                        void *is_empty
                        )
{
    Cbk_manager_t *cbkm = (Cbk_manager_t*)malloc(sizeof(Cbk_manager_t));

    cbkm->create   = create;
    cbkm->destroy  = destroy;
    cbkm->push     = push;
    cbkm->pop      = pop;
    cbkm->lookup   = lookup;
    cbkm->iterator = iterator;
    cbkm->sort     = sort;
    cbkm->is_empty = is_empty;

    cbkm->container = cbkm->create();

    return cbkm;
}

void set_max_cbkm(Cbk_manager_t * cbkm, unsigned int max_size)
{
    cbkm->max_size = max_size;
}

void delete_cbkm(void *cbkm)
{
    free(cbkm);
}

void *get_cbkm_container(void *cbkm)
{
    Cbk_manager_t *cbkm_ = cbkm;
    return cbkm_->container;
}

void *cbkm_init(void)
{
    Cbk_manager_t *cbkm = new_cbkm(cbq_init,
                                  cbq_del,
                                  cbq_push,
                                  cbq_pop,
                                  cbq_lookup,
                                  cbq_iterator,
                                  cbq_sort,
                                  cbq_is_empty
                                  );
    return cbkm;
}

void cbkm_push(void *cbkm, void *event)
{
    Cbk_manager_t *cbkm_ = cbkm;
    cbkm_->push(cbkm_->container, event);
}

void *cbkm_pop(void *cbkm)
{
    Cbk_manager_t *cbkm_ = cbkm;
    return cbkm_->pop(cbkm_->container);
}

void cbkm_iterator(void *cbkm, void *arg, void *context)
{
    Cbk_manager_t *cbkm_ = cbkm;
    while(!cbkm_->is_empty(cbkm_->container))
    {
        Cbk_t *cbk = cbkm_pop(cbkm_);
        cbk_fuc func = get_cbk_func(cbk);
        func(arg, context);
    }
}
