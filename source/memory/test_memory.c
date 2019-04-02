#include "memory.h"

int main(void) {
	unsigned char **old_matrix = NULL;
	unsigned char **new_matrix = NULL;
	int height = 10;
	int width = 10;

	if((old_matrix = create_new_matrix(height, width)) == NULL) 
		return 1;

	if((new_matrix = create_new_matrix(height, width)) == NULL) 
		return 1;

	free_matrix(old_matrix, new_matrix, height);

	printf("Test modułu pamięci przebiegł pomyślnie.\n");

	return 0;
}
