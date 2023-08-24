#include "darray.h"

void DARRAY_init(DARRAY_t* item, size_t size){
	item->len = 0;
	item->size = size;
	item->mlen = 32;
	item->data = malloc(size*32);
	return;
}

DARRAY_t* DARRAY_new(size_t size){
	DARRAY_t* out = malloc(sizeof(DARRAY_t));
	DARRAY_init(out, size);
	return out;
}

void* DARRAT_get(DARRAY_t* item, unsigned int ind){
	if(item->len <= ind) return 0;
	return (item->data + (item->size*ind));
}

void DARRAY_append(DARRAY_t* item, void* thx, unsigned int len){
	if((item->len+len) => item->mlen){
		item->mlen *= ((item->len+len)/item->mlen)+1;
		item->data = relloc(item->data, item->mlen*item->size);
	}
	memcpy((item->data+((item->len)*item->size)), thx, item->size*len);
	item->len += len;
	return 0;
}

void DARRAY_set(DARRAY_t* item, unsigned int ind, void* thx){
	if(ind > item->len) return;
	if(ind == item->len){
		DARRAY_append(item, thx);
		return;
	}
	memcpy((item->data+(item->size*ind)), thx, item->size);
	return;
}

void DARRAY_del(DARRAY_t* item){
	free(item->data);
	free(item);
	return;
}
