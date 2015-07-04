#include "buffend.h"

char createDatabase(char *db_name) {
	FILE *DB;
	int i, len;
	char vec_name 				[QTD_DB][LEN_DB_NAME],
		 vec_directory 			[QTD_DB][LEN_DB_NAME],
		 create 				[LEN_DB_NAME+6] = "mkdir ";

    if((DB = fopen("DB.dat","a+b")) == NULL) {
       	return ERRO_ABRIR_ARQUIVO;
    }

    for(i=0; fgetc (DB) != EOF; i++) {
    	fseek(DB, -1, 1);

        fread(vec_name[i]  		,sizeof(char), LEN_DB_NAME, DB);
        fread(vec_directory[i] 	,sizeof(char), LEN_DB_NAME, DB);

        if(strcmp(vec_name[i], db_name) == 0) {
        	fclose(DB);
        	return DB_EXISTS;
        }
    }

    data_base *SGBD;

	SGBD = (data_base*)malloc(sizeof(data_base));
	len = strlen(db_name);

	strcpy(SGBD->db_name		, db_name);
	strcpy(SGBD->db_directory	, db_name);
	strcat(SGBD->db_directory	, "/");
	SGBD->db_name[len] 			= '\0';
	SGBD->db_directory[len+1] 	= '\0';
	fwrite(SGBD ,sizeof(data_base), 1, DB);

	strcat(create, db_name);

	system(create);

    fclose(DB);

    return SUCCESS;
}