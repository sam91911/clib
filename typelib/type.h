#ifndef TYPE_H
#define TYPE_H
#include "dict.h"
#include "darray.h"
#include <stdlib.h>
#include <stdint.h>
#define TYPE_CALL 0x0100
#define TYPE_DICT 0x0200
#define TYPE_EVAL 0x0400
typedef struct{
	DICT_t dict;
	DARRAY_t darray;
	uint16_t type;
	size_t size;
	void* data;
} TYPE_t;

void TYPE_init(TYPE_t*, uint16_t, size_t, void*);
void TYPE_set(TYPE_t*, char*, TYPE_t*);
TYPE_t* TYPE_get(TYPE_t*, char*);


#endif
