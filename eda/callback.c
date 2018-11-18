#include "callback.h"

typedef struct _Cbk_t
{
    /* id */
    unsigned int id;
    /* priority */
    unsigned int priority;
    /* callback function pointer */
    void* (*func)(void *arg, void *context);
} Cbk_t;

Cbk_t *new_cbk(unsigned int id,
               unsigned int priority,
               void *func //cbk_fuc func
               )
{
    Cbk_t *cbk = (Cbk_t *)malloc(sizeof(Cbk_t));
    cbk->id       = id;
    cbk->priority = priority;
    cbk->func     = func;

    return cbk;
}

void delete_cbk(void *cbk)
{
    free(cbk);
}

void *get_cbk_func(void *cbk)
{
    Cbk_t *cbk_ = cbk;
    return cbk_->func;
}
