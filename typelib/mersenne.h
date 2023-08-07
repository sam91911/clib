#ifndef MERSENNE_H
#define MERSENNE_H
#include <stdint.h>
typedef struct {
	int index;
	uint32_t MT[624];
} MERSENNE_t;

void MERSENNE_init(MERSENNE_t*,uint32_t);
uint32_t MERSENNE_rand(MERSENNE_t*);

#endif
