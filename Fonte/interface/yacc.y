%{
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "../buffend.h"

extern int  yylineno;
extern char* yytext[];
extern FILE * yyin;
extern FILE* outFile_p;
int noerror, col_count, val_count;
int yyparse();
int yylex();
int yylex_destroy();

rc_insert GLOBAL_INS;
rc_select GLOBAL_SEL;
rc_parser GLOBAL_PARSER;

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
	char **dest;

	if (GLOBAL_PARSER.mode == 'I') {
		dest = &GLOBAL_PARSER.insert->tableName;
	} else if (GLOBAL_PARSER.mode == 'S') {
		dest = &GLOBAL_PARSER.select->tableName;
	}

	*dest = malloc(sizeof(char)*(strlen(*nome)+1));

	strcpy(*dest, *nome);
	*dest[strlen(*nome)] = '\0';
}

void setColumn(char **nome) {
	GLOBAL_INS.columnName = realloc(GLOBAL_INS.columnName, (col_count+1)*sizeof(char *));

	GLOBAL_INS.columnName[col_count] = malloc(sizeof(char)*(strlen(*nome)+1));
	strcpy(GLOBAL_INS.columnName[col_count], *nome);
	GLOBAL_INS.columnName[col_count][strlen(*nome)] = '\0';

	col_count++;
}

void setValue(char *nome, char type) {
	int i;
	GLOBAL_INS.values = realloc(GLOBAL_INS.values, (val_count+1)*sizeof(char *));
	GLOBAL_INS.type = realloc(GLOBAL_INS.type, (val_count+1)*sizeof(char));

	// Adiciona o valor no vetor de strings
	GLOBAL_INS.values[val_count] = malloc(sizeof(char)*(strlen(nome)+1));
	if (type == 'I') {
		strcpy(GLOBAL_INS.values[val_count], nome);
		GLOBAL_INS.values[val_count][strlen(nome)] = '\0';
	} else if (type == 'S') {
		for (i = 1; i < strlen(nome)-1; i++) {
			GLOBAL_INS.values[val_count][i-1] = nome[i];
		}
		GLOBAL_INS.values[val_count][strlen(nome)-2] = '\0';
	}

	GLOBAL_INS.type[val_count] = type;

	val_count++;
}

void clearGlobalStructs() {
	int i;

	if (GLOBAL_INS.tableName)
		free(GLOBAL_INS.tableName);
	GLOBAL_INS.tableName = (char *)malloc(sizeof(char *));

	if (GLOBAL_SEL.tableName)
		free(GLOBAL_SEL.tableName);
	GLOBAL_SEL.tableName = (char *)malloc(sizeof(char *));

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

	free(GLOBAL_INS.type);
	GLOBAL_INS.type = (char *)malloc(sizeof(char));
	val_count = col_count = GLOBAL_INS.N = 0;
	yylex_destroy();
	noerror = 1;

	GLOBAL_PARSER.insert 		= &GLOBAL_INS;
	GLOBAL_PARSER.select 		= &GLOBAL_SEL;
	GLOBAL_PARSER.mode			= 0;
	GLOBAL_PARSER.wait_semicolon= 0;
}

int interface() {
	pthread_t pth;

	pthread_create(&pth, NULL, (void*)clearGlobalStructs, NULL);
	pthread_join(pth, NULL);

	GLOBAL_PARSER.conn_active = 0;

	while(1){
		if (!GLOBAL_PARSER.conn_active) {
			printf(">");
		} else {
			printf("database=# ");
		}

		pthread_create(&pth, NULL, (void*)yyparse, NULL);
		pthread_join(pth, NULL);

		if (noerror) {
			if (GLOBAL_PARSER.mode != 0) {
				if (!GLOBAL_PARSER.conn_active) {
					printf("Você não está conectado. Utilize CONNECT para conectar.\n");
				} else {
					if (GLOBAL_PARSER.mode == 'I') {
						if (GLOBAL_PARSER.insert->N > 0)
							insert(&GLOBAL_INS);
					} else if (GLOBAL_PARSER.mode == 'S') {
						imprime(GLOBAL_SEL.tableName);
					}
				}
			}
		} else {
			printf("Erro sintático, verifique.\n");
		}

		pthread_create(&pth, NULL, (void*)clearGlobalStructs, NULL);
		pthread_join(pth, NULL);
	}
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

%token  INSERT		INTO		VALUES		SELECT		FROM
		STRING		NUMBER		VALUE		QUIT		LIST_TABLES
		LIST_TABLE 	ALPHANUM 	CONNECT;

start: insert | select | table_attr | list_tables | connection | exit_program | /*nothing*/;

/* CONNECTION */
connection: CONNECT {GLOBAL_PARSER.conn_active = 1; return 0;};

/* EXIT */
exit_program: QUIT {exit(0);};

/*--------------------------------------------------*/
/****************** SQL STATEMENTS ******************/
/*--------------------------------------------------*/

/* INSERT */
insert: INSERT INTO {GLOBAL_PARSER.mode = 'I';} table opt_column_list VALUES '(' value_list ')' ';' {
	if (col_count == val_count || GLOBAL_INS.columnName == NULL)
		GLOBAL_INS.N = val_count;
	else {
		printf("The column counter doesn't match the value counter.\n");
		noerror=0;
	}
};

table: STRING {setTable(yytext);};

opt_column_list: /*optional*/ | '(' column_list ')';

column_list: column | column ',' column_list;

column: STRING {setColumn(yytext);};

value_list: value | value ',' value_list;

value: VALUE {setValue(yylval.strval, 'I');}
	 | ALPHANUM {setValue(yylval.strval, 'S');};


/* SELECT */
select: SELECT {GLOBAL_PARSER.mode = 'S';} '*' FROM table_select ';';

table_select: STRING {setTable(yytext);};

/*--------------------------------------------------*/
/**************** GENERAL FUNCTIONS *****************/
/*--------------------------------------------------*/
/* TABLE ATTRIBUTES */
table_attr: LIST_TABLE STRING {
	if(GLOBAL_PARSER.conn_active)
		printTable(yylval.strval);
	else
		printf("Você não está conectado\n");
	return 0;
};

/* LIST TABLES */
list_tables: LIST_TABLES {
	if(GLOBAL_PARSER.conn_active)
		printTable(NULL);
	else
		printf("Você não está conectado\n");
	return 0;
};

%%
