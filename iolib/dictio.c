#include "dictio.h"

int DICTIO_save(FILE* file, DICT_t* item){
	if(!(file && item)) return -1;
	int len = 0;
	len += fprintf(file, "{\n");
	uint64_t i;
	for(i = 0; i < item->mlen; i++){
		if(item->data[i].key){
			len += fprintf(file, "%s:%s;\n", item->data[i].key, item->data[i].value);
		}
	}
	len += fprintf(file, "}\n");
	return len;
}

int DICTIO_load(FILE* file, DICT_t* item){
	if(!(file && item)) return -1;
	int len = 0;
	int read;
	int i;
	char buffer1[2048];
	char buffer2[2048];
	int n1, n2;
	for(;(read == '{') || (read == EOF);len++){
		read = fgetc(file);
	}
	if(read == EOF) return -1;
	i = 0;
	n1 = 0;
	n2 = 0;
	for(;;len++){
		read = fgetc(file);
		if(read == EOF) return -1;
		if(read == '}') break;
		if(read == '\n') continue;
		if(read == '\t') continue;
		if(read == ':'){i = 1;n2 = 0;continue;}
		if(read == ';'){i = 0;n1 = 0;
			DICT_set(item, buffer1, buffer2);
			continue;}
		if(i){
			buffer2[n2++] = (char)read;
		}else{
			buffer1[n1++] = (char)read;
		}
	}
	return len;
}
