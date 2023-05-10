#include "../util/AST.h"
#include "../util/symbol.h"
#include "../util/token.h"
#include "ir.h"
#include "irgen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void compileError(Coordinate pos, int lexemeLength, char *format, ...);
// The current IR being generated
IR *ir;
// Since function declarations cannot nest,
// we only need to keep track of the current function
Address *currentFunction = NULL;
// But control statements can nest,
// hence there is a linked list of control blocks
typedef struct ControlBlock
{
  Address *breakLabel;
  Address *continueLabel;
  struct ControlBlock *enclosing;
} ControlBlock;

ControlBlock *currentControlBlock = NULL;

static void newControlBlock(Address *s, Address *e)
{
  ControlBlock *cb = malloc(sizeof(ControlBlock));
  cb->continueLabel = s;
  cb->breakLabel = e;
  cb->enclosing = currentControlBlock;
  currentControlBlock = cb;
}
static void endControlBlock()
{
  ControlBlock *cb = currentControlBlock;
  currentControlBlock = currentControlBlock->enclosing;
  free(cb);
}

static Address *irNode(Node *node);

/**
 * @brief Generate IR for the given AST
 *
 * @param rootNode AST root node `program`
 * @param sourceFilename For error reporting
 * @return IR*
 */
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
static Address *irBreak(Node *node);
static Address *irContinue(Node *node);
static Address *irArrayExpr(Node *node);
/**
 * @brief Generate IR for a node. Calls the appropriate
 * function based on node type.
 *
 * @return Address* Returns the node's address (can be a variable or function address)
 */
static Address *irNode(Node *node)
{
  if (node == NULL)
    return NULL;
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
    case OPR_BREAK:
      irBreak(node);
      break;
    case OPR_CONTINUE:
      irContinue(node);
      break;
    case '[':
      return irArrayExpr(node);
    case OPR_RETURN:
      addInstruction(ir, newInstruction(OP_RETURN, irNode(node->as.opr.operands[0]), NULL, NULL));
      currentFunction = NULL;
      break;
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
static Address *irBreak(Node *node)
{
  if (!currentControlBlock)
  {
    compileError(node->src, 5, "Break statement not within loop or switch");
    return NULL;
  }
  addInstruction(ir, newInstruction(OP_GOTO, NULL, NULL, currentControlBlock->breakLabel));
  return NULL;
}
static Address *irContinue(Node *node)
{
  if (!currentControlBlock)
  {
    compileError(node->src, 5, "Continue statement not within loop or switch");
    return NULL;
  }
  addInstruction(ir, newInstruction(OP_GOTO, NULL, NULL, currentControlBlock->continueLabel));
  return NULL;
}
// For statement
static Address *irFor(Node *node)
{
  Address *startLabel = newLabelAddress();
  Address *endLabel = newLabelAddress();
  Address *continueLabel = newLabelAddress();
  newControlBlock(continueLabel, endLabel);
  irNode(node->as.opr.operands[0]);
  addInstruction(ir, newInstruction(OP_LABEL, NULL, NULL, startLabel));
  Address *condition = irNode(node->as.opr.operands[1]);
  if (!condition)
  {
    condition = newIntAddress0(1);
  }
  addInstruction(ir, newInstruction(OP_IF_FALSE_GOTO, condition, NULL, endLabel));
  irNode(node->as.opr.operands[3]);
  addInstruction(ir, newInstruction(OP_LABEL, NULL, NULL, continueLabel));
  irNode(node->as.opr.operands[2]);
  addInstruction(ir, newInstruction(OP_GOTO, NULL, NULL, startLabel));
  addInstruction(ir, newInstruction(OP_LABEL, NULL, NULL, endLabel));
  endControlBlock();
  return NULL;
}

static Address *irWhile(Node *node)
{
  Address *startLabel = newLabelAddress();
  Address *endLabel = newLabelAddress();
  newControlBlock(startLabel, endLabel);
  addInstruction(ir, newInstruction(OP_LABEL, NULL, NULL, startLabel));
  Address *condition = irNode(node->as.opr.operands[0]);
  addInstruction(ir, newInstruction(OP_IF_FALSE_GOTO, condition, NULL, endLabel));
  irNode(node->as.opr.operands[1]);
  addInstruction(ir, newInstruction(OP_GOTO, NULL, NULL, startLabel));
  addInstruction(ir, newInstruction(OP_LABEL, NULL, NULL, endLabel));
  endControlBlock();
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
/**
 * @brief Generate a function call
 *
 * There are two parts to a function:
 * 1. The parameters
 * Parameters are generated in reverse order, right to left is
 * top to down.
 * The parameter instruction is [OP_PARAM address null null]
 * Example:
 *      f(a, b, c) will generate parameters as:
 *      OP_PARAM c
 *      OP_PARAM b
 *      OP_PARAM a
 *
 * 2. The function call
 * The instruction for a call is as follows:
 * [OP_CALL funcAddress numParameters returnAddress]
 *
 * Example:
 *      temp = f(a, b, c) will generate the call as:
 *      OP_CALL f 3 temp
 *
 * Even if the function's return value is not assigned to anything,
 * a temporary return address created is still passed to the function call.
 * This is used to get the return address from the main function.
 *
 * @param node
 * @return Address*
 */
static Address *irFuncCall(Node *node)
{
  // generate the parameters
  Node *params = node->as.opr.operands[1];
  int nparams = 0;
  // since this is generating while traversing deeper,
  // the parameters are generated in reverse order (right to left)
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
  // printf("\t nparams %d\n", nparams);
  Symbol *sym = node->as.opr.operands[0]->as.symbol;
  Address *temp = newTempAddress(sym->type->type);
  Address *symAddr = symbolAddress(sym, ir);
  addInstruction(ir, newInstruction(OP_CALL, symAddr, newIntAddress(nparams, node->src), temp));
  return temp;
}
/**
 * Each `getArrayIndexOffset` returns two values:
 * 1. The offset from the base operand of the array expression,
 * 2. The size of the array element after 1 dereference.
 *
 */
typedef struct
{
  Address *offset;
  int size;
} ArrayInfo;
/**
 * @brief Calculates the rolled-out array index offset
 *
 * This function is called with an array_index node, whose opr is '['
 * An array_index node is for an array expression. It can be an rvalue
 * or an lvalue (for an assignment or an expression, respectively).
 *
 * Example:
 * int val = arr[3][4]; has 'arr[3][4]' as an lvalue array_index node
 * arr[2][3] = val; has 'arr[2][3]' as an rvalue array_index node
 *
 * The AST for arr[3][4] is like so:
 * array_index (
 *      array_index (
 *         symbol (arr)
 *         int (3)
 *      )
 *    int (4)
 * )
 * The array size information rests with the symbol within, from which the offset
 * is calculated. Since only the symbol's type contains the whole array size,
 * other expressions cannot be used as array base pointers because
 * the type of an expression is stored as a stripped down version of the original type.
 * Specifically, the expression's exprType only has the op as Array and the total
 * size as argument, not the individual dimension sizes.
 *
 * This function does not deal with the base symbol of the array. It must be passed in.
 *
 * -----------------------------------------------------
 *
 * **CALCULATING OFFSET**
 *
 * Consider the array `arr`
 *    ->  int arr[4][5]
 * Let us take a look at the offset for the array expression:
 *    ->  arr[2][3]
 *
 * It is helpful to think of it the "C" way.
 * The 2D indexing is desugared to pointer arithmetic by C like so:
 *                    *(*(arr + 2) + 3)
 * Assume that arr is 0.
 * This pointer arithmetic reduces as follows:
 *       1) arr + 2 = arr + 2*sizeof(arr) = (arr + 2)*5 = (0 + 2)*5 = 10, since a row has 5 elements and arr is 0
 *       2) ((10) + 3)*(sizeof(arr[2])) = 13, taking the size of integer to be 1
 * Finally, *(arr + 13) is the end element being addressed (not the _byte_).
 *
 * The 2D case is a special case of the general nD case. Here is a 3D example:
 *  [Decl]      -> int arr[4][5][6];
 *  [ArrayExpr] -> arr[1][2][3] = 24;
 *
 * It is even more beneficial to look at it from the "functional" perspective.
 * Each dereference operator is a function that returns
 * the local array size of what it is dereferencing. For example,
 *
 * Consider -> int arr[4][5][6];
 *  and let -> arr[1][2][3] be the expression:
 *                *(arr + 1) returns size(arr[1]) = 5, because arr[1] is an array of 5 elements.
 *          > [The 5 elements are themselves arrays]
 *                *(*(arr + 1) + 2) returns size as size(arr[1][2]) = 6, because arr[1][2] is an
 *                                        array of 6 elements.
 *
 * The dereference function also returns the offset it calculates, based on the size of its *operand*.
 *
 *               *(arr + 1) has the operand as `arr` and returns sizeof(arr)*1 + offset(arr) as the offset
 *
 * We take the base symbol `arr` as the base operand, with size as 1. This gives us the offset
 * in terms of *elements*, not bytes.
 *
 * The high level view of this dereference function is:
 *
 *   DEREFERENCE (base, offset):
 *      baseSize   := DEREFERENCE(base)->size
 *      baseOffset := DEREFERENCE(base)->offset
 *      return {
 *        size   := DEREFERENCED_SIZE(base)
 *        offset := baseOffset*baseSize + offset
 *      }
 * But how do we find `DEREFERENCED_SIZE(base)`? Luckily, the `Type*` structure is
 * what we need in times of support. Since a `Type` links to the type of the
 * array's element type, we can just keep going down the `Type` list for
 * every `DEREFERENCE` call. More explanation is in the function definition below.
 *
 * -----------------------------------------------------
 * **LASTLY**
 *
 * If you haven't noticed already, the first dimension is not used
 * anywhere to calculate the true offset. The first dimension only contributes to the
 * total size of the array. This is why the first dimension can be empty in an
 * array declaration. Below is an example.
 *
 * For every dimension index, it is multiplied with the size of the dimensions
 * following it.
 *              [Decl] arr  [?]      [5]      [6] ;
 *              [Expr] arr  [1]      [2]      [3] ;
 *                         *(5*6) + *(6)  +  *(1) ;
 *
 * @param arrIndex
 * @param type The type of the array
 * @return ArrayInfo
 */
static ArrayInfo getArrayIndexOffset(Node *arrIndex, Type *type)
{
  /**
   * The AST for arr[3][4] is like so:
   * array_index (
   *      array_index (   <--- firstElement
   *         symbol (arr) <--- firstElement
   *         int (3)      <--- operands[1]
   *      )
   *    int (4)           <--- operands[1]
   * )
   *
   */
  Node *firstElement = arrIndex->as.opr.operands[0];
  if (firstElement->type == NODE_SYMBOL)
  {
    // base case, refers to `symbol(arr)` above.
    // The size is 1, because we want the element offset, not the byte offset.
    return (ArrayInfo){irNode(arrIndex->as.opr.operands[1]), 1 /* , getHostSize(type->type->op) */};
  }
  // Sanity check
  if (arrIndex->type != NODE_OPR || arrIndex->as.opr.type != '[')
  {
    // should never happen. This is just a sanity check
    printf("Error: Expected array index\n");
    exit(1);
  }
  else
  {
    // printf("Outer type size if %d and inner is %d\n", type->size, type->type->size);
    // second element is the index offset at this level
    Address *currentOffset = irNode(arrIndex->as.opr.operands[1]); // 24
    // get the inner array info
    // Consider we are at *(*(arr+1) + 2), where currentOffset is 2
    // innerInfo corresponds to evaluating *(arr+1)
    // Notice that the type we pass is the DEREFERENCED type, not the type of the current array
    ArrayInfo innerInfo = getArrayIndexOffset(arrIndex->as.opr.operands[0], type->type); // 12, 1
    Address *temp = newTempAddress(newType(T_INT));
    addInstruction(ir, newInstruction('*', newIntAddress(type->size, arrIndex->src), innerInfo.offset, temp));
    addInstruction(ir, newInstruction('+', temp, currentOffset, temp));
    return (ArrayInfo){temp, innerInfo.size * type->size};
  }
}
static Symbol *getArrayBase(Node *arrIndex)
{
  // printf("Getting array base for type %d\n", arrIndex->as.opr.type == '[');
  while (arrIndex->type == NODE_OPR && arrIndex->as.opr.type == '[')
  {
    arrIndex = arrIndex->as.opr.operands[0];
  }
  if (arrIndex->type == NODE_SYMBOL)
  {
    return arrIndex->as.symbol;
  }
  else
  {
    compileError(arrIndex->src, 1, "Only symbols are supported as arrays. Need a different architecture to support other types.");
  }
}
/**
 * @brief Add an array indexing instruction (can be index expr rval or assign expr lval)
 *
 * Extracts the base array symbol, gets the offset and builds the temporary address
 * with a toned-down type, if `result` is NULL.
 *
 * @param node
 * @param opType The operation to use for the array index. This is one of OP_ARRAY_INDEX and OP_ARRAY_ASSIGN
 * @param result
 * @return Address*
 */
static Address *indexArrayWithOpAs(Node *node, InstType opType, Address *result)
{
  Symbol *sym = getArrayBase(node);
  ArrayInfo arrInfo = getArrayIndexOffset(node, sym->type);
  Address *offset = arrInfo.offset;
  Address *base = symbolAddress(sym, ir);
  if (!result)
  {
    result = newTempAddress(sym->type);
    result->type->size = getArraySize(sym->type);
    result->type->op = getArrayBaseType(sym->type);
    // printf("Setting base type =%d\n", result->type->op);
  }
  // addInstruction(ir, newInstruction('*', newIntAddress(getHostSize(getArrayBaseType(sym->type)), node->src), offset, offset));
  addInstruction(ir, newInstruction(opType, base, offset, result));
  return result;
}
static Address *irArrayExpr(Node *node)
{
  return indexArrayWithOpAs(node, OP_ARRAY_INDEX, NULL);
}
static Address *irExpr(Node *node)
{
  if (node->as.opr.nops == 1)
  {
    Address *temp = newTempAddress(newType(node->exprType.op));
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
    // printf("got binary expr %d\n", node->as.opr.operands[0]->type);
    Address *left = irNode(node->as.opr.operands[0]);
    Address *right = irNode(node->as.opr.operands[1]);
    Address *temp = newTempAddress(newType(node->exprType.op));
    // printf("got left as %d", left == NULL);
    addInstruction(ir, newInstruction(node->as.opr.type, left, right, temp));
    return temp;
  }
  printf("invalid expression\n");
  exit(1);
}
static Address *stringAddress(Value *value, Coordinate src)
{
  // Type *elementType = newType(value->type);
  Type *type = newType(T_ARRAY);
  type->size = value->size + 1;
  type->type = newType(T_CHAR);
  Address *temp = newTempAddress(type);
  // value->type = type;
  // printf("Adding string address for %s, size=%d\n", "", value->type);
  int eleSize = getHostSize(T_CHAR);
  addInstruction(ir, newInstruction(OP_ARRAY_DECL, newIntAddress(value->size + 1, src), newIntAddress(eleSize, src), temp));
  for (int i = 0; i < value->size; i++)
  {
    addInstruction(ir, newInstruction(OP_ARRAY_ASSIGN, temp, newIntAddress(i * eleSize, src), newCharAddress(((char *)(value->as.data))[i], src)));
  }
  addInstruction(ir, newInstruction(OP_ARRAY_ASSIGN, temp, newIntAddress(value->size * eleSize, src), newIntAddress(0, src)));
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
    return newCharAddress(node->as.value->as.character, node->src);
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
  currentFunction = funcAddr;
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
  if (currentFunction)
  {
    compileError(funcSymNode->as.symbol->src, strlen(currentFunction->sym->name), "Function %s has no return statement", currentFunction->sym->name);
  }
  addInstruction(ir, newInstruction(OP_FUNC_END, NULL, NULL, NULL));
  endFunction();
}
static Address *irSymbol(Node *node)
{
  return symbolAddress(node->as.symbol, ir);
}
static int readArrayInitialiser(IR *localIR, Node *arrList, Address *arrAddress, int elementSize, int startingIndex)
{
#define ADD_ELEMENT()                                                                                                 \
  if (arrElement->type == NODE_OPR && arrElement->as.opr.type == OPR_LIST)                                            \
  {                                                                                                                   \
    numberOfElementsInit += readArrayInitialiser(localIR, arrElement, arrAddress, elementSize, numberOfElementsInit); \
  }                                                                                                                   \
  else                                                                                                                \
  {                                                                                                                   \
    Address *initExprAddr = irNode(arrElement);                                                                       \
    addInstruction(localIR,                                                                                           \
                   newInstruction(OP_ARRAY_ASSIGN,                                                                    \
                                  arrAddress,                                                                         \
                                  newIntAddress(numberOfElementsInit + startingIndex,                                 \
                                                /*  *elementSize, */ arrElement->src),                                \
                                  initExprAddr));                                                                     \
    numberOfElementsInit++;                                                                                           \
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
static int getArrayNumberOfDimensions(Type *type)
{
  int ndim = 0;
  while (type->op == T_ARRAY)
  {
    ndim++;
    type = type->type;
  }
  return ndim;
}
static int addArrayDimensionSizes(IR *localIR, Type *type)
{
  int ndim = 0;
  if (type->op == T_ARRAY)
  {
    // addInstruction(localIR, newInstruction(OP_ASSIGN, newIntAddress(type->size, (Coordinate){0, 0}), NULL, NULL));
    return addArrayDimensionSizes(localIR, type->type) + 1;
  }
  else
  {
    // addInstruction(localIR, newInstruction(OP_ASSIGN, newIntAddress(getHostSize(type->op), (Coordinate){0, 0}), NULL, NULL));
    return 1;
  }
}
static int arrayIsDynamic(Type *type)
{
  // if the array is dynamic, it will have a dimension size of 0
  while (type->type)
  {
    type = type->type;
  }
  return type->size == 0;
}
static void arrayDeclaration(IR *localIR, Node *varInitialiser)
{
#define ADD_ARRAY_DIMS()                                                                                          \
  addInstruction(localIR, newInstruction(OP_ASSIGN, newIntAddress(elementSize, (Coordinate){0, 0}), NULL, NULL)); \
  ndim = addArrayDimensionSizes(localIR, type);

  Symbol *arrSymbol = varInitialiser->as.opr.operands[0]->as.symbol;
  Address *arrAddress = symbolAddress(arrSymbol, ir);
  Type *type = arrSymbol->type;
  TypeEnum baseType = getArrayBaseType(type);
  int elementSize = getHostSize(baseType);
  int arraySize = getArraySize(arrSymbol->type);
  // printf("In array decl\n");
  Node *initExpr = varInitialiser->as.opr.operands[2];
  int ndim = 0;
  if (initExpr && initExpr->type == NODE_OPR && initExpr->as.opr.type == OPR_LIST)
  {
    int numberOfElementsInit = readArrayInitialiser(localIR, varInitialiser->as.opr.operands[2], arrAddress, elementSize, 0);
    if (arraySize == 0 && numberOfElementsInit == 0)
    {
      compileError(varInitialiser->src, strlen(arrSymbol->name), "Array ('%s') size cannot be zero", arrSymbol->name);
    }
    else if (arraySize != 0 && arraySize < numberOfElementsInit && !arrayIsDynamic(type))
    {
      compileError(varInitialiser->src, numberOfElementsInit * 2, "Excess elements in initializer for array '%s'", arrSymbol->name);
    }
    arraySize = max(arraySize, numberOfElementsInit);
    arrAddress->type = type;
    // printf("\t\t\t\tIn array init %d\n", symbolAddress(arrSymbol, ir)->type->size);

    // ADD_ARRAY_DIMS();
    addInstruction(localIR,
                   newInstruction(OP_ARRAY_DECL,
                                  newIntAddress0(arraySize),
                                  newIntAddress0(elementSize),
                                  arrAddress));
  }
  else if (initExpr)
  {
    Address *initExprAddr = irNode(initExpr);
    symbolAddress(arrSymbol, ir)->type = initExprAddr->type;
    // printf("in array assign with size as %d\n", symbolAddress(arrSymbol, ir)->type->size);
    if (initExpr->type == NODE_LITERAL && initExpr->as.value->type == T_ARRAY)
    {
      addInstruction(localIR, newInstruction(OP_ASSIGN, initExprAddr, NULL, arrAddress));
      // addInstruction(localIR, newInstruction(OP_ARRAY_DECL, newIntAddress0(initExprAddr->type->size), newIntAddress0(elementSize), arrAddress));
      return;
    }
    if (initExpr->type == NODE_OPR && initExpr->as.opr.type != OPR_LIST)
    {
      addInstruction(localIR, newInstruction(OP_ASSIGN, initExprAddr, NULL, arrAddress));
      return;
    }
    if (initExpr->type != NODE_OPR || (initExpr->type == NODE_OPR && initExpr->as.opr.type != OPR_LIST))
      addInstruction(localIR,
                     newInstruction(OP_ARRAY_ASSIGN,
                                    arrAddress,
                                    newIntAddress0(0),
                                    initExprAddr));
    addInstruction(localIR,
                   newInstruction(OP_ARRAY_DECL,
                                  newIntAddress0(arraySize),
                                  newIntAddress0(elementSize),
                                  arrAddress));
  }
  else
  {
    // printf("in no init array\n");
    int ndim = addArrayDimensionSizes(localIR, type);
    if (arrayIsDynamic(type))
    {
      compileError(varInitialiser->src, strlen(arrSymbol->name), "Array ('%s') size cannot be zero.\n" ANSI_COLOR_BLUE "Either specify all dimensions or use a initialiser list." ANSI_COLOR_RESET, arrSymbol->name);
    }
    // ADD_ARRAY_DIMS();
    addInstruction(localIR,
                   newInstruction(OP_ARRAY_DECL,
                                  newIntAddress0(arraySize),
                                  newIntAddress0(ndim),
                                  arrAddress));
  }
#undef ADD_ARRAY_DIMS
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
  // printf("handling vr decl\n");
  Node *list = node->as.opr.operands[0];
  // Since we are going in reverse (actually should be depth first),
  // we need to store the instructions in an array
  // and then add them later in reverse order
  IR *localIR = newIR("ghost file");
  if (list->as.opr.type == OPR_LIST)
  {
    // single var assignment
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
  // printf("Adding back instructions\n");
#undef ADD_VAR_DECL
}
static Address *irAssign(Node *node)
{
  Address *right = irNode(node->as.opr.operands[1]);
  if (node->as.opr.operands[0]->type == NODE_OPR && node->as.opr.operands[0]->as.opr.type == '[')
  {
    // left is an array
    return indexArrayWithOpAs(node->as.opr.operands[0], OP_ARRAY_ASSIGN, right);
  }
  Address *left = irNode(node->as.opr.operands[0]);
  // no need to check type, it's already checked in semantic analysis
  addInstruction(ir, newInstruction(OP_ASSIGN, right, NULL, left));
}