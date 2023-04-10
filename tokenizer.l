%{
#include "y.tab.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
%}

alpha [a-zA-Z]
alphanum [a-zA-Z0-9]
digit [0-9]
nonzero [1-9]

%x str
%x comment

%%
 //Keywords
"int" {return K_INT;} 
"float" {return K_FLOAT;}
"char" {return K_CHAR;} 
"for" {return FOR;} 
"while" {return WHILE;} 
"else" {return ELSE;} 
"if" {return IF;} 
"switch" {return SWITCH;} 
"case" {return CASE;} 
"return" {return RETURN;}

 /* Symbols */
"-" {return MINUS;}
"+" {return PLUS;}
"*" {return STAR;}
"/" {return SLASH;}
"%" {return MOD;}

";" {return SEMICOLON;}
"," {return COMMA;}
":" {return COLON;}

"(" {return LEFT_PAREN;}
")" {return RIGHT_PAREN;}
"{" {return LEFT_BRACE;}
"}" {return RIGHT_BRACE;}
"[" {return LEFT_BRACKET;}
"]" {return RIGHT_BRACKET;}

"==" {return EQ;}
">" {return GT;}
"<" {return LT;}
">=" {return GE;}
"<=" {return LE;}
"!=" {return NE;}

"&&" {return AND;}
"||" {return OR;}
"!" {return NOT;}

"++" {return INC;}
"--" {return DEC;}

"=" {return ASSIGN;}
"+=" {return PLUS_ASSIGN;}
"-=" {return MINUS_ASSIGN;}
"*=" {return STAR_ASSIGN;}
"/=" {return SLASH_ASSIGN;}
"%=" {return MOD_ASSIGN;}


  /* Identifiers */
(_|{alpha})((_|{alphanum}))* {return IDENTIFIER;}

  /* Integers */
"0" {return INTEGER;}
{nonzero}({digit})* {return INTEGER;}

  /* Floats */
{nonzero}({digit})*"."({digit})* {return FLOAT;}

  /* Characters */
"\'"({alpha}|{digit})"\'" {return CHARACTER;}

  /* Comments*/
"//"[^\n]*\n ;

"/*" BEGIN(comment);
<comment>"*/" {BEGIN(INITIAL);}
<comment>. ;


  /* Strings*/
\" {BEGIN(str);}
<str>\" {BEGIN(INITIAL); return STRING;}
<str>\n {printf("Unterminated string.\n"); return ERROR;}
<str>[^\n] ; //add to yylval

  /* Whitespace */
[ \t\r\n] ;

<<EOF>> return EOF_TOKEN;
  /* Error */
. {printf("Error: Invalid character %s\n", yytext); return ERROR;}

%%
int main(int argc, char *argv[])
{
    if(argc != 2){
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    yyin = fopen(argv[1], "r");

    int token;
    while((token=yylex()) != EOF_TOKEN){
        printf("%d: %s\n", token, yytext);
    }
    return 0;
}
int yywrap(){
  exit(1);
  return 0;
}