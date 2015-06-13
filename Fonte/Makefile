all: prog

y.tab.c y.tab.h: yacc.y
	yacc -d yacc.y

lex.yy.c: lex.l y.tab.h
	lex lex.l

prog: *.c interface/*.c interface/*.h
	gcc *.c interface/*.c -lfl -o prog -Wall

clean:
	rm prog
	rm *.dat
