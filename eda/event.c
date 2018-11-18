#include "event.h"

#include "event_behavior.h"
#include "cb_behavior.h"

//# 注册回调函数
    //涉及到 设置优先级等
//# 事件入队出队 (封装成一个函数)


/**
 * event manager entity.
 */
Event_manager_t EManager =
{
    .init      = eq_init,
    .del       = eq_del,
    .push      = eq_push,
    .pop       = eq_pop,
    .lookup    = eq_lookup,
    .iterator  = eq_iterator,
    .is_empty  = eq_is_empty,
};

/**
 * cb manager entity.
 */
Cb_manager_t CBManager =
{
    .create     = cbq_init,
    .destroy    = cbq_del,
    .push       = cbq_push,
    .pop        = cbq_pop,
    .lookup     = cbq_lookup,
    .iterator   = cbq_iterator,
    .sort       = cbq_sort,
    .is_empty   = cbq_is_empty,
};

void* event_init(void)
{
    return EManager.init();
}

void* cb_init(void)
{
    return CBManager.create();
}

void* event_push(EventContainer* event_queue, void* e)
{
    EManager.push(event_queue, e);
}

void* cb_reg(Event_pair_t* event_no, void* cb)
{
    CBManager.push(event_no->event.cb_head, cb);
}

int event_check(EventContainer* event_queue)
{
    // while event queue is not empty
    if (!eq_is_empty(event_queue))
    {
        // get event msg
        Event_pair_t* ev = (Event_pair_t *)EManager.pop(event_queue);
        // while cb queue is not empty
        while (!cbq_is_empty(ev->event.cb_head))
        {
            Cb_t* cbx = (Cb_t *)CBManager.pop(ev->event.cb_head);
            cbx->func(ev->event.arg,ev->event.context);
        }
    } 

    return 0;
}