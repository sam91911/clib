#include "type.h"

void TYPE_init(TYPE_t* item, uint16_t mode, size_t size, void* data){
	item->type = mode;
	if(mode) memset(&(item->dict), 0, sizeof(DICT_t));
	else DICT_init(&(item->dict), 0, 16);
	item->size = size;
	item->data = data;
	return;
}

void TYPE_set(TYPE_t* item, char* key, TYPE_t* value){
	if(!item) return;
	if((item->type&0x03)) return;
	DICT_set(&(item->dict), key, value);
	return;
}

TYPE_t* TYPE_get(TYPE_t* item, char* key){
	if(!item) return 0;
	if((item->type&0x03)) return 0;
	return (TYPE_t*)DICT_get(&(item->dict), key);
}

void TYPE_del(TYPE_t* item){
	if(!item) return 0;
	if((item->dict.data)) DICT_del(&(item->dict));
	free(item);
	return;
}
