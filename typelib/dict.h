#ifndef DICT_H
#define DICT_H
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "xxhash.h"
#include "mersenne.h"

typedef struct{
	char* key;
	void* value;
} DICT_it;

typedef struct{
	uint64_t mlen;
	uint64_t len;
	MERSENNE_t rand;
	uint64_t h1;
	uint64_t h2;
	DICT_it* data;
} DICT_t;

void DICT_init(DICT_t*, uint32_t, uint64_t);
DICT_t* DICT_new(uint32_t, uint64_t);
void* DICT_get(DICT_t*, char*);
void DICT_set(DICT_t*, char*, void*);
void DICT_rm(DICT_t*, char*);
void DICT_del(DICT_t*);

#endif
