all: prog

prog: *.c interface/*.c interface/*.h
	gcc *.c interface/*.c -lfl -pthread -o ibetres.out -Wall -g

clean:
	rm ibetres.out
	rm *.dat
	rm ibetres/ -R
