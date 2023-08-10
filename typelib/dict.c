#include "dict.h"
#define xxhash(x, y, z) ({XXHASH_init(x, y); XXHASH_update(x, z, strlen(z)); XXHASH_final(x);})

void DICT_init(DICT_t* item, uint32_t seed){
	MERSENNE_init(&(item->rand), seed);
	item->h1 = (((uint64_t)MERSENNE_rand(&(item->rand)))<<32)|((uint64_t)MERSENNE_rand(&(item->rand)));
	item->h2 = (((uint64_t)MERSENNE_rand(&(item->rand)))<<32)|((uint64_t)MERSENNE_rand(&(item->rand)));
	item->len = 0;
	item->mlen = 32;
	item->data = calloc(32,sizeof(DICT_it));
	return;
}

DICT_t* DICT_new(uint32_t seed){
	DICT_t* out = malloc(sizeof(DICT_t));
	DICT_init(out, seed);
	return out;
}

void* DICT_get(DICT_t* item, char* key){
	if(!item) return 0;
	XXHASH_t hash;
	uint64_t id;
	id = (xxhash(&hash, item->h1, key)%item->mlen);
	if(!item->data[id].key) return 0;
	if(!strcmp(item->data[id].key, key)){
		return item->data[id].value;
	}
	id = (xxhash(&hash, item->h2, key)%item->mlen);
	if(!strcmp(item->data[id].key, key)){
		return item->data[id].value;
	}
	return 0;
}

void DICT_rm(DICT_t* item, char* key){
	if(!item) return 0;
	XXHASH_t hash;
	uint64_t id;
	id = (xxhash(&hash, item->h1, key)%item->mlen);
	if(!item->data[id].key) return 0;
	if(!strcmp(item->data[id].key, key)){
		item->data[id].key = 0;
		item->data[id].value = 0;
		return;
	}
	id = (xxhash(&hash, item->h2, key)%item->mlen);
	if(!strcmp(item->data[id].key, key)){
		item->data[id].key = 0;
		item->data[id].value = 0;
		return;
	}
	return 0;
}

void DICT_set(DICT_t* item, char* key, void* value){
	if(!item) return;
	DICT_it* old;
	uint64_t len;
	uint64_t i;
	XXHASH_t hash;
	uint64_t id;
	uint64_t loop_id;
	char* tmp_key;
	void* tmp_value;
	void* swp;
	id = (xxhash(&hash, item->h1, key)%item->mlen);
	if(item->data[id].key){
		if(!strcmp(key, item->data[id].key)){
			item->data[id].value = value;
			return;
		}
	}else{
		item->data[id].key = key;
		item->data[id].value = value;
		return;
	}
	id = (xxhash(&hash, item->h2, key)%item->mlen);
	if(item->data[id].key){
		if(!strcmp(key, item->data[id].key)){
			item->data[id].value = value;
			return;
		}
	}else{
		item->data[id].key = key;
		item->data[id].value = value;
		return;
	}
	if(item->len >= item->mlen/2){
		len = item->mlen;
		item->len = 0;
		item->mlen *= 2;
		old = item->data;
		item->data = calloc(item->mlen, sizeof(DICT_t));
		for(i = 0; i < len; i++)
			if(old[i].value)
				DICT_set(item, old[i].key, old[i].value);
		free(old);
	}
	id = (xxhash(&hash, item->h1, key)%item->mlen);
	tmp_key = key;
	tmp_value = value;
	for(;;){
		for(;;){
			if(item->data[id].key){
				loop_id = id;
				swp = item->data[id].key;
				item->data[id].key = tmp_key;
				tmp_key = swp;
				swp = item->data[id].value;
				item->data[id].value = tmp_value;
				tmp_value = swp;
				id = (xxhash(&hash, item->h2, tmp_key)%item->mlen);
				if(loop_id = id) break;
			}else{
				item->data[id].key = tmp_key;
				item->data[id].value = tmp_value;
				return;
			}
		}
		len = item->mlen;
		item->len = 0;
		old = item->data;
		item->data = calloc(item->mlen, sizeof(DICT_t));
		item->h1 = (((uint64_t)MERSENNE_rand(&(item->rand)))<<32)|((uint64_t)MERSENNE_rand(&(item->rand)));
		item->h2 = (((uint64_t)MERSENNE_rand(&(item->rand)))<<32)|((uint64_t)MERSENNE_rand(&(item->rand)));
		for(i = 0; i < len; i++)
			if(old[i].value)
				DICT_set(item, old[i].key, old[i].value);
		free(old);
	}
	return;
}

void DICT_del(DICT_t* item){
	free(item->data);
	free(item);
	return;
}
