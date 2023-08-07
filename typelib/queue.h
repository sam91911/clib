#ifndef QUEUE_H
#define QUEUE_H
#include "list.h"
#include <stdlib.h>

typedef struct {
	LIST_t* root;
	LIST_t* tail;
	unsigned int len;
} QUEUE_t;

void QUEUE_init(QUEUE_t*);
QUEUE_t* QUEUE_new(void);
void QUEUE_push(QUEUE_t*, void*);
void* QUEUE_pop(QUEUE_t*);
void QUEUE_del(QUEUE_t*);
void QUEUE_deepClean(QUEUE_t*, void (*)(void*));

#endif
