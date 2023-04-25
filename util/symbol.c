#include "map.h"
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
  globals->level = S_GLOBAL;
  globals->enclosing = NULL;
  identifiers = malloc(sizeof(SymbolTable));
  identifiers->map = hashmap_create();
  identifiers->level = S_GLOBAL;
  identifiers->enclosing = NULL;
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
/**
 * @brief Inserts the symbol in specified table
 *
 * **`name`** is not copied. It is assumed that the caller will not free it.
 *
 * @param name Symbol name string. Is NOT copied.
 * @param table Symbol Table
 * @param level Current level of symbol
 * @return Symbol*
 */
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
/**
 * @brief Looks up the symbol in the specified table and all enclosing ones.
 *
 * **`name`** is not copied. It is assumed that the caller will not free it.
 *
 * @param name
 * @param table
 * @return Symbol*
 */
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