#include "xxhash.h"
#define P1 11400714785074694791
#define P2 14029467366897019727
#define P3 1609587929392839161
#define P4 9650029242287828579
#define P5 2870177450012600261
#define rol(x,y) (((x) << (y))|((x) >> (64-(y))))

void XXHASH_init(XXHASH_t* item, uint64_t seed){
	item->seed = seed;
	item->v1 = seed + P1 + P2;
	item->v2 = seed + P2;
	item->v3 = seed;
	item->v4 = seed - P1;
	memset(item->data, 0, 32);
	item->len = 0;
	item->memsize = 0;
	return;
}

void XXHASH_update(XXHASH_t* item, uint8_t* data, uint64_t len){
	uint8_t* p = data;
	uint8_t* end = data+len;
	uint8_t* limit = end - 32;
	item->len += len;
	uint64_t v1, v2, v3, v4;
	if((item->memsize + len) < 32){
		memcpy((item->data + item->memsize), data, len);
		item->memsize += len;
		return;
	}
	if(item->memsize){
		memcpy((item->data + item->memsize), data, 32-item->memsize);
		v1 = item->v1;
		v2 = item->v2;
		v3 = item->v3;
		v4 = item->v4;
		v1 += (*(uint64_t*)(data + 0)) * P2;
		v1 = rol(v1, 31);
		v1 *= P1;
		v2 += (*(uint64_t*)(data + 8)) * P2;
		v2 = rol(v2, 31);
		v2 *= P1;
		v3 += (*(uint64_t*)(data + 16)) * P2;
		v3 = rol(v3, 31);
		v3 *= P1;
		v4 += (*(uint64_t*)(data + 32)) * P2;
		v4 = rol(v4, 31);
		v4 *= P1;
		item->v1 = v1;
		item->v2 = v2;
		item->v3 = v3;
		item->v4 = v4;
		p += 32-item->memsize;
		item->memsize = 0;
	}

	if(p + 32 <= end){
		v1 = item->v1;
		v2 = item->v2;
		v3 = item->v3;
		v4 = item->v4;
		do{
		v1 += (*(uint64_t*)(p + 0)) * P2;
		v1 = rol(v1, 31);
		v1 *= P1;
		v2 += (*(uint64_t*)(p + 8)) * P2;
		v2 = rol(v2, 31);
		v2 *= P1;
		v3 += (*(uint64_t*)(p + 16)) * P2;
		v3 = rol(v3, 31);
		v3 *= P1;
		v4 += (*(uint64_t*)(p + 32)) * P2;
		v4 = rol(v4, 31);
		v4 *= P1;
		p += 32;
		} while(p <= limit);
		item->v1 = v1;
		item->v2 = v2;
		item->v3 = v3;
		item->v4 = v4;
	}
	if(p < end){
		memcpy(item->data, p, end-p);
		item->memsize = (uint8_t)(end-p);
	}
	return;
}

uint64_t XXHASH_final(XXHASH_t* item){
	uint8_t* p = item->data;
	uint8_t* end = item->data + item->memsize;
	uint64_t h64, v1, v2, v3, v4;
	if(item->len >= 32){
		v1 = item->v1;
		v2 = item->v2;
		v3 = item->v3;
		v4 = item->v4;
		h64 = rol(v1, 1) + rol(v2, 7) + rol(v3, 12) + rol(v4, 18);
		v1 *= P2;
		v1 = rol(v1, 31);
		v1 *= P1;
		v2 *= P2;
		v2 = rol(v2, 31);
		v2 *= P1;
		v3 *= P2;
		v3 = rol(v3, 31);
		v3 *= P1;
		v4 *= P2;
		v4 = rol(v4, 31);
		v4 *= P1;
		h64 ^= v1;
		h64 = h64*P1 + P4;
		h64 ^= v2;
		h64 = h64*P1 + P4;
		h64 ^= v3;
		h64 = h64*P1 + P4;
		h64 ^= v4;
		h64 = h64*P1 + P4;
	}else{
		h64 = item->seed + P5;
	}
	
	h64 += item->len;

	for(;(p+8) <= end;p+=8){
		v1 = *(uint64_t*)p;
		v1 *= P2;
		v1 = rol(v1, 31);
		v1 *= P1;
		h64 ^= v1;
		h64 = h64*P1 + P4;
	}

	if((p+4) <= end){
		h64 ^= ((uint64_t)(*(uint32_t*)p))*P1;
		h64 = rol(h64, 23) * P2 + P3;
		p += 4;
	}

	for(;p<end;p++){
		h64 ^= (*p) * P5;
		h64 = rol(h64, 11) * P1;
	}

	h64 ^= (h64 >> 33);
	h64 *= P2;
	h64 ^= (h64 >> 29);
	h64 *= P3;
	h64 ^= (h64 >> 32);
	return h64;
}
