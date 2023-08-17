#ifndef TYPE_H
#define TYPE_H
#include "dict.h"
#include "darray.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#define TYPE_INT 0x01
#define TYPE_FLOAT 0x02
#define TYPE_STRING 0x03
#define TYPE_FUNCTION 0x04
typedef struct{
	DICT_t dict;
	uint16_t type;
	size_t size;
	void* data;
} TYPE_t;

void TYPE_init(TYPE_t*, uint16_t, size_t, void*);
void TYPE_set(TYPE_t*, char*, TYPE_t*);
TYPE_t* TYPE_get(TYPE_t*, char*);
void TYPE_del(TYPE_t*);

#endif
