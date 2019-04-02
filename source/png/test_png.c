#include "png_operator.h"

int main(int argc, char **argv) {
	unsigned char **row_pointers = NULL;	
	int height, width, i, j, k;
	char *file_name = argc > 1 ? argv[1] : "out.png";
	int nogen = argc > 2 ? atoi(argv[2]) : 5;
	int delay = argc > 3 ? atof(argv[3]) : 50;
	FILE *wfile = fopen("wfile.txt", "w");

	if((row_pointers = read_png_file(file_name, &width, &height)) == NULL)
		return 1;
	
	printf("--------\n");
	for(i = 0; i < height; i ++) {
		printf("| ");

		for(j = 0; j < width; j++)
			printf("%03u ", row_pointers[i][j]);

		printf(" |\n");
	}
	printf("--------\n");

	j = 0;
	k = 0;

	for(i = 0; i < nogen; i++) {
		if(write_png_file(i, width, height, row_pointers, wfile))
			return 1;

		if(k == width/2) {
			j++;
			k = 0;
		}

		if(j%2 == 0)
			row_pointers[j][2*k+1] = 0; 
		else
			row_pointers[j][2*k] = 0;
		k++;
	}

	fclose(wfile);

	gif_maker(delay);

	for(i = 0; i < height; i++)
		free(row_pointers[i]);

	free(row_pointers);

	return 0;
}
