#include <stdio.h>
#include <stdlib.h>
#include "./util/token.h"
#include "./util/AST.h"
#include "./util/symbol.h"
#include "./backend/built-in-functions.h"
#include "y.tab.h"

// extern yyin;
SymbolTable *table;
// extern char *yytext;
extern int lineno;
extern FILE *yyin;
extern char *yytext;
extern char *currentFileName;
int yylex();
int yyparse();

void testTokenizer()
{
  int token;
  printf(ANSI_COLOR_MAGENTA ANSI_COLOR_BOLD "%-10s\t\t %-18s\t\t %-18s\t\n" ANSI_COLOR_RESET, "Line number", "Lexeme", "Token Type");

  while ((token = yylex()) != EOF_TOKEN && token != 0)
  {
    // printf("%s: %s = %f\n", tokenStr(token), yytext, yylval.fValue);
    printToken(token);
  }
  printf("%-10d\t\t %-18s\t\t %-18s\t\n", lineno, "EOF", "EOF");
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return 1;
  }
  yyin = fopen(argv[1], "r");
  if (!yyin)
  {
    fprintf(stderr, "Failed to open file %s\n", argv[1]);
    return 1;
  }
  currentFileName = argv[1];

  testTokenizer();
  yyin = fopen(argv[1], "r");
  lineno = 1;
  // return 0;
  // printf("Starting parser\n");
  initSymbolTable();
  installBuiltInFunctions(globals);
  int error = yyparse();
  if (error)
  {
    return 1;
  }
  // printf("Successful\n");
  return 0;
}