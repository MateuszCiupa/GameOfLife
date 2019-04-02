#include <stdio.h>
#include <stdlib.h>
#define DEAD_CELL 255
#define ALIVE_CELL 0

#ifndef _LOGIC_H_
#define _LOGIC_H_

unsigned char next_state(int dead_neighbors, int alive_neighbors, int current_state);
void next_gen(unsigned char **old_matrix, unsigned char **new_matrix, int height, int width);

#endif
