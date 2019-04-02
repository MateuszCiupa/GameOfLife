#include "../png/png_operator.h"
#include "../memory/memory.h"
#include "../input/input.h"

int main(int argc, char **argv) {
// DEKLARACJA WSZYSTKICH ZMIENNYCH

	unsigned char **old_matrix = NULL; // STARA MACIERZ
	unsigned char **new_matrix = NULL; // NOWA MACIERZ
	unsigned char **tmp = NULL; // TYMCZASOWA POMOC W ZAMIANIE STAREJ MACIERZY Z NOWĄ
	int height, width, nogen, i, input_return, delay; // WYSOKOŚĆ I SZEROKOŚĆ MACIERZ, LICZBA GENERACJI, ITP...
	FILE *wfile = fopen("wfile.txt", "w"); // "write file", plik do zapisu kolejnych nazw plików png (wygenerowanych w write_png_file) 

// ANALIZATOR SKŁADNI
	switch(input_return = input_analizer(argc, argv)){
		case EXIT:
			return EXIT_FAILURE;
			break;
		case SET_DEFAULT:
			nogen = DEFAULT_NOGEN;
			delay = DEFAULT_DELAY;
			break;
		case SET_DELAY:
			nogen = atoi(argv[2]);
			delay = DEFAULT_DELAY;
			break;
		case 0:
			nogen = atoi(argv[2]);
			delay = atoi(argv[3]);
	} 

	char *png_file = argv[1];

	if((old_matrix = read_png_file(png_file, &width, &height)) == NULL) // CZYTAM PLIK WEJŚCIOWY PNG I ZAPISUJĘ GO W MACIERZY old_matrix
		return 1;

	if((new_matrix = create_new_matrix(height, width)) == NULL) // TWORZĘ NOWĄ MACIERZ new_matrix O WYMIARACH MACIERZY old_matrix
		return 1;

	system("touch files/nullpng.png"); //BRAK BLEDU PRZY PROBIE USUNIECIA PLIKOW W PUSTYM KATALOGU	
	system("rm files/*.png");
// ZACZYNAM TWORZENIE KOLEJNYCH GENERACJI 

	for(i = 0; i < nogen; i++) {
		next_gen(old_matrix, new_matrix, height, width); // MACIERZ new_matrix JEST WYPEŁNIONA NOWĄ GENERACJĄ KOMÓREK

		if(write_png_file(i, width, height, new_matrix, wfile)) // NA PODSTAWIE MACIERZY new_matrix TWORZYMY PLIK PNG
			return 1;

		tmp = new_matrix;
		new_matrix = old_matrix;
		old_matrix = tmp;
	}

	fclose(wfile); 

	free_matrix(old_matrix, new_matrix, height); 

	gif_maker(delay); 

	return 0;
}
