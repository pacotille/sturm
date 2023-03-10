#
# Makefile
#
#	command file for make to compile the solver.

solve: main.o sturm.o util.o
	cc -g -o solve main.o sturm.o util.o -lm

clean:
	/bin/rm -f main.o sturm.o util.o solve

main.o: main.c
	cc -g -o main.o -c main.c -lm

util.o: util.c
	cc -g -o util.o -c util.c -lm

sturm.o: sturm.c
	cc -g -o sturm.o -c sturm.c -lm

