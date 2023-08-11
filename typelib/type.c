#include "type.h"

void TYPE_init(TYPE_t* item, uint16_t mode, size_t size, void* data){
	if(mode&TYPE_DICT) DICT_init(&(item->dict));
	else item->dict = 0;
	if(mode&TYPE_CALL) DARRAY_init(&(item->darray), sizeof(TYPE_t));
	else item->darray = 0;
	item->type = mode;
	item->size = size;
	itme->data = data;
	return;
}

void TYPE_set(TYPE_t* item, char* key, TYPE_t* value){
	if(!item) return;
	if(!(item->mode&TYPE_DICT)) return;
	DICT_set(&(item->DICT), key, value);
	return;
}

TYPE_t* TYPE_get(TYPE_t* item, char* key){
	if(!item) return 0;
	if(!(item->mode&TYPE_DICT)) return 0;
	return (TYPE_t*)DICT_get(&(item->dict), key);
}
