#include "vm.h"
#include "../util/symbol.h"
#include "../backend/ir.h"
#include "../backend/built-in-functions.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
void point_at_in_line(int lineno, int from, int to);

VM vm;
hashmap *registers, *labels, *functions;

void initVM(IR *ir)
{
  vm.ir = ir;
  vm.ip = 0;
  registers = hashmap_create();
  labels = hashmap_create();
  functions = hashmap_create();
}

#define READ_INSTRUCTION() (vm.ir->instructions[vm.ip++])
#define IS_AT_END() (vm.ip >= vm.ir->size)
uintptr_t map[100];
int labelMap[100];
void store(int reg, uintptr_t value)
{
  map[reg] = value;
  // int a = reg;
  // int key[] = {a};
  // hashmap_set(registers, hashmap_static_arr(key), value);
}

uintptr_t load(int reg)
{
  return map[reg];
  uintptr_t value;
  int a = reg;
  int key[] = {a};
  int found = hashmap_get(registers, hashmap_static_arr(key), &value);
  printf("\t\t\t\tloading %d=%d, found=%d\n", reg, value, found);
  return value;
}

// Save a label and its ip
void saveLabel(Address *addr)
{
  labelMap[addr->id] = vm.ip - 1;
  printf("\t\t\t\t\t\t\t\t\tSaved label L%d ip=%d", addr->id, vm.ip - 1);
  // uintptr_t ip = vm.ip;
  // hashmap_set(labels, &(addr->id), sizeof(int), TO_UINTPTR(vm.ip - 1));
}
// Save a function and its ip
void saveFunction(Address *addr)
{
  uintptr_t ip = TO_UINTPTR(vm.ip);
  // printf("\tSaving function %d\n", addr->id);
  hashmap_set(functions, &(addr->id), sizeof(int), (vm.ip));
}
// Get the ip of a label
int getLabelIP(Address *addr)
{
  return labelMap[addr->id];
  // uintptr_t ip;
  // hashmap_get(labels, &(addr->id), sizeof(int), &ip);
  // return FROM_UINTPTR(ip, int);
}
// Get the ip of a function
// Returns -1 if function is not found.
int getFunctionIP(Address *addr)
{
  uintptr_t ip;
  int id = addr->id;
  // printf("\tgetting %d\n", id);
  if (!hashmap_get(functions, &(id), sizeof(int), &ip))
  {
    return -1;
  }
  return FROM_UINTPTR(ip, int);
}
uintptr_t getAddrValue(Address *addr)
{
  if (addr->isConstant)
  {
    switch (addr->type->op)
    {
    case T_INT:
      return TO_UINTPTR(addr->as.integer);
    case T_FLOAT:
      return TO_UINTPTR(addr->as.floating);
    case T_CHAR:
      printf("\t\t\t\t\t\tgetaddrvalue=%d\n", addr->as.character);
      return TO_UINTPTR(addr->as.character);
    default:
      runtimeError("Invalid constant type.");
    }
  }
  // printf("\t\t\t\t\t(id)getaddrvalue for %d=%ld\n", addr->id, load(addr->id));
  return load(addr->id);
}
int getAddrIntValue(Address *addr)
{
  uintptr_t temp = getAddrValue(addr);
  return FROM_UINTPTR(temp, int);
}
void push(Address *addr)
{
  VMValue *vmValue = malloc(sizeof(VMValue));
  if (!vmValue)
  {
    runtimeError("Out of memory.");
  }
  vmValue->value = getAddrValue(addr);
  vmValue->type = addr->type;
  vmValue->next = vm.stack;
  vm.stack = vmValue;
}
VMValue *pop()
{
  if (!vm.stack)
  {
    runtimeError("Stack underflow.");
  }
  VMValue *value = vm.stack;
  VMValue *next = vm.stack->next;
  // free(vm.stack);
  vm.stack = next;
  return value;
}
uintptr_t popValue()
{
  VMValue *v = pop();
  uintptr_t value = v->value;
  free(v);
  return value;
}
int stackLength()
{
  int length = 0;
  VMValue *v = vm.stack;
  while (v)
  {
    length++;
    v = v->next;
  }
  return length;
}
Address *mainFuncAddr = NULL;
void installLabelsAndFunctions()
{
  while (!IS_AT_END())
  {
    Instruction instruction = READ_INSTRUCTION();
    switch (instruction.op)
    {
    case OP_FUNC:
      saveFunction(instruction.result);
      if (strcmp("main", instruction.result->sym->name) == 0)
      {
        mainFuncAddr = instruction.result;
      }
      break;
    case OP_LABEL:
      saveLabel(instruction.result);
      break;
    }
  }
  if (!mainFuncAddr)
  {
    runtimeError("'main' function not defined.\n");
  }
}
Instruction currentInstruction;

void assignStatement();
void callFunction();
void returnStatement();
void mathOperation();
void arrayDeclaration();
void arrayAssign();
void arrayIndex();
void handleParam();

void executeGlobals()
{
  vm.ip = 0;
  while (!IS_AT_END())
  {
    currentInstruction = READ_INSTRUCTION();
    switch (currentInstruction.op)
    {
    case OP_ASSIGN:
      assignStatement();
      break;
    case OP_ARRAY_ASSIGN:
      arrayAssign();
      break;
    case OP_ARRAY_DECL:
      arrayDeclaration();
      break;

    case OP_FUNC:
      while ((currentInstruction = READ_INSTRUCTION()).op != OP_FUNC_END)
        ;
    case OP_LABEL:
      break;
    default:
      break;
    }
  }
}

Address *mainReturnValue;

void runVM()
{
  installLabelsAndFunctions();
  executeGlobals();
  // vm.ip = getFunctionIP(mainFuncAddr);
  mainReturnValue = newTempAddress(mainFuncAddr->type->type);
  currentInstruction = *newInstruction(OP_CALL, mainFuncAddr, newIntAddress0(0), mainReturnValue);
  for (; !(vm.ip > vm.ir->size); currentInstruction = READ_INSTRUCTION())
  {
    printf("\t\tat %d\n", vm.ip);
    switch (currentInstruction.op)
    {
    case OP_CALL:
      callFunction();
      break;
    case OP_ASSIGN:
      assignStatement();
      break;
    case OP_RETURN:
      returnStatement();
      break;
    case OP_ARRAY_DECL:
      arrayDeclaration();
      break;
    case OP_ARRAY_ASSIGN:
      arrayAssign();
      break;
    case OP_ARRAY_INDEX:
      arrayIndex();
      break;
    case OP_FUNC:
    case OP_LABEL:
      break;
    case OP_GOTO:
      vm.ip = getLabelIP(currentInstruction.result);
      break;
    case OP_IF_GOTO:
      if (getAddrIntValue(currentInstruction.arg1))
      {
        vm.ip = getLabelIP(currentInstruction.result);
      }
      break;
    case OP_IF_FALSE_GOTO:
      printf("yo here");
      if (!getAddrIntValue(currentInstruction.arg1))
      {
        vm.ip = getLabelIP(currentInstruction.result);
      }
      break;
    case OP_FUNC_END:
      runtimeError("Unexpected function end.");
    case OP_PARAM:
      handleParam();
      break;
    default:
      mathOperation();
      // runtimeError("Invalid instruction.");
      break;
    }
  }
  uintptr_t val = getAddrValue(mainReturnValue);
  printf("Main function returned: %d\n", FROM_UINTPTR(val, char));
}

void assignStatement()
{
  uintptr_t value = getAddrValue(currentInstruction.arg1);
  store(currentInstruction.result->id, getAddrValue(currentInstruction.arg1));
  currentInstruction.result->type->size = currentInstruction.arg1->type->size;
  currentInstruction.result->type->op = currentInstruction.arg1->type->op;
  currentInstruction.result->type->sym = currentInstruction.arg1->type->sym;
  currentInstruction.result->type->type = currentInstruction.arg1->type->type;
  // printf("\t\t\tGot assign size = %d for t%d", currentInstruction.result->type->size, currentInstruction.result->id);
}

void arrayIndex()
{
  Address *arr = currentInstruction.arg1;
  int offset = getAddrIntValue(currentInstruction.arg2);
  Address *target = currentInstruction.result;
  uintptr_t arrayBase = getAddrValue(arr);
  uintptr_t *arrBasePointer = FROM_UINTPTR(arrayBase, uintptr_t *);
  printf("Indexing t%d is symbol=%d\n", arr->id, arr->sym != NULL);
  if (offset >= arr->type->size || offset < 0)
  {
    runtimeMessage("Array index out of bounds-: " ANSI_COLOR_BOLD ANSI_COLOR_RED "(%d for size %d)\n" ANSI_COLOR_RESET, offset, arr->type->size);
    point_at_in_line(arr->src.line, arr->src.col, arr->type->sym->src.col + 2);
    exit(1);
  }
  uintptr_t value = arrBasePointer[offset];
  store(target->id, value);
}
void arrayAssign()
{
  Address *arr = currentInstruction.arg1;
  Address *offset = currentInstruction.arg2;
  Address *exprAddr = currentInstruction.result;
  uintptr_t arrayBase = getAddrValue(arr);
  uintptr_t *arrBasePointer = FROM_UINTPTR(arrayBase, uintptr_t *);
  int offsetInt = getAddrIntValue(offset);
  if (offsetInt >= arr->type->size || offsetInt < 0)
  {
    runtimeError("Array index out of bounds: " ANSI_COLOR_BOLD ANSI_COLOR_RED "(%d for size of %d)\n" ANSI_COLOR_RESET, offsetInt, arr->type->size);
  }
  arrBasePointer[offsetInt] = getAddrValue(exprAddr);
  printf("Successfully set %ld=%c\n", arrBasePointer[offsetInt], getAddrIntValue(exprAddr));
}
void arrayDeclaration()
{
  Address *arr = currentInstruction.result;
  int size = getAddrIntValue(currentInstruction.arg1);
  int ndims = getAddrIntValue(currentInstruction.arg2);
  uintptr_t *array = malloc(size * sizeof(uintptr_t));
  printf("Array type is %d and size is %d for t%d\n", getArrayBaseType(arr->type), currentInstruction.result->type->size, currentInstruction.result->id);
  arr->type->size = size;
  arr->type->type = newType(getArrayBaseType(arr->type));
  printf("Base pointer is %ld[0]= %d\n", TO_UINTPTR(array), array[0]);
  store(arr->id, TO_UINTPTR(array));
}

#define MATH_OPERATIONS(op)           \
  switch (op)                         \
  {                                   \
  case '+':                           \
    val = v1 + v2;                    \
    break;                            \
  case '-':                           \
    val = v1 - v2;                    \
    break;                            \
  case '*':                           \
    val = v1 * v2;                    \
    break;                            \
  case '/':                           \
    val = v1 / v2;                    \
    break;                            \
  case OPR_EQ:                        \
    val = (v1 == v2);                 \
    break;                            \
  case OPR_NE:                        \
    val = (v1 != v2);                 \
    break;                            \
  case OPR_GT:                        \
    val = (v1 > v2);                  \
    break;                            \
  case OPR_GE:                        \
    val = (v1 >= v2);                 \
    break;                            \
  case OPR_LT:                        \
    val = (v1 < v2);                  \
    break;                            \
  case OPR_LE:                        \
    val = (v1 <= v2);                 \
    break;                            \
  case OP_MINUS:                      \
    printf("\t\t\t\t\thuh\n");        \
    val = -v1;                        \
    break;                            \
  default:                            \
    runtimeError("Invalid operator"); \
  }
uintptr_t operateAsFloat(uintptr_t val1, uintptr_t val2, TypeEnum t1, TypeEnum t2, InstType op)
{
  float v1 = FROM_UINTPTR(val1, float);
  float v2 = FROM_UINTPTR(val2, float);
  if (t1 != T_FLOAT)
  {
    v1 = (float)(FROM_UINTPTR(val1, int));
  }
  if (t2 != T_FLOAT)
  {
    v2 = (float)(FROM_UINTPTR(val2, int));
  }
  float val;
  MATH_OPERATIONS(op);
  return TO_UINTPTR(val);
}
uintptr_t getMathResult()
{
  Address *arg1 = currentInstruction.arg1;
  Address *arg2 = currentInstruction.arg2;
  uintptr_t val1 = (arg1 ? getAddrValue(arg1) : 0);
  uintptr_t val2 = (arg2 ? getAddrValue(arg2) : 0);

  InstType op = currentInstruction.op;
  TypeEnum type = typeWiden(arg1->type->op, (arg2 ? arg2->type->op : T_FLOAT));
  if (type == T_FLOAT)
  {
    return operateAsFloat(val1, val2, arg1->type->op, (arg2 ? arg2->type->op : T_FLOAT), op);
  }
  int v1 = FROM_UINTPTR(val1, int);
  int v2 = FROM_UINTPTR(val2, int);
  uintptr_t val;
  switch (op)
  {
  case OPR_AND:
    val = v1 && v2;
    break;
  case OPR_OR:
    val = v1 || v2;
    break;
  case '!':
    val = !v1;
    break;
  default:
    MATH_OPERATIONS(op);
    break;
  }
  return val;
}
void mathOperation()
{
  uintptr_t res = getMathResult();
  store(currentInstruction.result->id, res);
}
void returnStatement()
{
  printf("\t stack has %d\n", stackLength());
  Address *returnValue = currentInstruction.arg1;
  uintptr_t val = popValue();
  int savedIp = FROM_UINTPTR(val, int);
  Instruction callInstruction = vm.ir->instructions[savedIp - 1];
  if (callInstruction.op == OP_CALL)
  {
    // printf("\t returning value %d to t%d\n", getAddrValue(returnValue), callInstruction.result->id);
    store(callInstruction.result->id, getAddrValue(returnValue));
  }
  {
    // else is the main function returning
    printf("\t returning value %d to t%d\n", getAddrValue(returnValue), mainReturnValue->id);
    store(mainReturnValue->id, getAddrValue(returnValue));
  }
  vm.ip = savedIp;
}
void handleParam()
{
  Instruction paramInstruction = currentInstruction;
  if (paramInstruction.arg1)
  {
    // this is a function argument to be passed
    push(currentInstruction.arg1);
  }
  else
  {
    runtimeError("Expected parameter.");
  }
}
void callFunction()
{
  int savedIp = vm.ip;
  int ip = getFunctionIP(currentInstruction.arg1);
  if (ip == -1)
  {
    printf("Calling native function\n");
    // vm.ip++;
    return dispatchNativeFunction(vm, currentInstruction);
  }
  vm.ip = ip;
  int n = getAddrIntValue(currentInstruction.arg2);
  printf("Calling function with %d params\n", n);
  while (n--)
  {
    Instruction paramIns = READ_INSTRUCTION();
    if (paramIns.op != OP_PARAM)
    {
      runtimeError("Expected parameter.");
    }
    Address *result = paramIns.result;
    store(result->id, popValue());
  }
  // push(currentInstruction.result);
  push(newIntAddress0(TO_UINTPTR(savedIp)));
}

#define WRITE_MESSAGE()                                                               \
  va_list args;                                                                       \
  va_start(args, message);                                                            \
  fprintf(stderr, ANSI_COLOR_BOLD ANSI_COLOR_RED "Runtime Error: " ANSI_COLOR_RESET); \
  vfprintf(stderr, message, args);

void runtimeError(char *message, ...)
{
  WRITE_MESSAGE();
  exit(1);
}
void runtimeMessage(char *message, ...)
{
  WRITE_MESSAGE();
}