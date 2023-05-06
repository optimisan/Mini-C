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
// globals is for built in functions
// identifiers is the current table
extern struct SymbolTable *globals, *identifiers;

/**
 * @brief Type of a variable or function
 *
 */
typedef enum
{
  T_CHAR,
  T_INT,
  T_FLOAT,
  T_ARRAY,
  T_FUNCTION,
  T_VOID
} TypeEnum;

/// Coordinate in the source file
typedef struct
{
  // Length is for an expression
  unsigned int line, col, length;
} Coordinate;

/// @brief Identifier struct used in parser.y as a token type
typedef struct
{
  Coordinate src;
  char *name;
} IdStruct;

struct Type;

/// @brief Scope of a table/symbol
typedef enum
{
  S_GLOBAL = 1,
  S_PARAM,
  S_LOCAL
} Scope;
struct Symbol;

/// @brief The type of a symbol
typedef struct Type
{
  /// Operator of this Type
  TypeEnum op;
  // Number of elements in an array
  // or number of parameters in a function
  int size;
  // Number of dimensions in an array
  // Unused
  int ndim;
  // 1 if the function is variadic
  short int variadicFunc;
  // Points back to the symbol of the function
  struct Symbol *sym;
  // Line number of the declaration of the symbol
  int lineno;
  // Function prototype
  // An array of size `size` of Type* of
  // the parameters of the function
  struct Type **proto;
  // The type operand
  // For a function this is the return type
  // For an array this is the element type
  // In all other cases this is NULL
  // Ex. int arr[][3]; has
  // op              = T_ARRAY,
  // type->op        = T_ARRAY,
  // type->type->op  = T_INT
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

// New type with only the `op` field set
Type *newType(TypeEnum typeEnum);

/**
 * @brief Initializes the symbol table
 * globals at level S_GLOBAL - 1
 * identifiers at level S_GLOBAL
 */
void initSymbolTable();

/**
 * @brief Widen the type of the two types. Use for math operations.
 */
TypeEnum typeWiden(TypeEnum t1, TypeEnum t2);
/**
 * @brief Get the Host Size for the literal type
 *
 * @param type
 * @return int
 */
int getHostSize(TypeEnum type);

// Travel through the array `Type` and
// get the `op` field of the last `Type` in the array
TypeEnum getArrayBaseType(Type *type);

/**
 * @brief Get the array size except the first dimension
 *
 * Ex. int a[2][3][4] -> 3*4 -> 12
 *
 * Ignores unspecfiied dimensions as 1
 * Ex. int a[][3][] -> 3*1 -> 3
 * although this is an invalid case.
 *
 * @param type
 * @return int
 */
int getArraySize(Type *type);
/**
 * @brief Creates a new symbol table at level
 *
 * If table is not NULL, then the new table will have the same
 * `all` list as the old one.
 *
 * @param table The current table to which the enclosing pointer of this table will point to
 * @param level The level of the new table
 * @return SymbolTable*
 */
SymbolTable *newTable(SymbolTable *table, int level);

/**
 * @brief Inserts the symbol in specified table
 *
 * Creates a new table if the level of the table is not equal to the current level
 *
 * **`name`** is not copied. It is assumed that the caller will not free it.
 *
 * @param name Symbol name string. Is NOT copied.
 * @param table Symbol Table pointer. If this table's level is not equal to the current level,
 * a new table is created.
 * @param level Current level of symbol
 * @return Symbol*
 */
Symbol *install(char *name, SymbolTable **table, int level, Coordinate src);

/**
 * @brief Looks up the symbol in the specified table and all enclosing ones.
 *
 * **`name`** is not copied. It is assumed that the caller will not free it.
 *
 * @param name
 * @param table
 * @return Symbol*
 */
Symbol *lookup(char *name, SymbolTable *table);

// Call when a new scope is entered
void beginScope();

// Call when a scope is exited
// Points identifiers to the enclosing table and
// decrements the current `level`
void endScope();

#endif