%{
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "util/AST.h"
#include "util/symbol.h"
#include "y.tab.h"
#define MAX_STR_CONST 1000
#define yyterminate() return EOF_TOKEN

#define YY_USER_ACTION \
  col += yyleng;
extern char *currentFileName;
int col = 1;
int lineno = 1;
int yyerror(char*s);
void point_at_in_line(int lineno, int from, int to);
%}

alpha [a-zA-Z]
alphanum [a-zA-Z0-9]
digit [0-9]
nonzero [1-9]

%x str
%x comment single_line_comment

%%
      char string_buf[MAX_STR_CONST];
      char *string_buf_ptr;



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
"continue" {return CONTINUE;}
"break" {return BREAK;}
"default" {return DEFAULT;}

"#include".*(\n) {col = 1; lineno++;
                  fprintf(stderr, ANSI_COLOR_BOLD ANSI_COLOR_YELLOW "Note: " ANSI_COLOR_RESET "Include directives are ignored\n");
                  point_at_in_line(lineno-2, 0, 8);
                }

 /* Symbols */
[-+*/%] return *yytext;
[;,:()] return *yytext;
[\{\}\[\]] return *yytext;
[=!<>] return *yytext;
  /* [&|] return *yytext; */

"==" {return EQ;}
">=" {return GE;}
"<=" {return LE;}
"!=" {return NE;}

"&&" {return AND;}
"||" {return OR;}

"++" {return INC;}
"--" {return DEC;}

"+=" {return PLUS_ASSIGN;}
"-=" {return MINUS_ASSIGN;}
"*=" {return STAR_ASSIGN;}
"/=" {return SLASH_ASSIGN;}
"%=" {return MOD_ASSIGN;}


  /* Identifiers */
(_|{alpha})((_|{alphanum}))* {
  yylval.id.name = malloc(strlen(yytext)+1);
  yylval.id.src.line = lineno;
  yylval.id.src.col = col - yyleng;
  // yylval.name = malloc(strlen(yytext)+1);
  strcpy(yylval.id.name, yytext);
  // strcpy(yylval.name, yytext);
  return IDENTIFIER;  
}

  /* Integers */
0 {yylval.iValue = 0; return INTEGER;}
{nonzero}({digit})*([eE][-+]?[0-9]+)? {yylval.iValue = (int)round(atof(yytext)); return INTEGER;}

  /* Floats */
{nonzero}({digit})*"."({digit})*([eE][-+]?[0-9]+)? {yylval.fValue = atof(yytext); return FLOAT;}

  /* Characters */
"\'"({alpha}|{digit})"\'" {yylval.cValue = yytext[1]; return CHARACTER;}

  /* Comments*/
  /* "//"[^\n]*\n { lineno++; } */
"//" BEGIN(single_line_comment);
<single_line_comment>"\n" {col = 1; lineno++; BEGIN(INITIAL);}
<single_line_comment><<EOF>> {BEGIN(INITIAL); return EOF_TOKEN;}
<single_line_comment>[^\n]+ ;

"/*" BEGIN(comment);
<comment>"\n" {col = 1; lineno++;}
<comment>"*/" {BEGIN(INITIAL);}
<comment><<EOF>> {yyerror("Unclosed comment found\n");}
<comment>. ;


  /* Strings*/
\" { string_buf_ptr = string_buf; BEGIN(str);}
<str>\" {
  BEGIN(INITIAL);
  *string_buf_ptr = '\0';
  yylval.sValue = (char*)malloc(strlen(string_buf)+1);
  strcpy(yylval.sValue, string_buf);
  return STRING;
}
<str>\n {yyerror("Unterminated string.\n"); return ERROR;}
<str>\\n {*string_buf_ptr++ = '\n';}
<str>[^\n] {
  *string_buf_ptr++ = *yytext;
}

  /* Whitespace */
[ \t\r] ;
\n {col = 1; lineno++;}

  /* <<EOF>> return EOF_TOKEN; */
  /* Error */
. {yyerror("Error: Invalid character"); return ERROR;}

%%
int yywrap(){
  yyterminate();
  return EOF_TOKEN;
}

int yyerror(char *s){
  fprintf(stderr, ANSI_COLOR_BOLD "%s[%d:%d] "ANSI_COLOR_RED "%s" ANSI_COLOR_RESET " at '%s'\n", currentFileName, lineno, col-1, s, yytext);
  point_at_in_line(lineno-1, col - yyleng-2, col-2);
  exit(1);
}

char *getlineat(int lineno)
{
  FILE *file = fopen(currentFileName, "r");
  // read the line `lineno` from file
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int i = 0;
  while ((read = getline(&line, &len, file)) != -1)
  {
    if (i == lineno)
    {
      return line;
    }
    i++;
  }
  return (char*)0;
}


void point_at_in_line(int lineno, int from, int to)
{
  // print the line and show a caret from bottom line at position `col`
  char *line = getlineat(lineno);
  if(!line || strlen(line) == 0){
    fprintf(stderr, "\tError at [End of file]\n");
    return;
  }
  // Recover silently and gracefully in invalid inputs
  if (from > to)
  {
    int temp = from;
    from = to;
    to = temp;
  }
  if (strlen(line) < to)
  {
    to = strlen(line);
  }
  if (strlen(line) < from)
  {
    from = strlen(line);
  }
  from = (from < 0) ? 0 : from;
  // print all characters till 'from'
  fprintf(stderr, "   %d | %.*s", lineno+1, from, line);
  // color characters enclosed in from-to with red and boldface
  fprintf(stderr, "\e[31;1m%.*s\e[0m", to - from, line + from);
  // print all characters from 'to' till end of line
  fprintf(stderr, "%s", line + to);

  //check if last character was newline, if not print it
  if(line[strlen(line)-1] != '\n'){
    fprintf(stderr, "\n");
  }

  //find number of digits in lineno for the left offset
  int offset = 0;
  lineno++;
  while((lineno) > 0){
    offset++;
    lineno /= 10;
  }
  //add the left padding
  offset+=3;
  while(offset--){
    fprintf(stderr, " ");
  }
  fprintf(stderr, " | ");

  for (int i = 0; i < from; i++)
  {
    fprintf(stderr, " ");
  }
  //place the caret
  fprintf(stderr, "\e[32;1m" ANSI_COLOR_RED "^");
  //underline the rest of the characters
  for(int i=from; i < to-1; i++){
    fprintf(stderr, "~");
  }
  fprintf(stderr, ANSI_COLOR_RESET "\n");
}