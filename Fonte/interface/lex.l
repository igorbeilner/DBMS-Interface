%{
#include <stdio.h>
#include "y.tab.h"
%}

%%

insert							return INSERT;
INSERT							return INSERT;
into							return INTO;
INTO							return INTO;
values							return VALUES;
VALUES							return VALUES;

[,]								return *yytext;
[;]								return *yytext;
[(]								return *yytext;
[)]								return *yytext;

[a-zA-Z]+[0-9]*					{yylval.strval = yytext; return STRING;};
([0-9][0-9]*\.?[0-9]*)?			{yylval.strval = yytext; return VALUE;};

\n								return 0;
[ \t]+							/* ignore whitespace */;
%%