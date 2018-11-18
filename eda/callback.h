#ifndef CALLBACK_H_
#define CALLBACK_H_

typedef struct _Cbk_t Cbk_t;
// typedef void *CbContainer;
typedef void* (*cbk_fuc)(void *arg, void *context);

Cbk_t *new_cbk(unsigned int id,
               unsigned int priority,
               void *func //cbk_fuc func
               );

void delete_cbk(void *cbk);
void *get_cbk_func(void *cbk);

#endif
