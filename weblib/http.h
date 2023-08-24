#ifndef HTTP_H
#define HTTP_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <sys/socket.h>
#include <unistd.h>
#include "../typelib/dict.h"
#include "../typelib/darray.h"
#include "../iolib/dictio.h"
#define HTTP_Continue 100
#define HTTP_Switching_ProtoCol 101
#define HTTP_Processing 102
#define HTTP_OK 200
#define HTTP_Created 201
#define HTTP_Acepted 202
#define HTTP_Non-Authoritative_Information 203
#define HTTP_No_Content 204
#define HTTP_Reset_Content 205
#define HTTP_Partial_Content 206
#define HTTP_MultiStatus 207
#define HTTP_Multiple_Choice 300
#define HTTP_Moved_Permanently 301
#define HTTP_Found 302
#define HTTP_See_Other 303
#define HTTP_BadRequest 400
#define HTTP_Unauthorized 401
#define HTTP_Forbidden 403
#define HTTP_Not_Found 404
#define HTTP_Internal_Server_Error 500
#define HTTP_Bad_Gateway 502
#define HTTP_Service_Unavailable 503
typedef struct{
	int status;
	int version;
	char* header;
	char* content;
	uint64_t len;
	DICT_t tag;
} HTTP_t;

void HTTP_init(HTTP_t*);
HTTP_t* HTTP_new(void);
void HTTP_del(HTTP_t*);
char* HTTP_send_str(HTTP_t*);
char* HTTP_rec_str(HTTP_t*);
void HTTP_set(HTTP_t*, char*, char*);
char* HTTP_get(HTTP_t*, char*);
void HTTP_content(HTTP_t*, char*, uint64_t);


#endif
