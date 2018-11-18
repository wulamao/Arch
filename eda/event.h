#ifndef EVENT_H_
#define EVENT_H_

#include "event_behavior.h"

/**
 * define event container structure.
 */
typedef void *EventContainer;


/**
 * define cb container structure.
 */
typedef void *CbContainer;

/**
 * define event message type.
 */
typedef enum {
    emsg_no1,
    EMSG_MAX
} Event_message_t;

/**
 * define callback function structure.
 */
typedef struct _Cb_t
{
    /* id */
    unsigned int id;
    /* priority */
    unsigned int priority;
    /* callback function pointer */
    void* (*func)(void *arg, void *context);
} Cb_t;

/**
 * define event structure.
 */
typedef struct _Event_t
{
    /* the address of container where saves call back functions */
    void *cb_head;
    /* pass parameter */
    void *arg;
    /* context */
    void *context;
    /* describe string */
    char *des;
} Event_t;

/**
 * define event pair structure.
 */
typedef struct _Event_pair_t
{
    /* event message type */
    Event_message_t type;
    /* event */
    Event_t event;
} Event_pair_t;

/**
 * define event manager structure.
 */
typedef struct _Event_manager_t
{
    /* create event container */
    EventContainer (*init)(void);
    /* delete event container */
    void (*del)(EventContainer c);
    /* cb register*/
    void* (*push)(EventContainer c, void *cb);
    /* cb remove*/
    void* (*pop)(EventContainer c);
    /* event lookup*/
    void* (*lookup)(EventContainer c, unsigned int method);
    /* event traversal*/
    void* (*iterator)(EventContainer c);
    /* sort */
    int (*is_empty)(EventContainer c);
} Event_manager_t;


/**
 * define callback manager structure.
 */
typedef struct _Cb_manager_t
{
    /* max size */
    unsigned int max_size;
    /* size */
    unsigned int size;

    /* create cb queue */
    CbContainer (*create)(void);
    /* delete cb queue */
    void (*destroy)(CbContainer c);
    /* cb push */
    void* (*push)(CbContainer c, void* data);
    /* cb pop */
    CbContainer (*pop)(CbContainer c);
    /* lookup */
    void* (*lookup)(CbContainer c, unsigned int method);
    /* cb queue traversal */
    void* (*iterator)(CbContainer c);
    /* sort */
    void (*sort)(CbContainer c);
    /* sort */
    int (*is_empty)(CbContainer c);
} Cb_manager_t;






extern void* event_init(void);
extern void* event_push(EventContainer* event_queue, void* e);
extern int event_check(EventContainer* event_queue);










#endif
