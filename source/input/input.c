#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"

void help( void )
{
	printf( "Witaj w symulatorze automatu komorkowego.\n" );
	printf( "Program generuje wybrana liczbe pokolen komorek przedstawionych w pliku PNG oraz tworzy animacje GIF.\n" );
	printf( "Aby skorzystac z programu, wywolaj go z argumentami w nastepujacej kolejnosci:\n" );
	printf( "1) Nazwa pliku PNG z mapa komorek,\n" );
	printf( "2) Liczba generacji do wygenerowania,\n" );
	printf( "3) Opoznienie miedzy klatkami w pliku GIF (1s = 100).\n" );
}

int input_analizer( int argc, char **argv )
{
	if( argc == 1 )
	{
		printf( "Nie podano nazwy pliku PNG.\nProgram konczy dzialanie.\n" );
		printf( "Aby wyswietlic pomoc, uruchom program z argumentem \"help\" lub \"h\".\n" );
		return EXIT;
	}

	if( strcmp( argv[1], "h" ) == 0 || strcmp( argv[1], "help" ) == 0 )
    	{
        	help();
        	return EXIT;
    	}
    	FILE *png = fopen( argv[1], "r" );
    	if( png == NULL )
    	{
        	printf( "Nie znaleziono pliku o nazwie %s.\nProgram konczy dzialanie.\n", argv[1] );
        	return EXIT;
    	}
    	else if( argc == 2)
    	{
        	fclose( png );
        	printf( "Nie podano liczby generacji oraz opoznienia.\n" );
        	printf( "Program przyjmie wartosci domyslne n = %d, t = %d.\n", DEFAULT_NOGEN, DEFAULT_DELAY );
        	return SET_DEFAULT;
    	}

	if( argv[2][0] == '-' )
	{
		printf( "Problem z argumentem n = %s. Liczba generacji nie moze byc ujemna.\n", argv[2] );
		printf( "Program przyjmie wartosci domyslne n = %d, t = %d.\n", DEFAULT_NOGEN, DEFAULT_DELAY );
		return SET_DEFAULT;
	}
	int i;
	for( i = 0; i < strlen( argv[2] ); i++ )
		if( argv[2][i] < '0' || argv[2][i] > '9' )
		{
			printf( "Problem z argumentem n = %s. Ilosc generacji musi byc okreslana przez liczbe.\n", argv[2] );
			printf( "Program przyjmie wartosci domyslne n = %d, t = %d.\n", DEFAULT_NOGEN, DEFAULT_DELAY );
			return SET_DEFAULT;
		}

	/*if( nogen % 2 != 0 && nogen % 2 != 1 )
	{
		printf( "Problem z argumentem n = %s. Liczba generacji musi byc liczba naturalna.\n", argv[2] );
		printf( "Program przyjmie wartosci domyslne n = %d, t = %d.\n", DEFAULT_NOGEN, DEFAULT_DELAY );
		return SET_DEFAULT;
	}*/
	if( argc == 3)
    	{
        	printf( "Nie podano opoznienia.\n" );
        	printf( "Program przyjmie wartosc domyslna t = %d.\n", DEFAULT_DELAY );
        	return SET_DELAY;
    	}

	if( argc == 4 )
	{
		if( argv[3][0] == '-' )
		{
			printf( "Problem z argumentem t = %s. Opoznienie nie moze byc ujemne.\n", argv[3] );
			printf( "Program przyjmie wartosc domyslna t = %d.\n", DEFAULT_DELAY );
			return SET_DELAY;
		}
		for( i = 0; i < strlen( argv[3] ); i++ )
			if( argv[3][i] < '0' || argv[3][i] > '9' )
			{
				printf( "Problem z argumentem t = %s. Opoznienie musi byc okreslane przez liczbe.\n", argv[3] );
				printf( "Program przyjmie wartosc domyslna t = %d.\n", DEFAULT_DELAY );
				return SET_DELAY;
			}
		/*if( delay % 2 != 0 && delay % 2 != 1 )
		{
			printf( "Problem z argumentem t = %s. Opoznienie musi byc liczba naturalna.\n", argv[3] );
			printf( "Program przyjmie wartosc domyslna t = %d.\n", DEFAULT_DELAY );
			return SET_DELAY;
		}*/
	}	
	
	else if( argc >= 5 )
	{
		printf( "Zbyt duzo argumentow. Nadobowiazkowe argumenty zostana zignorowane.\n" );
		printf( "Aby wyswietlic pomoc, uruchom program z argumentem \"help\" lub \"h\".\n" );
	}
	
	return 0;
}
