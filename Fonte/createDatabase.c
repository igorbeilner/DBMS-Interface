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

        printf("%d\n", valid);
        printf("%s\n", vec_name[i]);
        printf("%s\n", vec_directory[i]);

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
        	fclose(DB);
        	printf("database already exists\n");
            return;

        }
    }

    data_base *SGBD;

	SGBD = (data_base*)malloc(sizeof(data_base));
	len = strlen(db_name);

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

    printf("CREATE DATABASE\n");
}

void dropDatabase(char *db_name) {

	FILE *DB;
	int i;
	char vec_name 				[QTD_DB][LEN_DB_NAME],
		 vec_directory 			[QTD_DB][LEN_DB_NAME],
		 vec_name2 				[QTD_DB][LEN_DB_NAME],
		 vec_directory2 			[QTD_DB][LEN_DB_NAME],
		 valid, valid2;

    if((DB = fopen("DB.dat","rb")) == NULL) {
       	printf("error opening the file\n");
    }

    for(i=0; fgetc (DB) != EOF; i++) {
    	fseek(DB, -1, 1);

    	fread(&valid			,sizeof(char), 			 1, DB);
        fread(vec_name[i]  		,sizeof(char), LEN_DB_NAME, DB);
        fread(vec_directory[i] 	,sizeof(char), LEN_DB_NAME, DB);

        if(objcmp(vec_name[i], db_name) == 0) {
        	if(valid) {
	        	valid2 = 0;
	        	fseek(DB, ((LEN_DB_NAME*2+1)*(i+1))-1, SEEK_SET);
	        	fwrite(&valid2 ,sizeof(char), 1, DB);

	        	fseek(DB, ((LEN_DB_NAME*2+1)*(i+1))-1, SEEK_SET);

	        	fread(&valid2			,sizeof(char), 			 1, DB);
        		fread(vec_name2[i]  		,sizeof(char), LEN_DB_NAME, DB);
        		fread(vec_directory2[i] 	,sizeof(char), LEN_DB_NAME, DB);


        		printf("%d\n", valid);
        		printf("%s\n", vec_name[i]);
        		printf("%s\n", vec_directory[i]);

	        	fclose(DB);
	        	printf("DROP DATABASE\n");
	        	return;
	        }
        }
    }
    fclose(DB);

    printf("database does not exist\n");

}