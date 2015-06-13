y.tab.c y.tab.h: yacc.y
	yacc -d yacc.y

lex.yy.c: lex.l y.tab.h
	lex lex.l

clean:
	rm y.tab.c lex.yy.c y.tab.h
