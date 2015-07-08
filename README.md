#BANCO DE DADOS II
Implementação de interface com as funcionalidades a seguir:
##Comandos com sintaxe padrão do SQL:
 	CREATE DATABASE <dbName>;
 	CREATE TABLE <tblName>(
 		<attr1> integer [primary key],
 		<attr2> varchar(<size>),
 		<attr3> char,
 		<attr4> double,
 		<attr5> integer [references table(attrPK)]
 		[, ...]
 	);
 	INSERT INTO <tblName> values (123, 'string', 'c', 1.23, 123 [, ...]);
  	INSERT INTO <tblName> (<attr1>, <attr2>, <attr3>, <attr4>, <attr5> [, ...])
 		VALUES (321, 'string', 'c', 1.23, 123 [, ...]);```
 	DROP DATABASE <dbName>;
 	DROP TABLE <tblName>;
 	SELECT * FROM <tblName>;
##Comandos do Shell do SGBD:
 	help				// retorna um menu de ajuda
	\c <NomeBanco> 		// estabelece conexão com o banco de dados <NomeBanco>
	\l 					// retorna uma lista com os bancos de dados criados no SGBD
	\d 					// retorna uma lista com as tabelas existentes no banco de dados corrente
	\t <NomeTabela>		// retorna uma lista com o esquema de uma tabela
	\q 					// sai do shell do SGBD


**Alunos:** Eliton Traverssini, Igor Beilner e Régis T. Feyh.<br>
**Curso:** Ciência da Computação - UFFS - Chapecó - 2015/1<br>
**Disciplina:** Banco de Dados II<br>
**Professor:** Denio Duarte<br>
