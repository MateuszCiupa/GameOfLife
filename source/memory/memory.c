#include "memory.h"

unsigned char **create_new_matrix(int height, int width) {
	unsigned char **row_pointers = (unsigned char **)malloc(sizeof(unsigned char *) * height);

	if(row_pointers == NULL) {
		printf("Problem z alokowaniem pamieci na macierz pliku PNG.\n");
		printf("Program konczy dzialanie.\n" );
		return NULL;
	}
	
	int i;

	for(i = 0; i < height; i++) {
		row_pointers[i] = (unsigned char *)malloc(sizeof(unsigned char) * width);
		if(row_pointers[i] == NULL) {
			printf("Problem z alokowaniem pamieci na wiersze macierzy pliku PNG.\n");
			printf("Program konczy dzialanie.\n" );
			return NULL;
		}
	}

	return row_pointers;
}

void free_matrix(unsigned char **old_matrix, unsigned char **new_matrix, int height) {
	int i;
	for(i = 0; i < height; i++) {
		free(old_matrix[i]);
		free(new_matrix[i]);
	}

	free(old_matrix);
	free(new_matrix);
}
