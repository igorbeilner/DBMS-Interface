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
(?i:SELECT)						return SELECT;
(?i:FROM)						return FROM;
(?i:CREATE)						return CREATE;
(?i:TABLE)						return TABLE;
(?i:INTEGER)					return INTEGER;
(?i:INT)						return INTEGER;
(?i:VARCHAR)					return VARCHAR;
(?i:DOUBLE)						return DOUBLE;
(?i:PRIMARY)					return PRIMARY;
(?i:KEY)						return KEY;
(?i:FOREIGN)					return FOREIGN;
(?i:REFERENCES)					return REFERENCES;

[,]								return *yytext;
[;]								return *yytext;
[*]								return *yytext;
[(]								return *yytext;
[)]								return *yytext;

[a-zA-Z]+[0-9]*					{yylval.strval = yytext; return STRING;};
[\']([^'])+[\']			  		{yylval.strval = yytext; return ALPHANUM;};
[0-9]*\.[0-9]*					{yylval.strval = yytext; return VALUE;};
[0-9]+							{yylval.strval = yytext; return NUMBER;}

\n								{
									if (parser->mode != 0)
										printf("%s-# ", parser->db_name);
								 	else if (parser->conn_active)
								 		printf("%s=# ", parser->db_name);
								 	else
								 		printf(">");
								};

[\\][c]+						return CONNECT;
[\\][q]+						return QUIT;
[\\][d]+						return LIST_TABLES;
[\\][d]+[t]+					return LIST_TABLE;
[ \t]+							/* ignore whitespace */;
%%