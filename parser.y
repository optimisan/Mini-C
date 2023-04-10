%{
#include <stdio.h>
#include <stdlib.h>
int yyerror(char *s);
int yylex();
%}

/* Keywords */
%token K_INT K_FLOAT K_CHAR FOR WHILE ELSE IF SWITCH CASE RETURN
/* Literals */
%token INTEGER FLOAT CHARACTER STRING
/* Assignments */
%token ASSIGN PLUS_ASSIGN MINUS_ASSIGN STAR_ASSIGN SLASH_ASSIGN MOD_ASSIGN 
/* Math op */
%token PLUS MINUS STAR SLASH MOD INC DEC
/* Comparison */
%token EQ LT GT LE GE QUESTION_MARK NE
/* Logical */
%token NOT AND OR
/* Symbols */
%token COMMA SEMICOLON COLON
/* Comments */
%token SINGLE_START MULTI_START MULTI_END
/* Brackets */
%token LEFT_PAREN RIGHT_PAREN LEFT_BRACE RIGHT_BRACE LEFT_BRACKET RIGHT_BRACKET

%token IDENTIFIER ERROR

%token EOF_TOKEN

%%
program: IDENTIFIER;
%%

/* int main(int argc, char* argv[]){
    return 0;
} */
int yyerror(char *s){
  exit(1);
  return 1;
}