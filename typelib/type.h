#ifndef TYPE_H
#define TYPE_H
#include "dict.h"
#include <stdlib.h>
#include <stdint.h>
#define TYPE_CALL 0x0100
#define TYPE_DICT 0x0200
#define TYPE_EVAL 0x0400
typedef struct{
	DICT_t dict;
	uint16_t type;
	size_t size;
} TYPE_t;

void TYPE_init(TYPE_t*);
void TYPE_set(TYPE_t*, void*);
void TYPE_get(TYPE_t*, void*);


#endif
