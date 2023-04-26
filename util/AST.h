#ifndef __AST
#define __AST
#include "symbol.h"

typedef struct
{
  TypeEnum type;
  int size;
  union
  {
    int integer;
    float floating;
    char character;
    void *data;
    char *idVal;
  } as;
} Value;

typedef enum
{
  NODE_LITERAL,
  NODE_SYMBOL,
  NODE_OPR,
  NODE_STMT
} NodeType;

typedef enum
{
  OPR_VAR_DECL,
  OPR_ASSIGN,
  OPR_DECL_LIST,
  OPR_IF,
  OPR_WHILE,
  OPR_FOR,
  OPR_SWITCH,
  OPR_CASE,
  OPR_BREAK,
  OPR_CONTINUE,
  OPR_FUNC,
  OPR_CALL,
  OPR_LIST,
  OPR_RETURN,
  OPR_PRINT,
  OPR_SCAN,
  OPR_BLOCK,
  // MATH
  OPR_INC,
  OPR_DEC,
  OPR_GE,
  OPR_LE,
  OPR_GT,
  OPR_LT,
  OPR_EQ,
  OPR_NE,
  OPR_AND,
  OPR_OR,
  // Other math are ascii
} OprType;

struct Node;
typedef struct exprType
{
  TypeEnum op;
  int ndim;
  TypeEnum base;
} ExprType;
typedef struct Node
{
  NodeType type;
  ExprType exprType;
  Coordinate src;
  union
  {
    Value *value;
    Symbol *symbol;
    struct opr
    {
      int type;
      Type *exprType;
      int nops;
      struct Node **operands;
    } opr;
  } as;
} Node;

Node *charNode(int value);
Node *intNode(int value);
Node *floatNode(float value);
Node *strNode(char *str, int length);
Node *arrayNode(void *data, int length);
Node *identifierNode(Symbol *symbol);
Node *oprNode(OprType type, int nops, ...);
Node *stmtNode(OprType type, int nops, ...);

void freeFunctionAST(Node *node);
void freeNode(Node *node);
void printNode(Node *node);

#endif