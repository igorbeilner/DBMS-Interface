%{
#include <stdio.h>
#include "y.tab.h"
%}

%%

(?i:INSERT)						return INSERT;
(?i:INTO)						return INTO;
(?i:VALUES)						return VALUES;
(?i:CONNECT)					return CONNECT;
(?i:SELECT)						return SELECT;
(?i:FROM)						return FROM;

[,]								return *yytext;
[;]								return *yytext;
[*]								return *yytext;
[(]								return *yytext;
[)]								return *yytext;

[a-zA-Z]+[0-9]*					{yylval.strval = yytext; return STRING;};
[\']([^'])+[\']			  		{yylval.strval = yytext; return ALPHANUM;};
[0-9]*\.?[0-9]*					{yylval.strval = yytext; return VALUE;};

\n								return 0;
[\\][q]+						return QUIT;
[\\][d]+						return LIST_TABLES;
[\\][d]+[t]+					return LIST_TABLE;
[ \t]+							/* ignore whitespace */;
%%