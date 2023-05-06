#include <stdio.h>
#include <stdlib.h>
#include "./util/options.h"
#include "./util/token.h"
#include "./util/AST.h"
#include "./util/symbol.h"
#include "./backend/built-in-functions.h"
#include "y.tab.h"

// The current line number.
// This is from tokenizer.l.
extern int lineno;
extern FILE *yyin;
// Current token's lexeme
extern char *yytext;
// The source file name
extern char *currentFileName;
// From lex.yy.c, returns the next token.
// Ends with EOF
int yylex();
// Parses the source (from parser.y)
int yyparse();

// Prints all tokens frrom yylex()
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
/**
 * @brief Run the compiler
 *
 * This calls `yyparse()` which calls `backend` (backend/backend.c) when the start
 * production rule is reduced.
 *
 * The AST is passed to `backend` which generates the IR (as three address code)
 * and then calls the `VM` (virtual machine) to execute the IR.
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char *argv[])
{
  // Options like --dump-ast are parsed and flags set here
  char *filename = parseOptions(argc, argv);
  // Open fresh
  yyin = fopen(filename, "r");
  if (!yyin)
  {
    fprintf(stderr, "Failed to open file %s\n", filename);
    return 1;
  }
  currentFileName = filename;
  if (dumpTokens)
    testTokenizer();
  // On testing the tokenizer the file is read till the end,
  // so re-initialize the file pointer.
  yyin = fopen(filename, "r");
  lineno = 1;
  // Starting the parser
  // Initialise the symbol tables
  initSymbolTable();
  // Add the built in functions
  // to the global symbol table
  installBuiltInFunctions(globals);
  // Run the parser. All further operations will be
  // from parser.y
  int error = yyparse();
  if (error)
  {
    return 1;
  }
  // printf("Successful\n");
  return 0;
}