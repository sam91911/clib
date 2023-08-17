#ifndef DICTIO_H
#define DICTIO_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../typelib/dict.h"
void DICTIO_save(FILE*, DICT_t*);
void DICTIO_load(FILE*, DICT_t*);

#endif
