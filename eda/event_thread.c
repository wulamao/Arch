#include "pt.h"

#include "event.h"
#include "event_manager.h"


void test_cb1(void *arg, void *context)
{
    printf(" I'm cb1 ~ %d, %d \n", arg, context);
}

void test_cb2(void *arg, void *context)
{
    printf(" I'm cb2 ~ %d, %d \n", arg, context);
}

void test_cb3(void *arg, void *context)
{
    printf(" I'm cb3 ~ %d, %d \n", arg, context);
}


int event_thread(struct pt *pt)
{
    PT_BEGIN(pt);
//
    Event_t *event1 = new_event(emsg_no1,0,1,2,
                                "event 1 text" );
    Event_t *event2 = new_event(emsg_no2,0,3,4,
                                "event 2 text" );

    em_register(event1, test_cb1);
    em_register(event1, test_cb2);
    em_register(event2, test_cb1);
    em_register(event2, test_cb3);

    set_event_para(event1,3,4);

    em_push_event(event1);
    em_push_event(event2);

    while (1)
    {
        em_iterator();
        /* Wait until the other protothread has set its flag. */
        PT_WAIT_UNTIL(pt, 0 != 0);
        printf(" ==== \n");
    }

    PT_END(pt);
}

