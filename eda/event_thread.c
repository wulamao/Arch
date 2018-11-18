#include "pt.h"
#include "event.h"


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

#include "cb_behavior.h"



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

    event1.event.cb_head = cb_init();
    /* 回调函数注册 */
    Cb_t cb2,cb3;

    cb2.func = test_cb2;
    cb3.func = test_cb3;

    cb_reg(&event1, &cb1);
    cb_reg(&event1, &cb2);
    cb_reg(&event1, &cb3);

    /* event container pointer. */
    EventContainer event_queue = event_init();
    // emit emsg_no1
    event_push(event_queue, &event1);

    printf(" event_queue address is %#x \n", event_queue);
    printf(" event1.event.head address is %#x \n", event1.event.cb_head);

    while (1)
    {

        event_check(event_queue);
        /* Wait until the other protothread has set its flag. */
        PT_WAIT_UNTIL(pt, 0 != 0);
        printf(" ==== \n");
    }

    PT_END(pt);
}

