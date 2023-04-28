#include "built-in-functions.h"
#include "../util/symbol.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
void point_at_in_line(int lineno, int from, int to);
void printfFunction(VMValue **params, int n);

hashmap *functionMap;
void installBuiltInFunctions(SymbolTable *table)
{
  functionMap = hashmap_create();

  Symbol *funcSym = install("printf", &table, S_GLOBAL - 1, (Coordinate){0, 0, 0});
  Type *type = newType(T_FUNCTION);
  type->variadicFunc = 1;
  type->size = 1;
  type->proto = malloc(sizeof(Type) * 2);
  type->proto[0] = newType(T_ARRAY);
  type->proto[0]->type = newType(T_CHAR);
  type->proto[0]->size = 1;
  type->type = newType(T_INT);
  funcSym->type = type;

  hashmap_set(functionMap, "printf", strlen("printf"), (void *)printfFunction);
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

void printfFunction(VMValue **params, int n)
{
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
    runtimeMessage("printf called with non-string argument%d\n", formatV->src.col);
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
      case 'd':
      {
        VMValue *param = *(params++);
        n--;
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
        VMValue *param = *(params++);
        n--;
        if (param->type->op != T_FLOAT)
        {
          runtimeMessage("printf called with non-float argument%d\n", param->src.col);
          point_at_in_line(param->src.line - 1, param->src.col - 1, param->src.col + 6);
          exit(1);
        }
        written += printf("%f", FROM_UINTPTR(param->value, float));
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
    runtimeMessage("Extra parameters to printf %d\n", params[0]->src.line);
    point_at_in_line((*params)->src.line - 1, (*params)->src.col - 1, (*params)->src.col + 3);
  }
  RETURN_VALUE(written);
}