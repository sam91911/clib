#ifndef DARRAY_H
#define DARRAY_H

#include <stdlib.h>
#include <string.h>
typedef struct{
	void* data;
	unsigned int len;
	size_t size;
	unsigned int mlen;
} DARRAY_t;

void DARRAY_init(DARRAY_t*, size_t);
DARRAY_t* DARRAY_new(size_t);
void* DARRAY_get(DARRAY_t*, unsigned int);
void DARRAY_append(DARRAY_t*, void*, unsigned int);
void DARRAY_set(DARRAY_t*, unsigned int, void*);
void DARRAY_del(DARRAY_t*);

#endif
