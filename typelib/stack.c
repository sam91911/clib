#include "stack.h"

void STACK_init(STACK_t* item){
	item->root = LIST_new();
	item->len = 0;
	return;
}

STACK_t* STACK_new(void){
	STACK_t* out = malloc(sizeof(STACK_t*));
	STACK_init(out);
	return out;
}

void STACK_del(STACK_t* item){
	if(!item) return;
	if(item->root) LIST_clean(item->root);
	free(item);
	return;
}

void STACK_deepClean(STACK_t* item, void (*del)(void*)){
	if(!item) return;
	if(item->root) LIST_deepClean(item->root, del);
	free(item);
	return;
}

void STACK_push(STACK_t* item, void* cont){
	if(!item) return;
	LIST_t* nw = LIST_new();
	nw->next = item->root;
	nw->item = cont;
	item->root = nw;
	item->len++;
	return;
}

void* STACK_pop(STACK_t* item){
	if(!item) return 0;
	if(!item->root) return 0;
	LIST_t* nw = item->root;
	item->root = nw->next;
	item->len--;
	void* out = nw->item;
	LIST_del(nw);
	return out;
}

unsigned int STACK_len(STACK_t* item){
	if(!item) return UINT_MAX;
	return item->len;
}
