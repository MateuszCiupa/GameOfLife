#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <png.h>

#ifndef _PNGREAD_H_
#define _PNGREAD_H_

unsigned char **read_png_file(char *file_name, int *width, int *height);

int write_png_file(int nofile, int width, int height, unsigned char **row_pointers, FILE *wfile);

void gif_maker(int delay);

#endif
