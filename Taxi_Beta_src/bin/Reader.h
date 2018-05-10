#ifndef READER_H_INCLUDED_
#define READER_H_INCLUDED_

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct map_obj
{  
char *x_names;
char *y_names;
char *arr;
int x;
int y;
int num_taxis;
} Map;

Map Reader(Map map);

#endif /* READER_H_INCLUDED_ */
