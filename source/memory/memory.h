#include <stdio.h>
#include <stdlib.h>

#ifndef _MEMORY_H_
#define _MEMORY_H_

unsigned char **create_new_matrix(int height, int width);
void free_matrix(unsigned char **old_matrix, unsigned char **new_matrix, int height);

#endif
