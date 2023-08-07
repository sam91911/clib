#ifndef STACK_H
#define STACK_H
#include "list.h"
#include <stdlib.h>
#include <limits.h>
typedef struct stack{
	LIST_t* root;
	unsigned int len;
} STACK_t;

void STACK_init(STACK_t*);
STACK_t* STACK_new(void);
void STACK_del(STACK_t*);
void STACK_deepClean(STACK_t*, void (*)(void*));
void STACK_push(STACK_t*, void*);
void* STACK_pop(STACK_t*);
unsigned int STACK_len(STACK_t*);

#endif
