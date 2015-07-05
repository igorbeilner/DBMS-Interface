#include <stdlib.h>
#include <pthread.h>
#include "../buffend.h"
#include "parser.h"

void connect(char *nome) {
    int r;
    r = connectDB(nome);
	if (r == SUCCESS) {
        connected.db_name = malloc(sizeof(char)*((strlen(nome)+1)));

        strcpylower(connected.db_name, nome);

        connected.conn_active = 1;
        printf("You are now connected to database \"%s\".\n", nome);
    } else {
    	printf("error: Failed to establish connection with database named \"%s\". (Error code: %d)\n", nome, r);
    }
}

void setObjName(char **nome) {
    if (GLOBAL_PARSER.mode != 0) {
        GLOBAL_DATA.objName = malloc(sizeof(char)*((strlen(*nome)+1)));

        strcpylower(GLOBAL_DATA.objName, *nome);
        GLOBAL_DATA.objName[strlen(*nome)] = '\0';
    } else
        return;
}

void setColumnInsert(char **nome) {
    GLOBAL_DATA.columnName = realloc(GLOBAL_DATA.columnName, (col_count+1)*sizeof(char *));

    GLOBAL_DATA.columnName[col_count] = malloc(sizeof(char)*(strlen(*nome)+1));
    strcpylower(GLOBAL_DATA.columnName[col_count], *nome);
    GLOBAL_DATA.columnName[col_count][strlen(*nome)] = '\0';

    col_count++;
}

void setValueInsert(char *nome, char type) {
    int i;
    GLOBAL_DATA.values  = realloc(GLOBAL_DATA.values, (val_count+1)*sizeof(char *));
    GLOBAL_DATA.type    = realloc(GLOBAL_DATA.type, (val_count+1)*sizeof(char));

    // Adiciona o valor no vetor de strings
    GLOBAL_DATA.values[val_count] = malloc(sizeof(char)*(strlen(nome)+1));
    if (type == 'I' || type == 'D') {
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

void setColumnCreate(char **nome) {
    GLOBAL_DATA.columnName  = realloc(GLOBAL_DATA.columnName, (col_count+1)*sizeof(char *));
    GLOBAL_DATA.attribute   = realloc(GLOBAL_DATA.attribute, (col_count+1)*sizeof(int));
    GLOBAL_DATA.fkColumn    = realloc(GLOBAL_DATA.fkColumn, (col_count+1)*sizeof(char *));
    GLOBAL_DATA.fkTable     = realloc(GLOBAL_DATA.fkTable, (col_count+1)*sizeof(char *));
    GLOBAL_DATA.values      = realloc(GLOBAL_DATA.values, (col_count+1)*sizeof(char *));
    GLOBAL_DATA.type        = realloc(GLOBAL_DATA.type, (col_count+1)*sizeof(char *));

    GLOBAL_DATA.values[col_count] = malloc(sizeof(char));
    GLOBAL_DATA.values[col_count] = 0;

    GLOBAL_DATA.fkTable[col_count] = malloc(sizeof(char));
    GLOBAL_DATA.fkTable[col_count] = 0;

    GLOBAL_DATA.fkColumn[col_count] = malloc(sizeof(char));
    GLOBAL_DATA.fkColumn[col_count] = 0;

    GLOBAL_DATA.columnName[col_count] = malloc(sizeof(char)*(strlen(*nome)+1));
    strcpylower(GLOBAL_DATA.columnName[col_count], *nome);
    GLOBAL_DATA.columnName[col_count][strlen(*nome)] = '\0';
    GLOBAL_DATA.type[col_count] = 0;
    GLOBAL_DATA.attribute[col_count] = NPK;

    col_count++;
}

void setColumnTypeCreate(char type) {
    GLOBAL_DATA.type[col_count-1] = type;
    //if (type == 'C') GLOBAL_DATA.values[col_count-1] = (int)sizeof(char);
    //else if (type == 'D') GLOBAL_DATA.values[col_count-1] = (int)sizeof(double);
    //else if (type == 'I') GLOBAL_DATA.values[col_count-1] = (int)sizeof(int);
}

void setColumnSizeCreate(char *size) {
    GLOBAL_DATA.values[col_count-1] = realloc(GLOBAL_DATA.values[col_count-1], sizeof(char)*(strlen(size)+1));
    strcpy(GLOBAL_DATA.values[col_count-1], size);
    GLOBAL_DATA.values[col_count-1][strlen(size)-1] = '\0';
}

void setColumnPKCreate() {
    GLOBAL_DATA.attribute[col_count-1] = PK;
}

void setColumnFKTableCreate(char **nome) {
    GLOBAL_DATA.fkTable[col_count-1] = realloc(GLOBAL_DATA.fkTable[col_count-1], sizeof(char)*(strlen(*nome)+1));
    strcpylower(GLOBAL_DATA.fkTable[col_count-1], *nome);
    GLOBAL_DATA.fkTable[col_count-1][strlen(*nome)] = '\0';
    GLOBAL_DATA.attribute[col_count-1] = FK;
}

void setColumnFKColumnCreate(char **nome) {
    GLOBAL_DATA.fkColumn[col_count-1] = realloc(GLOBAL_DATA.fkColumn[col_count-1], sizeof(char)*(strlen(*nome)+1));
    strcpylower(GLOBAL_DATA.fkColumn[col_count-1], *nome);
    GLOBAL_DATA.fkColumn[col_count-1][strlen(*nome)] = '\0';
}


void clearGlobalStructs() {
    int i;

    if (GLOBAL_DATA.objName)
        free(GLOBAL_DATA.objName);
    GLOBAL_DATA.objName = (char *)malloc(sizeof(char *));

    for (i = 0; i < GLOBAL_DATA.N; i++ ) {
        if (GLOBAL_DATA.columnName)
            free(GLOBAL_DATA.columnName[i]);
        if (GLOBAL_DATA.values)
            free(GLOBAL_DATA.values[i]);
        if (GLOBAL_DATA.fkTable)
            free(GLOBAL_DATA.fkTable[i]);
        if (GLOBAL_DATA.fkColumn)
            free(GLOBAL_DATA.fkColumn[i]);
    }

    free(GLOBAL_DATA.columnName);
    GLOBAL_DATA.columnName = (char **)malloc(sizeof(char **));
    GLOBAL_DATA.columnName = NULL;

    free(GLOBAL_DATA.values);
    GLOBAL_DATA.values = (char **)malloc(sizeof(char **));
    GLOBAL_DATA.values = NULL;

    free(GLOBAL_DATA.fkTable);
    GLOBAL_DATA.fkTable = (char **)malloc(sizeof(char **));
    GLOBAL_DATA.fkTable = NULL;

    free(GLOBAL_DATA.fkColumn);
    GLOBAL_DATA.fkColumn = (char **)malloc(sizeof(char **));
    GLOBAL_DATA.fkColumn = NULL;

    free(GLOBAL_DATA.type);
    GLOBAL_DATA.type = (char *)malloc(sizeof(char));

    free(GLOBAL_DATA.attribute);
    GLOBAL_DATA.attribute = (int *)malloc(sizeof(int));

    yylex_destroy();
    noerror = 1;

    val_count = col_count = GLOBAL_DATA.N = 0;

    GLOBAL_PARSER.mode              = 0;
    GLOBAL_PARSER.parentesis        = 0;
}

void setMode(char mode) {
    GLOBAL_PARSER.mode = mode;
}


int interface() {
    pthread_t pth;

    pthread_create(&pth, NULL, (void*)clearGlobalStructs, NULL);
    pthread_join(pth, NULL);

    connect("ibetres"); // conecta automaticamente no banco padrão

    while(1){
        if (!connected.conn_active) {
            printf(">");
        } else {
            printf("%s=# ", connected.db_name);
        }

        pthread_create(&pth, NULL, (void*)yyparse, &GLOBAL_PARSER);
        pthread_join(pth, NULL);

        if (noerror) {
            if (GLOBAL_PARSER.mode != 0) {
                if (!connected.conn_active) {
                    printf("Você não está conectado. Utilize \\c <nome_banco> para conectar.\n");
                } else {
                    switch(GLOBAL_PARSER.mode) {
                        case OP_INSERT:
                            if (GLOBAL_DATA.N > 0) {
                                insert(&GLOBAL_DATA);
                            }
                            else
                                printf("warning: Nada para ser inserido, comando ignorado.\n");
                            break;
                        case OP_SELECT_ALL:
                            imprime(GLOBAL_DATA.objName);
                            break;
                        case OP_CREATE_TABLE:
                            createTable(&GLOBAL_DATA);
                            break;
                        case OP_CREATE_DATABASE:
                            createDB(GLOBAL_DATA.objName);
                            break;
                        case OP_DROP_TABLE:
                            excluirTabela(GLOBAL_DATA.objName);
                            break;
                        case OP_DROP_DATABASE:
                            dropDatabase(GLOBAL_DATA.objName);
                            break;
                        default: break;
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