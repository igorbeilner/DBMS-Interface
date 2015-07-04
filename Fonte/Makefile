all: prog

prog: *.c interface/*.c interface/*.h
	gcc *.c interface/*.c -lfl -pthread -o ibetres -Wall -g

clean:
	rm prog
	rm *.dat
	rm ibetres/ -R
