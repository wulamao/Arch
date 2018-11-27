
#include "event.h"
#include "queue.h"



typedef void *CB_LIST_DS;

void *new_cbf_list(void)
{
    return queue_new();
}

Event_t *new_event(Event_msg_t msg_no,
                        unsigned int priority,
                        //void *cbf_list,
                        void *arg,
                        void *context,
                        const char *str
                        )
{
    //Cbk_manager_t *cbkm_ = cbkm;
    Event_t *event    = (Event_t *)malloc(sizeof(Event_t));
    event->key        = msg_no;
    event->cbf_list   = new_cbf_list();
    event->arg        = arg;
    event->context    = context;
    event->describe   = str;
    return event;
}



void delete_event(void *event)
{
    Event_t *event_ = event;
    queue_free(event_->cbf_list);
    free(event);
}


unsigned int get_emsg_num(void)
{
    return EMSG_MAX;
}

void set_event_para(Event_t *ev, void *arg,void *context)
{
    ev->arg = arg;
    ev->context = context;
}



