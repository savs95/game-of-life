prog : util.o life.o
	gcc -o prog util.o life.o

util.o : util.c util.h
	gcc -c util.c

life.o : life.c
	gcc -c life.c

clean :
	rm life util.o life.o 
