#include "http.h"

void HTTP_init(HTTP_t* item){
	item->status = 0;
	item->version = 3;
	item->header = 0;
	item->content = 0;
	DICT_init(&(item->tag));
	return;
}

HTTP_t* HTTP_new(void){
	HTTP_t* out = malloc(sizeof(HTTP_t));
	HTTP_init(out);
	return out;
}

void HTTP_del(HTTP_t* item){
	free(item);
	return;
}

char* HTTP_rec_str(HTTP_t* item){
	char buf[2048];
	DARRAY_t data;
	DARRAY_init(&data, sizeof(char));
	sprintf(buf, "HTTP/%d %d \r\n", item->version, item->status);
	DARRAY_append(&data, buf, strlen(buf));
	DARRAY_append(&data, item->header, strlen(item->header));
	sprintf(buf, "\r\n");
	DARRAY_append(&data, buf, strlen(buf));
	DARRAY_append(&data, item->content, strlen(item->content));
	return (char*)data->data;
}

char* HTTP_send_str(HTTP_t* item){

