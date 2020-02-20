CFLAGS = -O0 -ansi -pedantic -Wall 
prog1: main.c
	gcc $(CFLAGS) main.c -o prog1
#
#	gcc -O0	-ansi -pedantic -Wall prog1.c
clean:
	rm -f *.o

