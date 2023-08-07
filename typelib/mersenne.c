#include "mersenne.h"

void MERSENNE_init(MERSENNE_t* item, uint32_t seed){
	uint32_t i;
	item->index = 0;
	item->MT[0] = seed;
	for(i = 1; i < 624; i++)
		item->MT[i] = (0x6c078965 * (item->MT[i-1] ^ (item->MT[i-1] >> 30))) + i;
	return;
}

uint32_t MERSENNE_rand(MERSENNE_t* item){
	uint32_t i, y;
	if(item->index == 0)
		for(i = 0; i < 624; i++){
			y = (item->MT[i]&0x80000000)|(item->MT[(i+1)%624]&0x7fffffff);
			item->MT[i] = item->MT[(i+397)%624] ^ (y >> 1);
			if(y%2)
				item->MT[i] = item->MT[i] ^ 0x9908b0df;
		}

	y = item->MT[item->index];
	y = y ^ (y >> 11);
	y = y ^ ((y << 7) & 0x9d2c5680);
	y = y ^ ((y << 15) & 0xefc60000);
	y = y ^ (y >> 18);

	item->index = (item->index+1)%624;
	return y;
}
