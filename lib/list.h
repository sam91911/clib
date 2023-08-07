#ifndef LIST_H
#define LIST_H
#include <stdlib.h>

typedef struct list{
	struct list* next;
	void* item;
}	LIST_t;

void LIST_init(LIST_t*);
LIST_t* LIST_new();
void LIST_del(LIST_t*);
void LIST_clean(LIST_t*);
void LIST_deepClean(LIST_t*, void (*) (void*));

#endif
