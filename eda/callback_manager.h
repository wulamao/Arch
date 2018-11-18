#ifndef CALLBACK_MANAGER_H_
#define CALLBACK_MANAGER_H_

typedef struct _Cbk_manager_t Cbk_manager_t;

//typedef void * (*cbkm_create)(void);
//typedef void (*cbkm_destroy)(void * c);
//typedef void* (*cbkm_push)(void * c, void* data);
//typedef void * (*cbkm_pop)(void * c);
//typedef void * (*cbkm_lookup)(void * c, unsigned int method);
//typedef void * (*cbkm_iterator)(void * c);
//typedef void (*cbkm_sort)(void * c);
//typedef int (*cbkm_is_empty)(void * c);

Cbk_manager_t *new_cbkm(void *create,
                        void *destroy,
                        void *push,
                        void *pop,
                        void *lookup,
                        void *iterator,
                        void *sort,
                        void *is_empty
                        );

void set_max_cbkm(Cbk_manager_t * cbkm, unsigned int max_size);
void *get_cbkm_container(void *cbkm);
void delete_cbkm(void *cbkm);
void *cbkm_init(void);
void cbkm_push(void *cbkm, void *event);
void *cbkm_pop(void *cbkm);
void cbkm_iterator(void *cbkm, void *arg, void *context);
#endif
