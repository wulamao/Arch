#ifndef EVENT_H_
#define EVENT_H_

/**
 * define event message type.
 */
typedef enum {
    emsg_no1 = 0,
    emsg_no2,
    emsg_no3,
    EMSG_MAX
} Event_msg_t;


typedef struct _Cbf_t
{
    /* id */
    unsigned int id;
    /* priority */
    unsigned int priority;
    /* callback function pointer */
    void* (*func)(void *arg, void *context);
} Cbf_t;

typedef void* (*cb_func)(void *arg, void *context);

/**
 * define event value structure.
 */
typedef struct _Event_t
{
    /* event message type */
    Event_msg_t key;

    unsigned int priority;
    /* the address of container where saves call back functions */
    void *cbf_list;
    /* pass parameter */
    void *arg;
    /* context */
    void *context;
    /* describe string */
    char *describe;
} Event_t;

typedef struct _Event_t Event_t;
// typedef void *EventContainer;

Event_t *new_event(Event_msg_t msg_no,
                        unsigned int priority,
                        //void *cbf_list,
                        void *arg,
                        void *context,
                        const char *str
                        );

void delete_event(void *event);

unsigned int get_emsg_num(void);
unsigned int get_event_type(void *event);
void set_event_para(Event_t *ev, void *arg,void *context);

#endif

