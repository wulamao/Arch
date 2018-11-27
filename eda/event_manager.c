#include "event_manager.h"
#include "event.h"
#include "queue.h"

void *event_queue;
//void *cbf_list;


int event_push(void *queue, Event_t *event)
{
    queue_push_tail(queue, event);
	return 0;
}

Event_t * event_pop(void *queue)
{
	return  queue_pop_head(queue);
}

int event_queue_is_empty(void *queue)
{
	return queue_is_empty(queue);
}

void event_sort(void *queue)
{

}

void event_emit(void *queue, Event_msg_t key, void *arg, void *context)
{
    Event_t event;
    event.key = key;
    event.arg  = arg;
    event.context = context;
	event_push(queue, &event);
}


int cb_func_push(void *queue, Cbf_t *cbf)
{
    queue_push_tail(queue, cbf);
	return 0;
}

void * cb_func_pop(void *queue)
{
	return  queue_pop_head(queue);
}

int cb_func_sort()
{
	return 0;
}

int cb_list_is_null()
{
	return 0;
}

int cb_list_iterator()
{
	return 0;
}

void new_cbf()
{

}

void delete_cbf()
{

}


int em_register(void *event, void *cbf)
{
    Event_t *_event = event;
    queue_push_tail(_event->cbf_list, cbf);
    return 0;
}


int em_push_event(void *event)
{
    event_push(&event_queue, event);
    return 0;
}

int em_iterator(void)
{
    while(!event_queue_is_empty(&event_queue))
    {
        Event_t *ev = event_pop(&event_queue);
        while(!queue_is_empty(ev->cbf_list))
        {
            cb_func cbf = queue_pop_head(ev->cbf_list);
            printf("%d %d\n", ev->arg, ev->context);
            cbf(ev->arg, ev->context);
        }
    }
}
