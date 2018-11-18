#include "pt.h"

#include "event.h"
#include "callback.h"
#include "event_manager.h"
#include "callback_manager.h"


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
    unsigned int num = get_emsg_num();
    printf("emsg has %d members \n ",num);
//
    Event_manager_t *em = em_init();
//
    Cbk_manager_t *cbkm1 = cbkm_init();
    Cbk_manager_t *cbkm2 = cbkm_init();


    Event_t *event1 = new_event(emsg_no1,
                                get_cbkm_container(cbkm1),
                                0, 1,
                                "event1 test",
                                cbkm1);

    Event_t *event2 = new_event(emsg_no2,
                                get_cbkm_container(cbkm2),
                                2, 3,
                                "event2 test",
                                cbkm2);
//
    Cbk_t *cbk1 = new_cbk(0, 0, test_cb1);
    Cbk_t *cbk2 = new_cbk(0, 0, test_cb2);
    Cbk_t *cbk3 = new_cbk(0, 0, test_cb3);
//
    em_push(em, event1);
    em_push(em, event2);

    em_push(em, event1);
    em_push(em, event1);
    em_push(em, event1);
    em_push(em, event1);
    em_push(em, event1);
    em_push(em, event1);

    cb_reg_event(event1, cbk1);
    cb_reg_event(event1, cbk2);
    cb_reg_event(event2, cbk3);

    while (1)
    {
        em_iterator(em);
        /* Wait until the other protothread has set its flag. */
        PT_WAIT_UNTIL(pt, 0 != 0);
        printf(" ==== \n");
    }

    PT_END(pt);
}

