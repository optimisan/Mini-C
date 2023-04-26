#include "../util/AST.h"
#include "../util/symbol.h"
#include "../util/token.h"
#include "ir.h"
#include "irgen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void compileError(Coordinate pos, int lexemeLength, char *format, ...);

IR *ir;

static Address *irNode(Node *node);

IR *generateIR(Node *rootNode, char *sourceFilename)
{
  ir = newIR(sourceFilename);
  irNode(rootNode);
  return ir;
}
static Address *irAssign(Node *node);
static Address *irExpr(Node *node);
static Address *irLiteral(Node *node);
static Address *irSymbol(Node *node);
static Address *irVarDecl(Node *node);
static Address *irFunctionDecl(Node *node);
static Address *irFuncCall(Node *node);
static Address *irIf(Node *node);
static Address *irWhile(Node *node);
static Address *irFor(Node *node);

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
      // freeNode(node->as.opr.operands[0]);
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
    case OPR_CALL:
      return irFuncCall(node);
    case OPR_IF:
      irIf(node);
      break;
    case OPR_WHILE:
      irWhile(node);
      break;
    case OPR_FOR:
      irFor(node);
      break;
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
    default:
      return irExpr(node);
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

static Address *irFor(Node *node)
{
  Address *startLabel = newLabelAddress();
  Address *endLabel = newLabelAddress();
  irNode(node->as.opr.operands[0]);
  addInstruction(ir, newInstruction(OP_LABEL, NULL, NULL, startLabel));
  Address *condition = irNode(node->as.opr.operands[1]);
  addInstruction(ir, newInstruction(OP_IF_FALSE_GOTO, condition, NULL, endLabel));
  irNode(node->as.opr.operands[3]);
  irNode(node->as.opr.operands[2]);
  addInstruction(ir, newInstruction(OP_GOTO, NULL, NULL, startLabel));
  addInstruction(ir, newInstruction(OP_LABEL, NULL, NULL, endLabel));
  return NULL;
}

static Address *irWhile(Node *node)
{
  Address *startLabel = newLabelAddress();
  Address *endLabel = newLabelAddress();
  addInstruction(ir, newInstruction(OP_LABEL, NULL, NULL, startLabel));
  Address *condition = irNode(node->as.opr.operands[0]);
  addInstruction(ir, newInstruction(OP_IF_FALSE_GOTO, condition, NULL, endLabel));
  irNode(node->as.opr.operands[1]);
  addInstruction(ir, newInstruction(OP_GOTO, NULL, NULL, startLabel));
  addInstruction(ir, newInstruction(OP_LABEL, NULL, NULL, endLabel));
  return NULL;
}

static Address *irIf(Node *node)
{
  // Condition
  Address *condition = irNode(node->as.opr.operands[0]);
  Address *elseLabel = newLabelAddress();
  Address *endLabel;
  addInstruction(ir, newInstruction(OP_IF_FALSE_GOTO, condition, NULL, elseLabel));
  // Then
  irNode(node->as.opr.operands[1]);
  if (node->as.opr.nops == 3)
  {
    endLabel = newLabelAddress();
    addInstruction(ir, newInstruction(OP_GOTO, NULL, NULL, endLabel));
  }
  // Else
  addInstruction(ir, newInstruction(OP_LABEL, NULL, NULL, elseLabel));
  if (node->as.opr.nops == 3)
  {
    irNode(node->as.opr.operands[2]);
    addInstruction(ir, newInstruction(OP_LABEL, NULL, NULL, endLabel));
  }
}

static Address *irFuncCall(Node *node)
{
  // generate the parameters
  Node *params = node->as.opr.operands[1];
  int nparams = 0;
  if (params)
  {
    while (params && params->type == NODE_OPR && params->as.opr.type == OPR_LIST)
    {
      Node *param = params->as.opr.operands[1];
      Address *temp = irNode(param);
      nparams++;
      addInstruction(ir, newInstruction(OP_PARAM, temp, NULL, NULL));
      params = params->as.opr.operands[0];
    }
    nparams++;
    addInstruction(ir, newInstruction(OP_PARAM, irNode(params), NULL, NULL));
  }
  printf("\t nparams %d\n", nparams);
  Symbol *sym = node->as.opr.operands[0]->as.symbol;
  // int nparams1 = sym->type->size;
  Address *temp = newTempAddress(sym->type->type);
  addInstruction(ir, newInstruction(OP_CALL, symbolAddress(sym, ir), newIntAddress(nparams, node->src), temp));
  return temp;
}

static Address *irExpr(Node *node)
{
  if (node->as.opr.nops == 1)
  {
    Address *temp = newTempAddress(NULL);
    int type = node->as.opr.type;
    if (type == '-')
    {
      type = OP_MINUS;
    }
    addInstruction(ir, newInstruction(type, irNode(node->as.opr.operands[0]), NULL, temp));
    return temp;
  }
  else if (node->as.opr.nops == 2)
  {
    printf("got binary expr %d\n", node->as.opr.operands[0]->type);
    Address *left = irNode(node->as.opr.operands[0]);
    Address *right = irNode(node->as.opr.operands[1]);
    Address *temp = newTempAddress(newType(node->exprType.op));
    printf("got left as %d", left == NULL);
    addInstruction(ir, newInstruction(node->as.opr.type, left, right, temp));
    return temp;
  }
  printf("invalid expression\n");
  exit(1);
}
static Address *stringAddress(Value *value, Coordinate src)
{
  Type *elementType = newType(value->type);
  Type *type = newType(T_ARRAY);
  type->size = value->size + 1;
  type->type = elementType;
  Address *temp = newTempAddress(type);
  printf("Adding string address for %s\n", (char *)(value->as.data));
  int eleSize = getHostSize(T_CHAR);
  addInstruction(ir, newInstruction(OP_ARRAY_DECL, newIntAddress(value->size + 1, src), newIntAddress(eleSize, src), temp));
  for (int i = 0; i < value->size; i++)
  {
    addInstruction(ir, newInstruction(OP_ARRAY_ASSIGN, temp, newIntAddress(i, src), newCharAddress(((char *)(value->as.data))[i], src)));
  }
  addInstruction(ir, newInstruction(OP_ARRAY_ASSIGN, temp, newIntAddress(value->size, src), newIntAddress(0, src)));
  return temp;
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
    return newIntAddress(node->as.value->as.integer, node->src);
  case T_CHAR:
    return newIntAddress(node->as.value->as.character, node->src);
  case T_FLOAT:
    return newFloatAddress(node->as.value->as.floating, node->src);
  case T_ARRAY:
    return stringAddress(node->as.value, node->src);
  default:
    printf("literal type not supported\n");
    exit(1);
  }
}
static Address *irFunctionDecl(Node *node)
{
  Node *funcSymNode = node->as.opr.operands[0];
  Address *funcAddr = functionAddress(funcSymNode->as.symbol, ir);
  addInstruction(ir, newInstruction(OP_FUNC, newIntAddress(funcSymNode->as.symbol->type->size, funcSymNode->src), NULL, funcAddr));

  Node *params = node->as.opr.operands[1];
  if (params)
  {
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
  }
  Node *funcBody = node->as.opr.operands[2];
  beginFunction();
  irNode(funcBody);
  freeFunctionAST(node);
  endFunction();
}
static Address *irSymbol(Node *node)
{
  return symbolAddress(node->as.symbol, ir);
}
static int readArrayInitialiser(IR *localIR, Node *arrList, Address *arrAddress)
{
#define ADD_ELEMENT()                                                                   \
  if (arrElement->type == NODE_OPR && arrElement->as.opr.type == OPR_LIST)              \
  {                                                                                     \
    numberOfElementsInit += readArrayInitialiser(localIR, arrElement, arrAddress);      \
  }                                                                                     \
  else                                                                                  \
  {                                                                                     \
    Address *initExprAddr = irNode(arrElement);                                         \
    addInstruction(localIR,                                                             \
                   newInstruction(OP_ARRAY_ASSIGN,                                      \
                                  arrAddress,                                           \
                                  newIntAddress(numberOfElementsInit, arrElement->src), \
                                  initExprAddr));                                       \
    numberOfElementsInit++;                                                             \
  }

  int numberOfElementsInit = 0;
  if (arrList == NULL)
    return 0;
  if (arrList->type == NODE_OPR && arrList->as.opr.type == OPR_LIST)
  {
    Node *arrElement = arrList->as.opr.operands[0];
    ADD_ELEMENT();
    arrElement = arrList->as.opr.operands[1];
    ADD_ELEMENT();
  }
  else
  {
    Node *arrElement = arrList;
    ADD_ELEMENT();
  }
  return numberOfElementsInit;
#undef ADD_ELEMENT
}
static int max(int a, int b)
{
  return a > b ? a : b;
}
static void arrayDeclaration(IR *localIR, Node *varInitialiser)
{
  Symbol *arrSymbol = varInitialiser->as.opr.operands[0]->as.symbol;
  Address *arrAddress = symbolAddress(arrSymbol, ir);
  Type *type = arrSymbol->type;
  TypeEnum baseType = getArrayBaseType(type);
  int elementSize = getHostSize(baseType);
  int arraySize = getArraySize(arrSymbol->type);
  printf("In array decl\n");
  Node *initExpr = varInitialiser->as.opr.operands[2];
  if (initExpr && initExpr->type == NODE_OPR && initExpr->as.opr.type == OPR_LIST)
  {
    printf("In array init\n");
    int numberOfElementsInit = readArrayInitialiser(localIR, varInitialiser->as.opr.operands[2], arrAddress);
    if (arraySize == 0 && numberOfElementsInit == 0)
    {
      // point_at_in_line(arrSymbol->src.line, arrSymbol->src.col, strlen(arrSymbol->name));
      compileError(varInitialiser->src, strlen(arrSymbol->name), "Array ('%s') size cannot be zero", arrSymbol->name);
    }
    else if (arraySize != 0 && arraySize < numberOfElementsInit)
    {
      compileError(varInitialiser->src, numberOfElementsInit * 2, "Excess elements in initializer for array '%s'", arrSymbol->name);
    }
    arraySize = max(arraySize, numberOfElementsInit);
    addInstruction(localIR,
                   newInstruction(OP_ARRAY_DECL,
                                  newIntAddress(arraySize, (Coordinate){0, 0, 0}),
                                  newIntAddress(elementSize, (Coordinate){0, 0, 0}),
                                  arrAddress));
  }
  else if (initExpr)
  {
    printf("in array assign\n");
    Address *initExprAddr = irNode(initExpr);
    addInstruction(localIR,
                   newInstruction(OP_ASSIGN,
                                  arrAddress,
                                  NULL,
                                  initExprAddr));
  }
  else
  {
    printf("in no init array\n");
    addInstruction(localIR,
                   newInstruction(OP_ARRAY_DECL,
                                  newIntAddress(arraySize, (Coordinate){0, 0, 0}),
                                  newIntAddress(elementSize, (Coordinate){0, 0, 0}),
                                  arrAddress));
  }
}
static Address *irVarDecl(Node *node)
{
#define ADD_VAR_DECL()                                                    \
  Address *left = irNode(varInitialiser->as.opr.operands[0]);             \
  Address *expr;                                                          \
  if (varInitialiser->as.opr.operands[1] != NULL)                         \
  {                                                                       \
    arrayDeclaration(localIR, varInitialiser);                            \
  }                                                                       \
  else                                                                    \
  {                                                                       \
    if (varInitialiser->as.opr.nops == 2)                                 \
    {                                                                     \
      expr = newIntAddress(0, (Coordinate){0, 0, 0});                     \
    }                                                                     \
    else                                                                  \
      expr = irNode(varInitialiser->as.opr.operands[2]);                  \
    addInstruction(localIR, newInstruction(OP_ASSIGN, expr, NULL, left)); \
  }
  //^ Second operand is the array specifier, so ignore
  printf("handling vr decl\n");
  Node *list = node->as.opr.operands[0];
  // Since we are going in reverse (actually should be depth first),
  // we need to store the instructions in an array
  // and then add them later in reverse order
  IR *localIR = newIR("ghost file");
  if (list->as.opr.type == OPR_LIST)
  {
    // single var assignment
    //   Node *varInitialiser = list;
    //   ADD_VAR_DECL();
    // }
    for (; list->as.opr.nops == 2 && list->as.opr.type == OPR_LIST; list = list->as.opr.operands[0])
    {
      Node *varInitialiser = list->as.opr.operands[1];
      ADD_VAR_DECL();
    }
  }
  Node *varInitialiser = list;
  ADD_VAR_DECL();
  // add instructions in reverse from localIR
  for (int i = localIR->size - 1; i >= 0; i--)
  {
    addInstruction(ir, &(localIR->instructions[i]));
  }
  printf("Adding back instructions\n");
#undef ADD_VAR_DECL
}
static Address *irAssign(Node *node)
{
  Address *left = irNode(node->as.opr.operands[0]);
  Address *right = irNode(node->as.opr.operands[1]);
  // no need to check type, it's already checked in semantic analysis
  addInstruction(ir, newInstruction(OP_ASSIGN, right, NULL, left));
}