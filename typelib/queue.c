#include "queue.h"

void QUEUE_init(QUEUE_t* item){
	item->len = 0;
	item->root = 0;
	item->tail = 0;
	return;
}

QUEUE_t* QUEUE_new(void){
	QUEUE_t* item = malloc(sizeof(QUEUE_t));
	QUEUE_init(item);
	return item;
}

void QUEUE_push(QUEUE_t* item, void* cont){
	LIST_t* nw = LIST_new();
	item->len++;
	if(item->tail){
		item->tail->next = nw;
		item->tail = nw;
	}else{
		item->tail = item->root = nw;
	}
	return;
}

void* QUEUE_pop(QUEUE_t* item){
	void* out;
	if(item->root){
		out = item->root;
		item->root = item->root->next;
		item->len--;
		if(!item->root){
			item->tail = 0;
		}
	}else{
		out = 0;
	}
	return out;
}

void QUEUE_del(QUEUE_t* item){
	LIST_clean(item->root);
	free(item);
	return;
}

void QUEUE_deepClean(QUEUE_t* item, void (*del)(void*)){
	LIST_deepClean(item->root, del);
	free(item);
	return;
}
