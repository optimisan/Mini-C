#include "AST.h"
#include "symbol.h"
#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
extern int lineno, col, yyleng;
Node *charNode(int value)
{
  Node *node = malloc(sizeof(Node));
  node->type = NODE_LITERAL;
  node->exprType.op = T_CHAR;
  node->src.line = lineno;
  node->src.col = col - 3;
  node->src.length = 3;
  Value *v = malloc(sizeof(Value));
  node->as.value = v;
  v->type = T_CHAR;
  v->as.character = value;
  return node;
}
Node *intNode(int value)
{
  Node *node = malloc(sizeof(Node));
  node->type = NODE_LITERAL;
  node->exprType.op = T_INT;
  node->src.line = lineno;
  node->src.col = col - yyleng;
  node->src.length = yyleng;
  Value *v = malloc(sizeof(Value));
  node->as.value = v;
  v->type = T_INT;
  v->as.integer = value;
  return node;
}
Node *floatNode(float value)
{
  Node *node = malloc(sizeof(Node));
  node->type = NODE_LITERAL;
  node->exprType.op = T_FLOAT;
  node->src.line = lineno;
  node->src.col = col - yyleng;
  node->src.length = yyleng;
  Value *v = malloc(sizeof(Value));
  node->as.value = v;
  v->type = T_FLOAT;
  v->as.floating = value;
  return node;
}
Node *strNode(char *str, int length)
{
  Node *node = malloc(sizeof(Node));
  node->type = NODE_LITERAL;
  node->exprType.op = T_ARRAY;
  node->exprType.ndim = 1;
  node->exprType.base = T_CHAR;
  node->src.line = lineno;
  node->src.col = col - length;
  node->src.length = length;
  Value *v = malloc(sizeof(Value));
  node->as.value = v;
  v->type = T_ARRAY;
  v->size = length;
  // copy the string in str
  char *s = malloc(strlen(str) + 1);
  strcpy(s, str);
  v->as.data = s;
  return node;
}
Node *arrayNode(void *data, int length)
{
  Node *node = malloc(sizeof(Node));
  node->type = NODE_LITERAL;
  node->exprType.op = T_ARRAY;
  node->exprType.ndim = length;
  node->src.line = lineno;
  node->src.length = length * 2;
  node->src.col = col - node->src.length;
  Value *v = malloc(sizeof(Value));
  node->as.value = v;
  v->type = T_ARRAY;
  v->size = length;
  v->as.data = data;
  return node;
}
Node *identifierNode(Symbol *symbol)
{
  Node *node = malloc(sizeof(Node));
  if (!node)
  {
    fprintf(stderr, "Failed to allocate memory for node");
    exit(1);
  }
  node->type = NODE_SYMBOL;
  node->exprType.op = (symbol->type) ? symbol->type->op : -1;
  node->exprType.ndim = -1;
  Type *base = symbol->type;
  while (base)
  {
    node->exprType.ndim++;
    node->exprType.base = base->op;
    base = base->type;
  }
  // printf("back %d\n", node->exprType.ndim);
  node->as.symbol = symbol;
  node->src.line = lineno;
  node->src.length = strlen(symbol->name);
  node->src.col = col - node->src.length;
  return node;
}
Node *stmtNode(OprType type, int nops, ...)
{
  va_list va;
  Node *node = malloc(sizeof(Node));

  if (!node)
  {
    fprintf(stderr, "Failed to allocate memory for node\n");
    exit(1);
  }
  node->type = NODE_STMT;
  node->as.opr.operands = malloc(sizeof(Node *) * nops);
  node->src.line = lineno;
  node->src.col = col - 3;
  node->src.length = 3;
  if (!node->as.opr.operands)
  {
    fprintf(stderr, "Failed to allocate memory for operands\n");
    exit(1);
  }
  node->as.opr.nops = nops;
  node->as.opr.type = type;
  va_start(va, nops);
  for (int i = 0; i < nops; i++)
  {
    node->as.opr.operands[i] = va_arg(va, Node *);
  }
  va_end(va);
  return node;
}
Node *oprNode(OprType type, int nops, ...)
{
  va_list va;
  Node *node = malloc(sizeof(Node));
  if (!node)
  {
    fprintf(stderr, "Failed to allocate memory for node\n");
    exit(1);
  }
  node->type = NODE_OPR;
  node->as.opr.operands = malloc(sizeof(Node *) * nops);
  if (!node->as.opr.operands)
  {
    fprintf(stderr, "Failed to allocate memory for operands\n");
    exit(1);
  }
  node->src.line = lineno;
  node->src.col = col - 3;
  node->src.length = 3;
  node->as.opr.nops = nops;
  node->as.opr.type = type;
  va_start(va, nops);
  for (int i = 0; i < nops; i++)
  {
    node->as.opr.operands[i] = va_arg(va, Node *);
  }
  va_end(va);
  return node;
}

void freeNode(Node *node)
{
  if (!node)
    return;
  switch (node->type)
  {
  case NODE_LITERAL:
    if (node->as.value->type == T_ARRAY)
    {
      free(node->as.value->as.data);
    }
    free(node->as.value);
    free(node);
    return;
  case NODE_SYMBOL:
    free(node);
    return;
  case NODE_OPR:
    for (int i = 0; i < node->as.opr.nops; i++)
    {
      freeNode(node->as.opr.operands[i]);
    }
    free(node);
  default:
    break;
  }
}
void freeFunctionAST(Node *node)
{
  if (node->type == NODE_OPR && node->as.opr.type == OPR_FUNC)
  {
    // free the param list
    freeNode(node->as.opr.operands[1]);
    // printf("Freed param list for function\n");
    // free the body
    freeNode(node->as.opr.operands[2]);
    // printf("Freed body for function\n");
  }
}
void printNodeWithOffset(Node *node, int offset)
{
#define PRINT_OFFSET()             \
  for (int i = 0; i < offset; i++) \
  {                                \
    printf("    ");                \
  }
  PRINT_OFFSET();
  if (!node)
  {
    printf("null\n");
    return;
  }

  switch (node->type)
  {
  case NODE_LITERAL:
    switch (node->as.value->type)
    {
    case T_INT:
      printf("INT: %d", node->as.value->as.integer);
      break;
    case T_FLOAT:
      printf("FLOAT: %f", node->as.value->as.floating);
      break;
    case T_ARRAY:
      printf("ARR: %s", (char *)node->as.value->as.data);
      break;
    default:
      break;
    }
    break;
  case NODE_SYMBOL:
    printf("SYM %s", node->as.symbol->name);
    break;
  case NODE_OPR:
    // printf("NODE_OPR ");
    switch (node->as.opr.type)
    {
    case OPR_ASSIGN:
      printf("=");
      break;
    case OPR_IF:
      printf("if");
      break;
    case OPR_WHILE:
      printf("while");
      break;
    case OPR_FOR:
      printf("for");
      break;
    case OPR_FUNC:
      printf("func");
      break;
    case OPR_RETURN:
      printf("return");
      break;
    case OPR_CALL:
      printf("call");
      break;
    case OPR_PRINT:
      printf("print");
      break;
    case OPR_SCAN:
      printf("SCAN");
      break;
    case '[':
      printf("array_index");
      break;
    case OPR_LIST:
      printf("list");
      break;
    case OPR_DECL_LIST:
      printf("decl_list");
      break;
    case OPR_VAR_DECL:
      printf("var_decl");
      break;
    default:
      printf("%c", node->as.opr.type);
      break;
    }
    // PRINT_OFFSET();

    printf("(\n");
    for (int i = 0; i < node->as.opr.nops; i++)
    {
      printNodeWithOffset(node->as.opr.operands[i], offset + 1);
      if (i < node->as.opr.nops - 1)
      {
        // printf("\n");
      }
    }
    PRINT_OFFSET();

    printf(")");
    break;
  default:
    break;
  }
  printf("\n");
}

void printNode(Node *node)
{
  printNodeWithOffset(node, 0);
}