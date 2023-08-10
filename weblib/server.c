#include "server.h"

int SERVER_init(SERVER_t* server, uint16_t msub, const char* path){
	struct stat buf;
	server->sub = 0;
	server->msub = msub;
	server->server_dir = path;
	if(access(path, F_OK)) mkdir(path, S_IRWXU|S_IRWXP|S_IRWXO);
	else{
		stat(path, &buf);
		if(!(buf.st_mode&S_IFDIR)) return -1;
	}
	server->server_P = 0;
	memset(&(server->addr), 0, sizeof(sockaddr));
	pid_t* sub_P = calloc(msub, sizeof(pid_t));
	server->socket = 0;
	return 0;
}

int SERVER_setPort(SERVER_t* item, uint16_t port){
	if(!item) return -1;
	*(uint16_t*)(item->addr.sa_data) = port;
	return 0;
}

int SERVER_setAddress(SERVER_t* item, uint8_t* addr){
	if(!item) return -1;
	memcpy(item->addr.sa_data+2, addr, 4);
	return 0;
}

int SERVER_load(SERVER_t* server, const char* path){
	struct stat buf;
	stat(path, &buf);
	if(!(access(path, F_OK)&&(buf.st_mode&S_IFDIR))) return -1;
	server->server_dir = path;
	return 0;
}

int SERVER_setMax(SERVER_t* item, uint16_t msub){
	int i,j;
	pid_t* nw = calloc(msub, sizeof(pid_t));
	for(i = j = 0; i < item->msub; i++){
		if(item->sub_P[i]){
			if(j == msub){
				kill(item->sub_P[i], SIGQUIT);
			}else{
				nw[j++] = item->sub_P[i];
			}
		}
	}
	free(item->sub_P);
	item->sub_P = nw;
	return 0;
}

int SERVER_close(SERVER_t* item){
	if(!item) return -1;
	int i;
	for(i = 0; i < item->msub; i++){
		if(item->sub_P[i]) kill(item->sub_P[i], SIGQUIT);
	}
	kill(item->server_P, SIGQUIT);
	int chstat;
	free(item->sub_P);
	free(item);
	wait(&chstat);
	if(!(chstat&(WEXITSTATUS|WIFEXITED))) return -1;
	return 0;
}

int SERVER_run(SERVER_t* item, int (*proc)(int)){
	if(!item) return -1;
	pid_t sp = fork();
	switch(sp){
		case -1:
			return -2;
		case 0:
			;
		default:
			item->server_P = sp;
			FILE* f;
			if(!(f = fopen(item->server_dir, "r+"))){
				SERVER_close(item);
				return -1;
			}
			
	}
	return 0;
}
