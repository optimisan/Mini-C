#include "map.h"
#include "AST.h"
#include "symbol.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SymbolTable *globals, *identifiers;
int level = S_GLOBAL;

void initSymbolTable()
{
  globals = malloc(sizeof(SymbolTable));
  globals->map = hashmap_create();
  globals->level = S_GLOBAL - 1;
  globals->enclosing = NULL;
  identifiers = malloc(sizeof(SymbolTable));
  identifiers->map = hashmap_create();
  identifiers->level = S_GLOBAL;
  identifiers->enclosing = globals;
}
SymbolTable *newTable(SymbolTable *table, int level)
{
  SymbolTable *t = malloc(sizeof(SymbolTable));
  t->enclosing = table;
  t->level = level;
  t->map = hashmap_create();
  if (table)
    t->all = table->all;
  return t;
}

Symbol *install(char *name, SymbolTable **table, int level, Coordinate src)
{
  Symbol *symbol = malloc(sizeof(Symbol));
  SymbolTable *tp = *table;
  hashmap *map = tp->map;
  if (level > 0 && tp->level < level)
  {
    tp = *table = newTable(tp, level);
  }
  symbol->name = name;
  symbol->scope = level;
  symbol->type = NULL;
  symbol->up = tp->all;
  symbol->src = src;
  tp->all = symbol;
  int g = hashmap_get_set(tp->map, name, strlen(name), (uintptr_t *)&symbol);
  return symbol;
}

Symbol *lookup(char *name, SymbolTable *table)
{
  uintptr_t symbol;
  while (table)
  {
    if (hashmap_get(table->map, name, strlen(name), &symbol))
    {
      return (Symbol *)symbol;
    }
    table = table->enclosing;
  }
  return NULL;
}

void beginScope()
{
  level++;
}
void freeSymbolsAtLevel(int level)
{
  Symbol *all = identifiers->all;
  Symbol *next = all;
  while (all && all->scope >= level)
  {
    printf("freeing symbol %s\n", all->name);
    next = all->up;
    free(all->name);
    if (all->type)
      free(all->type);
    free(all);
    all = next;
  }
}
void endScope()
{
  if (identifiers->level == level)
  {
    identifiers = identifiers->enclosing;
  }
  level--;
}
Type *newType(TypeEnum typeEnum)
{
  Type *type = malloc(sizeof(Type));
  memset(type, 0, sizeof(Type));
  type->op = typeEnum;
  return type;
}
int getHostSize(TypeEnum type)
{
  switch (type)
  {
  case T_INT:
    return (int)(sizeof(int));
  case T_FLOAT:
    return (int)(sizeof(float));
  case T_CHAR:
    return (int)(sizeof(char));
  default:
    printf("invalid type for host size\n");
    exit(1);
  }
}
TypeEnum getArrayBaseType(Type *type)
{
  while (type->type != NULL)
  {
    type = type->type;
  }
  return type->op;
}
int getArraySize(Type *type)
{
  int size = 1;
  while (type->type)
  {
    size *= (type->size == 0 ? 1 : type->size);
    type = type->type;
  }
  return size;
}

TypeEnum typeWiden(TypeEnum t1, TypeEnum t2)
{
  // arrays are not allowed
  if (t1 == T_ARRAY || t2 == T_ARRAY)
  {
    return -1;
  }
  if (t1 == T_FLOAT || t2 == T_FLOAT)
  {
    return T_FLOAT;
  }
  if (t1 == T_INT || t2 == T_INT)
  {
    return T_INT;
  }
  if (t1 == T_CHAR || t2 == T_CHAR)
  {
    return T_CHAR;
  }
  return -1;
}