#include "logic.h"

void matrixToString(unsigned char **matrix, int height, int width) {
	int i, j;
	for(i = 0; i < height; i++) {
		for(j = 0; j < width; j++)
			printf("%3u ", matrix[i][j]);
		printf("\n");
	}
	printf("\n");
}

int main(void) {
	int height = 5;
	int width = 5;
	int i;
	int nogen = 5;
	unsigned char **tmp;
	unsigned char **old_matrix = (unsigned char **)malloc(sizeof(unsigned char *) * height);
	unsigned char **new_matrix = (unsigned char **)malloc(sizeof(unsigned char *) * height);

	for(i = 0; i < height; i++) {
		old_matrix[i] = (unsigned char *)malloc(sizeof(unsigned char) * width);
		new_matrix[i] = (unsigned char *)malloc(sizeof(unsigned char) * width);
	}

	old_matrix[0][0] =   0; old_matrix[0][1] = 255; old_matrix[0][2] = 255; old_matrix[0][3] =   0; old_matrix[0][4] = 255;
	old_matrix[1][0] = 255; old_matrix[1][1] = 255; old_matrix[1][2] =   0; old_matrix[1][3] =   0; old_matrix[1][4] =   0;
	old_matrix[2][0] =   0; old_matrix[2][1] = 255; old_matrix[2][2] =   0; old_matrix[2][3] =   0; old_matrix[2][4] = 255;
	old_matrix[3][0] =   0; old_matrix[3][1] =   0; old_matrix[3][2] = 255; old_matrix[3][3] = 255; old_matrix[3][4] = 255;
	old_matrix[4][0] = 255; old_matrix[4][1] =   0; old_matrix[4][2] =   0; old_matrix[4][3] = 255; old_matrix[4][4] =   0;	
	
	matrixToString(old_matrix, height, width);

	for(i = 0; i < nogen; i++) {
		next_gen(old_matrix, new_matrix, height, width);
		matrixToString(new_matrix, height, width);
		tmp = old_matrix;
		old_matrix = new_matrix;
		new_matrix = tmp;
	}

	for(i = 0; i < height; i++) {
		free(old_matrix[i]);
		free(new_matrix[i]);
	}

	free(old_matrix);
	free(new_matrix);

	return 0;
}
