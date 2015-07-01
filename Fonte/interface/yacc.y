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
int yyparse(rc_parser *parser);
int yylex(rc_parser *parser);
int yylex_destroy();

rc_insert GLOBAL_DATA;
rc_parser GLOBAL_PARSER;

void yyerror(rc_parser *GLOBAL_PARSER, char *s, ...) {
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

void connect(char **nome) {
    if (GLOBAL_PARSER.mode != 0) {
        printf("Você já está conectado!\n");
        return;
    } else {
        GLOBAL_PARSER.db_name = malloc(sizeof(char)*((strlen(*nome)+1)));

        strcpy(GLOBAL_PARSER.db_name, *nome);
        GLOBAL_PARSER.db_name[strlen(*nome)] = '\0';

        GLOBAL_PARSER.conn_active = 1;
    }
}

void setTable(char **nome) {
    if (GLOBAL_PARSER.mode != 0) {
        GLOBAL_PARSER.data->tableName = malloc(sizeof(char)*((strlen(*nome)+1)));

        strcpy(GLOBAL_PARSER.data->tableName, *nome);
        GLOBAL_PARSER.data->tableName[strlen(*nome)] = '\0';
    } else
        return;
}

void setColumn(char **nome) {
    GLOBAL_DATA.columnName = realloc(GLOBAL_DATA.columnName, (col_count+1)*sizeof(char *));

    GLOBAL_DATA.columnName[col_count] = malloc(sizeof(char)*(strlen(*nome)+1));
    strcpy(GLOBAL_DATA.columnName[col_count], *nome);
    GLOBAL_DATA.columnName[col_count][strlen(*nome)] = '\0';

    col_count++;
}

void setValue(char *nome, char type) {
    int i;
    GLOBAL_DATA.values = realloc(GLOBAL_DATA.values, (val_count+1)*sizeof(char *));
    GLOBAL_DATA.type = realloc(GLOBAL_DATA.type, (val_count+1)*sizeof(char));

    // Adiciona o valor no vetor de strings
    GLOBAL_DATA.values[val_count] = malloc(sizeof(char)*(strlen(nome)+1));
    if (type == 'I') {
        strcpy(GLOBAL_DATA.values[val_count], nome);
        GLOBAL_DATA.values[val_count][strlen(nome)] = '\0';
    } else if (type == 'S') {
        for (i = 1; i < strlen(nome)-1; i++) {
            GLOBAL_DATA.values[val_count][i-1] = nome[i];
        }
        GLOBAL_DATA.values[val_count][strlen(nome)-2] = '\0';
    }

    GLOBAL_DATA.type[val_count] = type;

    val_count++;
}

void clearGlobalStructs() {
    int i;

    if (GLOBAL_DATA.tableName)
        free(GLOBAL_DATA.tableName);
    GLOBAL_DATA.tableName = (char *)malloc(sizeof(char *));

    for (i = 0; i < GLOBAL_DATA.N; i++ ) {
        if (GLOBAL_DATA.columnName)
            free(GLOBAL_DATA.columnName[i]);
        free(GLOBAL_DATA.values[i]);
    }

    free(GLOBAL_DATA.columnName);
    GLOBAL_DATA.columnName = (char **)malloc(sizeof(char **));
    GLOBAL_DATA.columnName = NULL;

    free(GLOBAL_DATA.values);
    GLOBAL_DATA.values = (char **)malloc(sizeof(char **));

    free(GLOBAL_DATA.type);
    GLOBAL_DATA.type = (char *)malloc(sizeof(char));
    val_count = col_count = GLOBAL_DATA.N = 0;

    free(GLOBAL_DATA.attribute);
    GLOBAL_DATA.attribute = (char *)malloc(sizeof(char));

    yylex_destroy();
    noerror = 1;

    GLOBAL_PARSER.data              = &GLOBAL_DATA;
    GLOBAL_PARSER.mode              = 0;
}

void setMode(char mode) {
    GLOBAL_PARSER.mode = mode;
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
            printf("%s=# ", GLOBAL_PARSER.db_name);
        }

        pthread_create(&pth, NULL, (void*)yyparse, &GLOBAL_PARSER);
        pthread_join(pth, NULL);

        if (noerror) {
            if (GLOBAL_PARSER.mode != 0) {
                if (!GLOBAL_PARSER.conn_active) {
                    printf("Você não está conectado. Utilize \\c <nome_banco> para conectar.\n");
                } else {
                    if (GLOBAL_PARSER.mode == 'I') {
                        if (GLOBAL_PARSER.data->N > 0)
                            insert(&GLOBAL_DATA);
                    } else if (GLOBAL_PARSER.mode == 'S') {
                        imprime(GLOBAL_DATA.tableName);
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

%parse-param { rc_parser *GLOBAL_PARSER }
%lex-param { rc_parser *GLOBAL_PARSER }

%%

%token  INSERT      INTO        VALUES      SELECT      FROM
        CREATE      TABLE       INT         TEXT        DOUBLE
        PRIMARY     KEY
        STRING      NUMBER      VALUE       QUIT        LIST_TABLES
        LIST_TABLE  ALPHANUM    CONNECT;

start: insert | select | create_table | table_attr | list_tables | connection | exit_program | semicolon {return 0;} | /*nothing*/;

/* CONNECTION */
connection: CONNECT STRING {connect(yytext); return 0;};

/* EXIT */
exit_program: QUIT {exit(0);};

/*--------------------------------------------------*/
/****************** SQL STATEMENTS ******************/
/*--------------------------------------------------*/

/* INSERT */
insert: INSERT INTO {setMode('I');} table opt_column_list VALUES '(' value_list ')' semicolon {
    if (col_count == val_count || GLOBAL_DATA.columnName == NULL)
        GLOBAL_DATA.N = val_count;
    else {
        printf("The column counter doesn't match the value counter.\n");
        noerror=0;
    }
    return 0;
};

semicolon: ';';

table: STRING {setTable(yytext);};

opt_column_list: /*optional*/ | '(' column_list ')';

column_list: column | column ',' column_list;

column: STRING {setColumn(yytext);};

value_list: value | value ',' value_list;

value: VALUE {setValue(yylval.strval, 'I');}
     | ALPHANUM {setValue(yylval.strval, 'S');};


/* SELECT */
select: SELECT {setMode('S');} '*' FROM table_select semicolon {return 0;};

table_select: STRING {setTable(yytext);};

/* CREATE TABLE */
create_table: CREATE TABLE {setMode('C');} table '(' table_column_attr ')' semicolon {return 0;};

table_column_attr: column type special | column type special ',' table_column_attr;

type: INT | TEXT | DOUBLE;

special: /*optional*/ | PRIMARY KEY;

/*--------------------------------------------------*/
/**************** GENERAL FUNCTIONS *****************/
/*--------------------------------------------------*/
/* TABLE ATTRIBUTES */
table_attr: LIST_TABLE STRING {
    if(GLOBAL_PARSER->conn_active)
        printTable(yylval.strval);
    else
        printf("Você não está conectado\n");
    return 0;
};

/* LIST TABLES */
list_tables: LIST_TABLES {
    if(GLOBAL_PARSER->conn_active)
        printTable(NULL);
    else
        printf("Você não está conectado\n");
    return 0;
};

%%
