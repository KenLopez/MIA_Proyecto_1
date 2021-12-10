# Makefile

FILES = analizador/Lexer.cpp analizador/Parser.cpp shared/Structs.cpp classes/mkdisk.cpp classes/rmdisk.cpp classes/fdisk.cpp classes/exec.cpp classes/rep.cpp shared/utilities.cpp main.cpp
CC = g++ 
CFLAGS = -g -ansi

main: $(FILES)
	$(CC) $(CFLAGS) $(FILES) -o proyecto_1

analizador/Lexer.cpp: analizador/Lexer.l
	flex analizador/Lexer.l

analizador/Parser.cpp: analizador/Parser.y analizador/Lexer.cpp
	bison analizador/Parser.y

clean:
	rm -f *.o *~ analizador/Lexer.cpp analizador/Lexer.h analizador/Parser.cpp analizador/Parser.h proyecto_1
