#ifndef XXHASH_H
#define XXHASH_H
#define rol(x,y) (((x) << (y))|((x) >> (64-(y))))
#include <stdint.h>
#include <string.h>

typedef struct{
	uint8_t data[32];
	uint8_t memsize;
	uint64_t len;
	uint64_t v1;
	uint64_t v2;
	uint64_t v3;
	uint64_t v4;
	uint64_t seed;
} XXHASH_t;

void XXHASH_init(XXHASH_t*, uint64_t);
void XXHASH_update(XXHASH_t*, uint8_t*, uint64_t);
uint64_t XXHASH_final(XXHASH_t*);
#endif
