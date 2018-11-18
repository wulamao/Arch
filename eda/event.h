#ifndef EVENT_H_
#define EVENT_H_

/**
 * define event message type.
 */
typedef enum {
    emsg_no1 = 0,
    emsg_no2,
    EMSG_MAX
} Event_msg_t;

typedef struct _Event_pair_t Event_pair_t;
typedef Event_pair_t Event_t;
// typedef void *EventContainer;

Event_t *new_event(Event_msg_t msg_no,
                        void *head,
                        void *arg,
                        void *context,
                        char *str,
                        void *cbkm
                        );

void delete_event(void *event);

void cb_reg_event(void *event, void *cbk);
void cb_iterator_event(void *event);
unsigned int get_emsg_num(void);
unsigned int get_event_type(void *event);

#endif

