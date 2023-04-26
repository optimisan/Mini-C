#include "built-in-functions.h"
#include "../util/symbol.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void installBuiltInFunctions(SymbolTable *table)
{
  Symbol *funcSym = install("printf", &table, S_GLOBAL - 1, (Coordinate){0, 0, 0});
  Type *type = newType(T_FUNCTION);
  type->variadicFunc = 1;
  type->size = 1;
  type->proto = malloc(sizeof(Type) * 2);
  type->proto[0] = newType(T_ARRAY);
  type->proto[0]->type = newType(T_CHAR);
  type->proto[0]->size = 1;
  type->type = newType(T_INT);
  funcSym->type = type;
  printf("printf type is %d\n", funcSym->type->op);
}