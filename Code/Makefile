all: main

main: main.o
	gcc -o main main.o huffman.o

main.o: main.c huffman.c
	gcc -c -g main.c huffman.c

clean: 
	rm *.o

