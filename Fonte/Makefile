all: prog

prog: *.c interface/*.c interface/*.h
	gcc *.c interface/*.c -lfl -pthread -o prog -Wall -g

clean:
	rm prog
	rm *.dat
