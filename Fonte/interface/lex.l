%{
#include <stdio.h>
#include "../buffend.h"
#include "y.tab.h"
#define YY_DECL int yylex(rc_parser *parser)
%}

%%

(?i:INSERT)						return INSERT;
(?i:INTO)						return INTO;
(?i:VALUES)						return VALUES;
(?i:CONNECT)					return CONNECT;
(?i:SELECT)						return SELECT;
(?i:FROM)						return FROM;
(?i:CREATE)						return CREATE;
(?i:TABLE)						return TABLE;
(?i:INT)						return INT;
(?i:TEXT)						return TEXT;
(?i:DOUBLE)						return DOUBLE;
(?i:PRIMARY)					return PRIMARY;
(?i:KEY)						return KEY;

[,]								return *yytext;
[;]								return *yytext;
[*]								return *yytext;
[(]								return *yytext;
[)]								return *yytext;

[a-zA-Z]+[0-9]*					{yylval.strval = yytext; return STRING;};
[\']([^'])+[\']			  		{yylval.strval = yytext; return ALPHANUM;};
[0-9]*\.?[0-9]*					{yylval.strval = yytext; return VALUE;};

\n								{
									if (parser->mode != 0)
										printf("%s-# ", parser->db_name);
								 	else if (parser->conn_active)
								 		printf("%s=# ", parser->db_name);
								 	else
								 		printf(">");
								};
[\\][q]+						return QUIT;
[\\][d]+						return LIST_TABLES;
[\\][d]+[t]+					return LIST_TABLE;
[ \t]+							/* ignore whitespace */;
%%