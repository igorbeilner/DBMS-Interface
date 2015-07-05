#include "buffend.h"

char connectDB(char *db_name) {
	FILE *DB;
	int i;
	char vec_name 				[QTD_DB][LEN_DB_NAME],
		 vec_directory 			[QTD_DB][LEN_DB_NAME],
		 valid;

    if((DB = fopen("DB.dat","rb")) == NULL) {
       	return ERRO_ABRIR_ARQUIVO;
    }

    for(i=0; fgetc (DB) != EOF; i++) {
    	fseek(DB, -1, 1);

    	fread(&valid			,sizeof(char), 			 1, DB);
        fread(vec_name[i]  		,sizeof(char), LEN_DB_NAME, DB);
        fread(vec_directory[i] 	,sizeof(char), LEN_DB_NAME, DB);

        if(objcmp(vec_name[i], db_name) == 0) {
        	if(valid) {
	        	strcpylower(connected.db_directory, vec_directory[i]);
	        	fclose(DB);
	        	return SUCCESS;
	        }
        }
    }
    fclose(DB);

    return DB_NOT_EXISTS;

}

void createDB(char *db_name) {
	FILE *DB;
	int i, len;
	char vec_name 				[QTD_DB][LEN_DB_NAME],
		 vec_directory 			[QTD_DB][LEN_DB_NAME],
		 create 				[LEN_DB_NAME+6] = "mkdir ",
         *aux_name_tolower,
         valid;

    if((DB = fopen("DB.dat","a+b")) == NULL) {
       	printf("error opening the file\n");
    }

    for(i=0; fgetc (DB) != EOF; i++) {
    	fseek(DB, -1, 1);

    	fread(&valid			,sizeof(char), 			 1, DB);
        fread(vec_name[i]  		,sizeof(char), LEN_DB_NAME, DB);
        fread(vec_directory[i] 	,sizeof(char), LEN_DB_NAME, DB);

        if(objcmp(vec_name[i], db_name) == 0) {
        	if(valid) {
	        	fclose(DB);
				if(objcmp(db_name, "ibetres") != 0)
	        		printf("database already exists\n");
	            return;
	        }
        }
    }

    data_base *SGBD;

	SGBD = (data_base*)malloc(sizeof(data_base));
	len = strlen(db_name);
	memset(SGBD->db_name 		, 0, LEN_DB_NAME);
	memset(SGBD->db_directory 	, 0, LEN_DB_NAME);


	SGBD->valid = 1;
	strcpylower(SGBD->db_name		, db_name);
	strcpylower(SGBD->db_directory	, db_name);
	strcat(SGBD->db_directory	, "/");
	SGBD->db_name[len] 			= '\0';
	SGBD->db_directory[len+1] 	= '\0';
	fwrite(SGBD ,sizeof(data_base), 1, DB);

    aux_name_tolower = (char *)malloc(sizeof(char) * (strlen(db_name)+1));
    strcpylower(aux_name_tolower, db_name);
    strcat(create, aux_name_tolower);

	system(create);

    fclose(DB);
	if(objcmp(db_name, "ibetres") != 0)
    	printf("CREATE DATABASE\n");
}

void dropDatabase(char *db_name) {

	FILE *DB;
	int i;
	char vec_name 				[QTD_DB][LEN_DB_NAME],
		 vec_directory 			[QTD_DB][LEN_DB_NAME],
		 valid;

	if(strcmp(db_name, connected.db_name) == 0) {
		printf("not permitted exclusion\n");
		return;
	}

    if((DB = fopen("DB.dat","r+b")) == NULL) {
       	printf("error opening the file\n");
    }

    for(i=0; fgetc (DB) != EOF; i++) {
    	fseek(DB, -1, 1);

    	fread(&valid			,sizeof(char), 			 1, DB);
        fread(vec_name[i]  		,sizeof(char), LEN_DB_NAME, DB);
        fread(vec_directory[i] 	,sizeof(char), LEN_DB_NAME, DB);

        if(objcmp(vec_name[i], db_name) == 0) {
        	if(valid) {
	        	valid = 0;
	        	fseek(DB, ((LEN_DB_NAME*2+1)*i), SEEK_SET);
	        	fwrite(&valid ,sizeof(char), 1, DB);

	        	char directory[LEN_DB_NAME*2] = "rm ";
	        	strcat(directory, vec_directory[i]);
	        	strcat(directory, " -R\0");

	        	system(directory);

	        	fclose(DB);
	        	printf("DROP DATABASE\n");
	        	return;
	        }
        }
    }
    fclose(DB);

    printf("database does not exist\n");

}
