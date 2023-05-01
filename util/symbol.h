#ifndef __SYMBOL
#define __SYMBOL
#include "map.h"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_PINK "\x1b[91m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_BOLD "\x1b[1m"

struct SymbolTable;
extern int level;
extern struct SymbolTable *globals, *identifiers;

typedef enum
{
  T_CHAR,
  T_INT,
  T_FLOAT,
  T_ARRAY,
  T_FUNCTION,
  T_VOID
} TypeEnum;

typedef struct
{
  // Length is for an expression
  unsigned int line, col, length;
} Coordinate;

typedef struct
{
  Coordinate src;
  char *name;
} IdStruct;

struct Type;

typedef enum
{
  S_GLOBAL = 1,
  S_PARAM,
  S_LOCAL
} Scope;
struct Symbol;
typedef struct Type
{
  TypeEnum op;
  int size;
  int ndim;
  short int variadicFunc;
  struct Symbol *sym;
  int lineno;
  // Function prototype
  struct Type **proto;
  // The type operand
  // For a function this is the return type
  // For an array this is the element type
  // In all other cases this is NULL
  struct Type *type;
} Type;

/**
 * @brief Symbol table entry
 */
typedef struct Symbol
{
  // The name of symbol Ex. arr, sqrt
  char *name;
  // The scope of the symbol
  Scope scope;
  // The Coordinate of the symbol
  // Used for error reporting
  Coordinate src;
  struct Symbol *up;
  // Type of variable or function
  Type *type;
} Symbol;

/**
 *
 *
 */
typedef struct SymbolTable
{
  int level; // 1 for function, 2 for a block inside function
  struct SymbolTable *enclosing;
  // Map string->Symbol*
  hashmap *map;
  Symbol *all;
} SymbolTable;

Type *newType(TypeEnum typeEnum);

void initSymbolTable();
TypeEnum typeWiden(TypeEnum t1, TypeEnum t2);

int getHostSize(TypeEnum type);
TypeEnum getArrayBaseType(Type *type);
int getArraySize(Type *type);
SymbolTable *newTable(SymbolTable *table, int level);
Symbol *install(char *name, SymbolTable **table, int level, Coordinate src);
Symbol *lookup(char *name, SymbolTable *table);
void beginScope();
void endScope();

#endif