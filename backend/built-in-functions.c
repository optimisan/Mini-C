#include "built-in-functions.h"
#include "../util/symbol.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void installBuiltInFunctions(SymbolTable *table)
{
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
  // printf("printf type is %d\n", funcSym->type->op);
}

void dispatchNativeFunction(VM vm, Instruction callInstruction)
{
  uintptr_t params = getAddrValue(callInstruction.arg2);
  printf("Executing native with nparams: %d\n", FROM_UINTPTR(params, int));
  while (FROM_UINTPTR(params, int) > 0)
  {
    VMValue *param = pop();
    printf("\t\t\tType of param is %d, size=%d \n", param->type->op, param->type->size);
    if (param->type->op == T_ARRAY)
    {
      printf("\t\t\t\t");
      uintptr_t arrVal = param->value;
      uintptr_t *arrBase = FROM_UINTPTR(arrVal, uintptr_t *);
      for (int i = 0; i < param->type->size; i++)
      {
        printf("%c", FROM_UINTPTR(arrBase[i], char));
      }
      printf("\n");
    }
    params--;
  }
}