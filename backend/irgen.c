#include "../util/AST.h"
#include "../util/symbol.h"
#include "../util/token.h"
#include "ir.h"
#include "irgen.h"
#include <stdio.h>
#include <stdlib.h>

IR *ir;

static Address *irNode(Node *node);

IR *generateIR(Node *rootNode, char *sourceFilename)
{
  ir = newIR(sourceFilename);
  irNode(rootNode);
  return ir;
}
static Address *irAssign(Node *node);
static Address *irLiteral(Node *node);
static Address *irSymbol(Node *node);
static Address *irVarDecl(Node *node);
static Address *irFunctionDecl(Node *node);

static Address *irNode(Node *node)
{
  if (node == NULL)
    return NULL;
  // printNode(node);
  // return NULL;
  if (node->type == NODE_OPR)
  {
    switch (node->as.opr.type)
    {
    case OPR_DECL_LIST:
    case OPR_LIST:
      irNode(node->as.opr.operands[0]);
      irNode(node->as.opr.operands[1]);
      break;
    case OPR_ASSIGN:
      irAssign(node);
      break;
    case OPR_VAR_DECL:
      irVarDecl(node);
      break;
    case OPR_FUNC:
      irFunctionDecl(node);
      break;
    // case OPR_IF:
    //   irIf(node);
    //   break;
    // case OPR_WHILE:
    //   irWhile(node);
    //   break;
    // case OPR_FOR:
    //   irFor(node);
    //   break;
    // case OPR_RETURN:
    //   irReturn(node);
    //   break;
    // case OPR_PRINT:
    //   irPrint(node);
    //   break;
    // case OPR_READ:
    //   irRead(node);
    //   break;
    // case OPR_FUNC:
    //   irFunc(node);
    //   break;
    // case OPR_ARG:
    //   irArg(node);
    //   break;
    // case OPR_CALL:
    //   irCall(node);
    //   break;
    // case OPR_CAST:
    //   irCast(node);
    //   break;
    // case OPR_NEG:
    //   irNeg(node);
    //   break;
    // case OPR_POS:
    //   irPos(node);
    //   break;
    // case OPR_INDEX:
    //   irIndex(node);
    //   break;
    // case OPR_DEREF:
    //   irDeref(node);
    //   break;
    // case OPR_ADDR:
    //   irAddr(node);
    //   break;
    // case OPR_SIZEOF:
    //   irSizeof(node);
    //   break;
    // case OPR_CAST_INT:
    // case OPR_CAST_FLOAT:
    // case OPR_CAST_CHAR:
    //   irCast(node);
    //   break;
    case OPR_LT:
    case OPR_LE:
    case OPR_GT:
    case OPR_GE:
    case OPR_EQ:
    case OPR_NE:
    case OPR_AND:
    case OPR_OR:
      // irBinary(node);
      break;
    default:
      break;
    }
  }
  else if (node->type == NODE_LITERAL)
  {
    return irLiteral(node);
  }
  else if (node->type == NODE_SYMBOL)
  {
    return irSymbol(node);
  }
  return NULL;
}
static Address *irLiteral(Node *node)
{
  if (node->type != NODE_LITERAL)
  {
    printf("node is not a literal\n");
    exit(1);
  }
  TypeEnum constType = node->as.value->type;
  switch (constType)
  {
  case T_INT:
    return newIntAddress(constType, node->as.value->as.integer, node->src);
  case T_CHAR:
    return newCharAddress(constType, node->as.value->as.character, node->src);
  case T_FLOAT:
    return newFloatAddress(constType, node->as.value->as.floating, node->src);
  default:
    printf("literal type not supported\n");
    exit(1);
  }
}
static Address *irFunctionDecl(Node *node)
{
  Node *funcSymNode = node->as.opr.operands[0];
  Address *funcAddr = functionAddress(funcSymNode->as.symbol, ir);
  addInstruction(ir, newInstruction(OP_FUNC, NULL, NULL, funcAddr));
  Node *params = node->as.opr.operands[1];
  typedef struct Param
  {
    Address *addr;
    struct Param *next;
  } Param;
  Param *paramList = NULL;
  while (params->type == NODE_OPR)
  {
    Node *param = params->as.opr.operands[1];
    Address *paramAddr = irNode(param);
    Param *newParam = malloc(sizeof(Param));
    newParam->addr = paramAddr;
    newParam->next = paramList;
    paramList = newParam;
    params = params->as.opr.operands[0];
  }
  addInstruction(ir, newInstruction(OP_PARAM, NULL, NULL, irNode(params)));
  while (paramList)
  {
    if (paramList->addr)
    {
      addInstruction(ir, newInstruction(OP_PARAM, NULL, NULL, paramList->addr));
    }
    Param *next = paramList->next;
    free(paramList);
    paramList = next;
  }
  Node *funcBody = node->as.opr.operands[2];
  beginFunction();
  irNode(funcBody);
  endFunction();
}
static Address *irSymbol(Node *node)
{
  return symbolAddress(node->as.symbol, ir);
}
static void arrayDeclaration(Node *varInitialiser)
{
  printf("\namazing array\n");
  printNode(varInitialiser);
  printf("\n");
  exit(1);
}
static Address *irVarDecl(Node *node)
{
#define ADD_VAR_DECL()                                             \
  Address *left = irNode(varInitialiser->as.opr.operands[0]);      \
  Address *expr;                                                   \
  if (varInitialiser->as.opr.operands[1] != NULL)                  \
  {                                                                \
    arrayDeclaration(varInitialiser);                              \
  }                                                                \
  else                                                             \
  {                                                                \
    if (varInitialiser->as.opr.nops == 2)                          \
    {                                                              \
      expr = newIntAddress(T_INT, 0, (Coordinate){0, 0, 0});       \
    }                                                              \
    else                                                           \
      expr = irNode(varInitialiser->as.opr.operands[2]);           \
    instructions[i] = newInstruction(OP_ASSIGN, expr, NULL, left); \
  }
  //^ Second operand is the array specifier, so ignore

  Node *list = node->as.opr.operands[0];
  // Since we are going in reverse (actually should be depth first),
  // we need to store the instructions in an array
  // and then add them later in reverse order
  int i = 0;
  Instruction *instructions[list->as.opr.nops];
  if (list->as.opr.type != OPR_LIST)
  {
    // single var assignment
    Node *varInitialiser = list;
    ADD_VAR_DECL();
  }
  for (; list->as.opr.nops == 2 && list->as.opr.type == OPR_LIST; list = list->as.opr.operands[0], i++)
  {
    Node *varInitialiser = list->as.opr.operands[1];
    ADD_VAR_DECL();
  }
  Node *varInitialiser = list;
  ADD_VAR_DECL();
  // add instructions in reverse
  for (int j = i; j >= 0; j--)
  {
    addInstruction(ir, instructions[j]);
  }
#undef ADD_VAR_DECL
}
static Address *irAssign(Node *node)
{
  Address *left = irNode(node->as.opr.operands[0]);
  Address *right = irNode(node->as.opr.operands[1]);
  // no need to check type, it's already checked in semantic analysis
  addInstruction(ir, newInstruction(OP_ASSIGN, right, NULL, left));
}