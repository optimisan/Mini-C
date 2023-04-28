#include "built-in-functions.h"
#include "../util/symbol.h"
#include <inttypes.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/time.h>

void point_at_in_line(int lineno, int from, int to);
void printfFunction(VMValue **params, int n);
void secondsSinceEpoch(VMValue **params, int n);

hashmap *functionMap;

void installFunction(SymbolTable *table, void *nativeCode, char *name, int variadic, Type *returnType, int nparams, ...)
{
  // char *nameCopy = malloc(strlen(name) + 1);
  // strcpy(nameCopy, name);
  Symbol *funcSymbol = install(name, &table, S_GLOBAL - 1, (Coordinate){0, 0, 0});
  Type *type = newType(T_FUNCTION);
  type->variadicFunc = variadic;
  type->size = nparams;
  type->proto = malloc(sizeof(Type) * nparams);
  type->type = returnType;
  va_list args;
  va_start(args, nparams);
  for (int i = 0; i < nparams; i++)
  {
    type->proto[i] = va_arg(args, Type *);
  }
  va_end(args);
  funcSymbol->type = type;
  hashmap_set(functionMap, name, strlen(name), nativeCode);
}

void installBuiltInFunctions(SymbolTable *table)
{
  functionMap = hashmap_create();

  /*
  Install system functions
  */
  // 1. printf
  Type *formatType = newType(T_ARRAY);
  formatType->size = 1;
  formatType->type = newType(T_CHAR);
  installFunction(table, (void *)printfFunction, "printf", 1, newType(T_INT), 1, formatType);

  // 2. time: secondsSinceEpoch
  installFunction(table, (void *)secondsSinceEpoch, "time", 0, newType(T_INT), 0);
  // Symbol *funcSym = install("printf", &table, S_GLOBAL - 1, (Coordinate){0, 0, 0});
  // Type *type = newType(T_FUNCTION);
  // type->variadicFunc = 1;
  // type->size = 1;
  // type->proto = malloc(sizeof(Type) * 2);
  // type->proto[0] = newType(T_ARRAY);
  // type->proto[0]->type = newType(T_CHAR);
  // type->proto[0]->size = 1;
  // type->type = newType(T_INT);
  // funcSym->type = type;

  // hashmap_set(functionMap, "printf", strlen("printf"), (void *)printfFunction);
  // printf("printf type is %d\n", funcSym->type->op);
}
#define RETURN_VALUE(val) store(callInstruction.result->id, TO_UINTPTR(val));

#define GET_STACK_PARAMS(n, arr) \
  for (int i = 0; i < n; i++)    \
  {                              \
    arr[i] = pop();              \
  }

Instruction callInstruction;

void dispatchNativeFunction(VM vm, Instruction ci)
{
  callInstruction = ci;
  int nparams = getAddrIntValue(callInstruction.arg2);
  VMValue *params[nparams];
  GET_STACK_PARAMS(nparams, params);
  uintptr_t func;
  int res = hashmap_get(functionMap, (callInstruction.arg1->sym->name), strlen((callInstruction.arg1->sym->name)), &func);
  void (*f)(VMValue **, int) = (void *)func;
  f(params, nparams);
}

int printValueString(uintptr_t arr)
{
  uintptr_t *arrBase = FROM_UINTPTR(arr, uintptr_t *);
  int i = 0;
  while ((*arrBase) != 0)
  {
    i += printf("%c", FROM_UINTPTR(*arrBase, char));
    arrBase++;
  }
  return i;
}

void printfFunction(VMValue **params, int n)
{
#define CHECK(n)                                         \
  if (n < 0)                                             \
  {                                                      \
    runtimeError("Insufficient arguments for printf\n"); \
  }

  if (n == 0)
  {
    runtimeMessage("printf called with no arguments %d\n", params[0]->type->sym == NULL);
    point_at_in_line(params[0]->type->lineno, 0, 6);
    exit(1);
  }
  VMValue *formatV = params[0];
  n--;
  if (formatV->type->op != T_ARRAY)
  {
    runtimeMessage("Expected a (char[]) type string parameter\n");
    point_at_in_line(formatV->src.line - 1, formatV->src.col - 1, formatV->src.col + 6);
    exit(1);
  }
  uintptr_t *ptr = FROM_UINTPTR(formatV->value, uintptr_t *);
  uintptr_t *base = ptr;
  int written = 0;
  params++;
  for (; FROM_UINTPTR(*ptr, char) != 0; ptr++)
  {
    char c = FROM_UINTPTR(*ptr, char);
    if (c == '%')
    {
      ptr++;
      c = FROM_UINTPTR(*ptr, char);
      switch (c)
      {
      case 0:
        RETURN_VALUE(written);
        return;
      case 's':
      {
        n--;
        CHECK(n);
        VMValue *stringValue = *(params++);
        if (stringValue->type->op != T_ARRAY)
        {
          runtimeMessage("printf called with non-string argument\n");
          point_at_in_line(stringValue->src.line - 1, stringValue->src.col - 1, stringValue->src.col + 6);
          exit(1);
        }
        written += printValueString(stringValue->value);
        break;
      }
      case 'd':
      {
        n--;
        CHECK(n);
        VMValue *param = *(params++);
        if (param->type->op != T_INT)
        {
          runtimeMessage("printf called with non-int argument%d\n", param->type->op);
          point_at_in_line(param->src.line - 1, param->src.col - 1, param->src.col + 6);
          exit(1);
        }
        written += printf("%d", FROM_UINTPTR(param->value, int));
        break;
      }
      case 'f':
      {
        n--;
        CHECK(n);
        VMValue *param = *(params++);
        if (param->type->op != T_FLOAT)
        {
          runtimeMessage("printf called with non-float argument\n");
          point_at_in_line(param->src.line - 1, param->src.col - 1, param->src.col + 6);
          exit(1);
        }
        written += printf("%f", FROM_UINTPTR(param->value, float));
        break;
      }
      case 'c':
      {
        n--;
        CHECK(n);
        VMValue *param = *(params++);
        if (param->type->op != T_CHAR)
        {
          runtimeMessage("Expected a character parameter in printf\n");
          point_at_in_line(param->src.line - 1, param->src.col - 1, param->src.col + 6);
          if (param->type->op != T_INT)
            exit(1);
        }
        written += printf("%c", FROM_UINTPTR(param->value, int));
        break;
      }
      default:
      {
        runtimeMessage("Invalid format specifier %c\n", c);
        point_at_in_line(formatV->src.line - 1, formatV->src.col - 1, formatV->src.col + (ptr - base) + 1);
      }
      }
    }
    else
    {
      written += printf("%c", c);
    }
  }
  if (n > 0)
  {
    runtimeMessage("Extra parameters to printf\n");
    // point_at_in_line((*params)->src.line - 1, (*params)->src.col - 1, (*params)->src.col + 3);
  }
  RETURN_VALUE(written);
}

void secondsSinceEpoch(VMValue **params, int n)
{
  struct timeval te;
  gettimeofday(&te, NULL);                                         // get current time
  long long milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000; // calculate milliseconds
  // printf("milliseconds: %lld\n", milliseconds);
  // return milliseconds;
  int ms = (int)milliseconds;
  RETURN_VALUE(ms);
  // RETURN_VALUE(sec_microsecs);
}