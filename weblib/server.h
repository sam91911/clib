#ifndef SERVER_H
#define SERVER_H
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
typedef struct{
	uint16_t sub;
	uint16_t msub;
	char* server_dir;
	pid_t server_P;
	sockaddr addr;
	pid_t* sub_P;
	int socket;
} SERVER_t;

int SERVER_init(SERVER_t*, uint16_t, const char*);
int SERVER_setPort(SERVER_t*, uint16_t);
int SERVER_setAddress(SERVER_t*, uint8_t*);
int SERVER_load(SETVER_t*, const char*);
int SERVER_setMax(SERVER_t*, uint16_t);
int SERVER_close(SERVER_t*);
int SERVER_run(SERVER_t*, int(*)(int));
#endif
