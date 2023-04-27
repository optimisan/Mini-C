#include "token.h"
#include "symbol.h"
#include "AST.h"
#include "../y.tab.h"
#include <stdlib.h>
#include <stdio.h>
extern char *yytext;
extern int lineno;
char *tokenStr(int token)
{
  switch (token)
  {
  case K_INT:
    return "K_INT";
  case K_FLOAT:
    return "K_FLOAT";
  case K_CHAR:
    return "K_CHAR";
  case FOR:
    return "FOR";
  case WHILE:
    return "WHILE";
  case ELSE:
    return "ELSE";
  case IF:
    return "IF";
  case SWITCH:
    return "SWITCH";
  case CASE:
    return "CASE";
  case RETURN:
    return "RETURN";
  case CONTINUE:
    return "CONTINUE";
  case BREAK:
    return "BREAK";
  case DEFAULT:
    return "DEFAULT";
  case INTEGER:
    return "INTEGER";
  case FLOAT:
    return "FLOAT";
  case CHARACTER:
    return "CHARACTER";
  case STRING:
    return "STRING";
  case PLUS_ASSIGN:
    return "PLUS_ASSIGN";
  case MINUS_ASSIGN:
    return "MINUS_ASSIGN";
  case STAR_ASSIGN:
    return "STAR_ASSIGN";
  case SLASH_ASSIGN:
    return "SLASH_ASSIGN";
  case MOD_ASSIGN:
    return "MOD_ASSIGN";
  case INC:
    return "INC";
  case DEC:
    return "DEC";
  case EQ:
    return "EQ";
  case LE:
    return "LE";
  case GE:
    return "GE";
  case NE:
    return "NE";
  case AND:
    return "AND";
  case OR:
    return "OR";
  case IDENTIFIER:
    return "IDENTIFIER";
  case ERROR:
    return "ERROR";
  case EOF_TOKEN:
    return "EOF_TOKEN";
  default:
  {
    char *s = malloc(1);
    s[0] = token;
    return s;
  }
  }
}
void printToken(int token)
{
  printf("%-10d\t\t %-18s\t\t %-18s\t\n", lineno, ((token == STRING) ? yylval.sValue : yytext), tokenStr(token));
}