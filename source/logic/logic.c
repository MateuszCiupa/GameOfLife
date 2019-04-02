#include "logic.h"

unsigned char next_state(int dead_neighbors, int alive_neighbors, int current_state) {
	if(current_state == DEAD_CELL)
		if(alive_neighbors == 3)
			return ALIVE_CELL;
		else
			return DEAD_CELL;
	else
		if(alive_neighbors == 2 || alive_neighbors == 3)
			return ALIVE_CELL;
		else
			return DEAD_CELL;
}

void next_gen(unsigned char **old_matrix, unsigned char **new_matrix, int height, int width) {
	int i, j;
	int alive;
	int dead;

	for(i = 0; i < height; i++)
		for(j = 0; j < width; j++) {
			dead = 0;
			alive = 0;

			if(i > 0 && j > 0) 
				if(old_matrix[i-1][j-1] == DEAD_CELL)
					dead++;
				else
					alive++;
			
			if(i > 0)
				if(old_matrix[i-1][j] == DEAD_CELL)
					dead++;
				else
					alive++;

			if(i > 0 && j+1 < width) 
				if(old_matrix[i-1][j+1] == DEAD_CELL)
					dead++;
				else
					alive++;

			if(j > 0)
				if(old_matrix[i][j-1] == DEAD_CELL)
					dead++;
				else
					alive++;

			if(j+1 < width)
				if(old_matrix[i][j+1] == DEAD_CELL)
					dead++;
				else
					alive++;

			if(i+1 < height && j > 0)
				if(old_matrix[i+1][j-1] == DEAD_CELL)
					dead++;
				else
					alive++;

			if(i+1 < height)
				if(old_matrix[i+1][j] == DEAD_CELL)
					dead++;
				else
					alive++;

			if(i+1 < height && j+1 < width)
				if(old_matrix[i+1][j+1] == DEAD_CELL)
					dead++;
				else
					alive++; 

			if(old_matrix[i][j] == DEAD_CELL)
				new_matrix[i][j] = next_state(dead, alive, DEAD_CELL);			
			else
				new_matrix[i][j] = next_state(dead, alive, ALIVE_CELL);
		}
 
	// SPRAWDZAMY PIERWSZY WIERSZ
				
	// SPRAWDZAMY OSTATNI WIERSZ

	// SPRAWDZAMY PIERWSZĄ KOLUMNĘ

	// SPRAWDZAMY OSTATNIĄ KOLUMNĘ
}

