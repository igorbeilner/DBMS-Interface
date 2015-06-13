%{
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "../buffend.h"

extern int  yylineno;
extern char* yytext[];
extern FILE * yyin;
extern FILE* outFile_p;
int noerror, col_count, val_count;

rc_insert GLOBAL_INS;

void yyerror(char *s, ...) {
	noerror = 0;
	/*extern yylineno;

	va_list ap;
	va_start(ap, s);

	fprintf(stderr, "%d: error: ", yylineno);
	vfprintf(stderr, s, ap);
	fprintf(stderr, "\n");
	*/
}

int yywrap() {
	return 1;
}

void setTable(char **nome) {
	GLOBAL_INS.tableName = malloc(sizeof(char)*(strlen(*nome)+1));

	strcpy(GLOBAL_INS.tableName, *nome);
	GLOBAL_INS.tableName[strlen(*nome)] = '\0';
}

void setColumn(char **nome) {
	GLOBAL_INS.columnName = realloc(GLOBAL_INS.columnName, (col_count+1)*sizeof(char *));

	GLOBAL_INS.columnName[col_count] = malloc(sizeof(char)*(strlen(*nome)+1));
	strcpy(GLOBAL_INS.columnName[col_count], *nome);
	GLOBAL_INS.columnName[col_count][strlen(*nome)] = '\0';

	col_count++;
}

void setValue(char *nome) {
	GLOBAL_INS.values = realloc(GLOBAL_INS.values, (val_count+1)*sizeof(char *));

	// Adiciona o valor no vetor de strings
	GLOBAL_INS.values[val_count] = malloc(sizeof(char)*(strlen(nome)+1));
	strcpy(GLOBAL_INS.values[val_count], nome);
	GLOBAL_INS.values[val_count][strlen(nome)] = '\0';

	val_count++;
}

void clearGlobalIns() {
    int i;

    if (GLOBAL_INS.tableName)
    	free(GLOBAL_INS.tableName);
    GLOBAL_INS.tableName = (char *)malloc(sizeof(char *));

    for (i = 0; i < GLOBAL_INS.N; i++ ) {
    	if (GLOBAL_INS.columnName)
    		free(GLOBAL_INS.columnName[i]);
    	free(GLOBAL_INS.values[i]);
    }

    free(GLOBAL_INS.columnName);
    GLOBAL_INS.columnName = (char **)malloc(sizeof(char **));
    GLOBAL_INS.columnName = NULL;

    free(GLOBAL_INS.values);
    GLOBAL_INS.values = (char **)malloc(sizeof(char **));
    val_count = col_count = GLOBAL_INS.N = 0;
    noerror = 1;
}

int interface() {
	clearGlobalIns();

	printf("database> ");

	yyparse();

	if (noerror) {
		if (GLOBAL_INS.N > 0) {
			printf("Comando reconhecido, chamando função...\n");
			insert(&GLOBAL_INS);
		}
	} else {
		printf("Erro sintático, verifique.\n");
	}

	clearGlobalIns();
	return 0;
}

%}

%union {
	int intval;
	double floatval;
	int subtok;
	char *strval;
}

%%

%token INSERT INTO STRING NUMBER VALUES VALUE;

line: insert into tabela values ';' {if (col_count == val_count || GLOBAL_INS.columnName == NULL) GLOBAL_INS.N = val_count; else {printf("The column counter doesn't match the value counter.\n");noerror=0;};}
	|';' '\n' {return 0;}
	| STRING ';' line {return 0;}
	| STRING '\n' line {return 0;}
	|;
insert: INSERT;

into: INTO;

tabela: STRING {setTable(yytext);} opt_column_list;

opt_column_list: /*optional*/ | '(' column_list ')';

column_list: column | column ',' column_list;

column: STRING {setColumn(yytext);};

values: VALUES '(' value_list ')';

value_list: value | value ',' value_list;

value: VALUE {setValue(yylval.strval);} | STRING {setValue(yylval.strval);};

%%