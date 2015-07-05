/* FUNÇÕES AUXILIARES DO INTERPRETADOR DE COMANDOS (yacc + lex)
 * O yacc vai chamando essas funções conforme vai identificando os tokens.
 * Essas funcções irão preencher uma estrutura, ou parte dela, e chamarão
 * as funções do banco de dados para executar as operações.
 */
#define OP_INSERT 			1
#define OP_CREATE_TABLE 	2
#define OP_DROP_TABLE 		3
#define OP_CREATE_DATABASE 	4
#define OP_DROP_DATABASE 	5
#define OP_SELECT_ALL 		6

/* Estrutura global que guarda as informações obtidas pelo yacc
 * na identificação dos tokens
 */
rc_insert GLOBAL_DATA;

/* Estrutura auxiliar do reconhecedor.
 */
rc_parser GLOBAL_PARSER;

int noerror, // Indica se houve algum erro de sintaxe
	col_count, // Número de colunas do insert ou create table
	val_count; // Número de valores do insert.

/* Funcções do yacc
 */
int yyparse(rc_parser *parser);
int yylex(rc_parser *parser);
int yylex_destroy();

/* Imprime o erro caso o comando seja inválido
 */
void invalidCommand(char *command);

/* Estabelece a conexão com uma base de dados. Se conectar,
 * define os parâmetros globais para a exibição do console.
 */
void connect(char *nome);


/* Define o nome do banco de dados ou da tabela identificado
 * no token
 */
void setObjName(char **nome);

/* Adiciona na estrutura uma nova coluna identificada no
 * comando INSERT.
 */
void setColumnInsert(char **nome);

/* Define o valor que será inserido, identificado no token
 * do comando INSERT
 */
void setValueInsert(char *nome, char type);

/* Adiciona na estrutura uma nova coluna identificada no
 * comando CREATE TABLE, isso inicializará outras variáveis
 * também (type, attribute, ...)
 */
void setColumnCreate(char **nome);

/* Define o tipo da coluna identificada no comando CREATE
 * TABLE.
 */
void setColumnTypeCreate(char type);

/* Define o tamanho da coluna identificada no comando
 * CREATE TABLE
 */
void setColumnSizeCreate(char *size);

/* Define a coluna identificada no comando CREATE TABLE
 * como PRIMARY KEY
 */
void setColumnPKCreate();

/* Define a tabela que a coluna identificada no CREATE TABLE
 * irá referenciar
 */
void setColumnFKTableCreate(char **nome);

/* Define a coluna da tabela que a coluna identificada
 * no CREATE TABLE irá referenciar.
 */
void setColumnFKColumnCreate(char **nome);

/* Reinicializa todas as propriedades da estrutura que armazena
 * os dados identificados pelos tokens SQL.
 */
void clearGlobalStructs();

/* Define a operação que será realizada pelo identificador através
 * dos tokens iniciais.
 */
void setMode(char mode);