
#include "event.h"
#include "callback_manager.h"
/**
 * define event value structure.
 */
typedef struct _Event_value_t
{
    /* the address of container where saves call back functions */
    void *cb_head;
    /* pass parameter */
    void *arg;
    /* context */
    void *context;
    /* describe string */
    char *des;
} Event_value_t;

/**
 * define event pair structure.
 */
typedef struct _Event_pair_t
{
    /* event message type */
    Event_msg_t key;
    /* event */
    Event_value_t* value;
    /* cb manager */
    Cbk_manager_t* cbkm;
} Event_pair_t;


Event_pair_t *new_event(Event_msg_t msg_no,
                        void *head,
                        void *arg,
                        void *context,
                        char *str,
                        void *cbkm
                        )
{
    Cbk_manager_t *cbkm_ = cbkm;
    Event_pair_t *event = (Event_pair_t *)malloc(sizeof(Event_pair_t));
    event->value = (Event_value_t *)malloc(sizeof(Event_value_t));

    event->key = msg_no;
    event->value->cb_head = head;
    event->value->arg     = arg;
    event->value->context = context;
    event->value->des     = str;
    event->cbkm           = cbkm_;

    return event;
}

void delete_event(void *event)
{
    free(event);
}

void cb_reg_event(void *event, void *cbk)
{
    Event_t *event_ = event;
    cbkm_push(event_->cbkm, cbk);
}

void cb_iterator_event(void *event)
{
    Event_t *event_ = event;
    cbkm_iterator(event_->cbkm, event_->value->arg, event_->value->context);
}

unsigned int get_emsg_num(void)
{
    return EMSG_MAX;
}

unsigned int get_event_type(void *event)
{
    Event_t *_event = event;
    return _event->key;
 }
