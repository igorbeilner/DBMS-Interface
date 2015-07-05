#include <stdlib.h>
#include <stdio.h>

extern FILE * yyin;
extern FILE* outFile_p;
rc_insert GLOBAL_DATA;
rc_parser GLOBAL_PARSER;

int noerror, col_count, val_count;

int yyparse(rc_parser *parser);
int yylex(rc_parser *parser);
int yylex_destroy();


void connect(char *nome);

void setTable(char **nome);

void setColumnInsert(char **nome);

void setColumnCreate(char **nome);

void setColumnTypeCreate(char type);

void setColumnSizeCreate(char *size);

void setColumnPKCreate();

void setColumnFKTableCreate(char **nome);

void setColumnFKColumnCreate(char **nome);

void setValueInsert(char *nome, char type);

void clearGlobalStructs();

void setMode(char mode);