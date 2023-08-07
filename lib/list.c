#include "list.h"

void LIST_init(LIST_t* item){
	item->next = 0;
	item->item = 0;
	return;
}
LIST_t* LIST_new(void){
	LIST_t* out = malloc(sizeof(LIST_t));
	LIST_init(out);
	return out;
}

void LIST_del(LIST_t* item){
	if(!item) return;
	free(item);
	return;
}

void LIST_clean(LIST_t* item){
	if(!item) return;
	LIST_t* nw;
	LIST_t* nx;
	for(({nw = item; nx = nw?nw->next:0;}); nw; nx = ({nw = nx;nw?nw->next:0;})){
		free(nw);
	}
	return;
}

void LIST_deepClean(LIST_t* item, void (*del)(void*)){
	if(!item) return;
	LIST_t* nw;
	LIST_t* nx;
	for(({nw = item; nx = nw?nw->next:0;}); nw; nx = ({nw = nx;nw?nw->next:0;})){
		(*del)(nw->item);
		free(nw);
	}
	return;
}
