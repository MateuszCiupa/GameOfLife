cell_machine: main_module.o input.o png.o memory.o logic.o
	cc main_module.o input.o png.o memory.o logic.o -lpng -o cell_machine
	rm -f *.o

main_module.o: main_module/main.c
	cc main_module/main.c -c -o main_module.o

input.o: input/input.c input/input.h
	cc input/input.c -c -o input.o

png.o: png/png_operator.c png/png_operator.h
	cc png/png_operator.c -c -o png.o

memory.o:  memory/memory.c memory/memory.h
	cc memory/memory.c -c -o memory.o

logic.o: logic/logic.c logic/logic.h
	cc logic/logic.c -c -o logic.o

test_input: input/input.c input/input.h input/test_input.c
	cc input/input.c input/test_input.c -o test_input

test_png: png/png_operator.c png/test_png.c
	cc png/png_operator.c png/test_png.c -lpng -o test_png

test_memory: memory/memory.c memory/test_memory.c
	cc memory/memory.c memory/test_memory.c -o test_memory

test_logic: logic/logic.c logic/test_logic.c
	cc logic/logic.c logic/test_logic.c -o test_logic
