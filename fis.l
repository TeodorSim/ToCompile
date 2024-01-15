%{
#include <cstdio>
#include "y.tab.h" // generat de yacc - defineste lista de token-uri folosite
%}

space [ \t ]

%option noyywrap
%%
"typeof" {return TYPEOF;}
"eval" {return EVAL;}
"typ_void" {yylval.dataTyp=strdup(yytext); return VOID;}
"int" {yylval.dataTyp=strdup(yytext); return INT;}
"float" {yylval.dataTyp=strdup(yytext); return FLOAT;}
"char" {yylval.dataTyp=strdup(yytext); return CHAR;}
"string" {yylval.dataTyp=strdup(yytext); return STRING;}
"bool" {yylval.dataTyp=strdup(yytext); return BOOL;}

"constant" {return CONSTANT;}

"structure" {return STRUCTURE;}

"classOf" {return CLASSOF;} 

"private" {return PRIVATE;}
"protected" {return PROTECTED;}
"public" {return PUBLIC;} 

"if" {return IF;}

"else" {return ELSE;}

"while" {return WHILE;}
	
"for" {return FOR;}

"do" {return DO;}

"true" | "false" {yylval.boolTyp = strdup(yytext); return BOOL;}

"print" {return PRINT;}

"begin_program" {return BGIN;}

"end_program"   {return END;}

"return" {return RETURN;}

"<-" {return ASSIGN;}

"<" {return LESS;}
"<=" {return LESSEQ;}
">" {return GRT;}
">=" {return GRTEQ;}
"==" {return EQ;}
"!" {return NOT;}

"&&" {return AND;}
"||" {return OR;}

"::" {return DOUA_DOUA_PCTE;}

"{" {return OPEN_PRTHS;}

"}" {return CLOSE_PRTHS;}

"[" {return OPEN_SQR_PRTHS;}

"]" {return CLOSE_SQR_PRTHS;}

[-+]?0|[-+]?([1-9][0-9]*) {yylval.intTyp = atoi(yytext); return INT_NUM;}

[-+]?0|[-+]?([1-9][0-9]*)"."[0-9]* {yylval.floatTyp = atof(yytext); return REAL_NUM;} 

'[a-zA-Z0-9]'  {yylval.charTyp = strdup(yytext); return CHAR_VAL;} 

\"[^"]*\" {yylval.stringTyp = strdup(yytext); return STRING_VAL;}

[a-zA-Z][_a-zA-Z0-9]*(\.[a-zA-Z][_a-zA-Z0-9]*)* {yylval.dataTyp = strdup(yytext); return IDENTIF;}

[a-zA-Z][_a-zA-Z0-9]*(\[[0-9a-z]+\])+ {yylval.arrayTyp = strdup(yytext); return ARRAY_IDENTIF;}

true {yylval.stringTyp = strdup(yytext); return BOOL_VAL;}
false {yylval.stringTyp = strdup(yytext); return BOOL_VAL;}


 {space} ;

\n {yylineno++;} 
. {return yytext[0];}
%%