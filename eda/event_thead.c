#include "pt.h"
#include "event.h"
#include "event_behavior.h"
#include "cb_behavior.h"

#include "queue.h"

void test_cb1(void *arg, void *context)
{
    printf(" I'm cb1 ~ %d, %d", arg, context);
}

void test_cb2(void *arg, void *context)
{
    printf(" I'm cb2 ~ %d, %d", arg, context);
}

void test_cb3(void *arg, void *context)
{
    printf(" I'm cb3 ~ %d, %d", arg, context);
}

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

/**
 * event entity.
 */
Event_pair_t event1 =
{
    .type = emsg_no1,
    .event = {
        .cb_head = 0,
        .arg = 1,
        .context = 2,
        .des = "test notify message!"
    }
};

Cb_t cb1 = {
    .id = 3,
    .priority = 4,
    .func = test_cb1,
};

int event_thread(struct pt *pt)
{
    PT_BEGIN(pt);

    event1.event.cb_head = CBManager.create();
    /* 回调函数注册 */
    Cb_t cb2,cb3;

    cb2.func = test_cb2;
    cb3.func = test_cb3;

    CBManager.push(event1.event.cb_head, &cb1);
    CBManager.push(event1.event.cb_head, &cb2);
    CBManager.push(event1.event.cb_head, &cb3);

    /* event container pointer. */
    EventContainer event_queue = EManager.init();
    // emit emsg_no1
    EManager.push(event_queue, &event1);

    printf(" event_queue address is %#x \n", event_queue);
    printf(" event1.event.head address is %#x \n", event1.event.cb_head);


    while (1)
    {
        // while event queue is not empty
        while (!eq_is_empty(event_queue))
        {
            // get event msg
            Event_pair_t* ev = (Event_pair_t *)EManager.pop(event_queue);
            // while cb queue is not empty
            while (!cbq_is_empty(event1.event.cb_head))
            {
                Cb_t* cbx = (Cb_t *)CBManager.pop(ev->event.cb_head);
                cbx->func(ev->event.arg,ev->event.context);
            }
        }

        /* Wait until the other protothread has set its flag. */
        PT_WAIT_UNTIL(pt, 0 != 0);
        printf(" ==== \n");
    }

    PT_END(pt);
}

