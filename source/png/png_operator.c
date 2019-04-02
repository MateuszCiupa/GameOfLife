#include "png_operator.h"

png_byte bit_depth;
png_byte color_type;

png_bytep *read_png_file(char *file_name, int *width, int *height) {
	char header[8];
	png_bytep *row_pointers;
	png_structp png_ptr;
	png_infop info_ptr;
	int number_of_passes;
	int x, y;

	FILE *fp = fopen(file_name, "rb");

	if(!fp)	{
		printf("[read_png_file] Plik %s nie moze zostac odczytany.\n", file_name);
		return NULL;
	}

	fread(header, 1, 8, fp);

	if(png_sig_cmp(header, 0, 8)) {
		printf("[read_png_file] Plik %s nie jest formatu PNG.\n", file_name);
		return NULL;
	}


	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL); 

	if(!png_ptr) {
		printf("[read_png_file] png_create_read_struct nie dziala.\n");
		return NULL;
	}	

	info_ptr = png_create_info_struct(png_ptr);

	if(!info_ptr) {
		printf("[read_png_file] png_create_info_struct nie dziala.\n");
		return NULL;
	}

	if(setjmp(png_jmpbuf(png_ptr))) {
		printf("[read_png_file] Wystapil blad podczas init_io.\n");
		return NULL;
	}

	png_init_io(png_ptr, fp);
	png_set_sig_bytes(png_ptr, 8);
	png_read_info(png_ptr, info_ptr);

	*width = png_get_image_width(png_ptr, info_ptr);
	*height = png_get_image_height(png_ptr, info_ptr);
	color_type = png_get_color_type(png_ptr, info_ptr);
	bit_depth = png_get_bit_depth(png_ptr, info_ptr);

	number_of_passes = png_set_interlace_handling(png_ptr);
	png_read_update_info(png_ptr, info_ptr);


	if(setjmp(png_jmpbuf(png_ptr))) {
		printf("[read_png_file] Wystapil blad podczas read_image.\n");
		return NULL;
	}


	row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * *height);

	for(y = 0; y < *height; y++)
		row_pointers[y] = (png_byte*)malloc(sizeof(png_byte) * *width);

	png_read_image(png_ptr, row_pointers);

	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	fclose(fp);

	return row_pointers;
}

int write_png_file(int nofile, int width, int height, unsigned char **row_pointers, FILE *wfile) {
	png_structp png_ptr;
	png_infop info_ptr;
	int number_of_passes;
	int x, y;
	double figure = nofile;
	int i;

	for(i = 0; figure >= 1; i++)
		figure = figure / 10;
 
	char file_name[16+i];
	sprintf(file_name, "files/pngout%d.png", nofile);
	FILE *fp = fopen(file_name, "wb");

	fprintf(wfile, "%s ", file_name);

	if (!fp) {
		printf("[write_png_file] Nie mozna otworzyc pliku %s w celu zapisu.\n", file_name);
		return 1;
	}

	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if (!png_ptr) {
		printf("[write_png_file] Wystapil blad podczas png_create_write_struct.\n");
		return 1;
	}

	info_ptr = png_create_info_struct(png_ptr);

	if (!info_ptr) {
		printf("[write_png_file] Wystapil blad podczas png_create_info_struct.\n");
		return 1;
	}

	if (setjmp(png_jmpbuf(png_ptr))) {
 		printf("[write_png_file] Wystapil blads podczas init_io.\n");
		return 1;
	}

	png_init_io(png_ptr, fp);

	if (setjmp(png_jmpbuf(png_ptr))) {
		printf("[write_png_file] Wystapil blad przy zapisywaniu naglowka.\n");
		return 1;
	}

	png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

	png_write_info(png_ptr, info_ptr);

	if (setjmp(png_jmpbuf(png_ptr))) {
		printf("[write_png_file] Wystapil blad zapisu.\n");
		return 1;
	}

	png_write_image(png_ptr, row_pointers);

	if (setjmp(png_jmpbuf(png_ptr))) {
		printf("[write_png_file] Wystapil blad w koncowej fazie zapisu.\n");
		return 1;
	}

	png_write_end(png_ptr, NULL);
	png_destroy_write_struct(&png_ptr, &info_ptr);

	fclose(fp);

	return 0;
}

void gif_maker(int delay) {
	int tmp = delay;
	int i;

	for(i = 0; tmp >= 1; i++)
		tmp = tmp / 10;

	char caption[47+i];
	sprintf(caption, "convert -delay %d @wfile.txt -loop 0 files/outgif.gif", delay);
	system(caption);
	system("rm wfile.txt");
}
