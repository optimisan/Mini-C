#include "built-in-functions.h"
#include "../util/symbol.h"
#include <inttypes.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/time.h>
#include <regex.h>
#include <time.h>

// This is from `tokenizer.l`
void point_at_in_line(int lineno, int from, int to);

/**
 * These are all the built in functions
 *
 * Before calling a function, the parameters are pushed to the stack
 * as instances of `VMValue`. The function is then called with the
 * parameters as an array of `VMValue*` and the number of parameters.
 *
 */

void printfFunction(VMValue **params, int n);
void secondsSinceEpoch(VMValue **params, int n);
void regexMatch(VMValue **params, int n);
void randomInt(VMValue **params, int n);
void scanInt(VMValue **params, int n);
void scanFloat(VMValue **params, int n);
void scanChar(VMValue **params, int n);
void scanString(VMValue **params, int n);
void exitFunction(VMValue **params, int n);

extern Address *mainReturnValue;
extern VM vm;

hashmap *functionMap;

/**
 * @brief Installs the built in function in the Symbol Table
 *
 * @param table The symbol table
 * @param nativeCode Function pointer in C. This accepts a pointer to VMValue*'s and the number of arguments.
 * @param name The name of the function
 * @param variadic If the function is variadic
 * @param returnType The return `Type*` of the function
 * @param nparams The number of parameters
 * @param ... Type* of the parameters
 */
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
  hashmap_set(functionMap, name, strlen(name), TO_UINTPTR(nativeCode));
}

/**
 * @brief Installs all the built in functions
 *
 * @param table Symbol Table. This is where the functions will be installed
 * Pass `globals` as the symbol table to have global functions.
 * These functions cannot be redifined (due to the way the symbol tables work)
 */
void installBuiltInFunctions(SymbolTable *table)
{
  srand(time(NULL));
  functionMap = hashmap_create();

  /*
  Install system functions
  */
  // 1. printf
  Type *formatType = newType(T_ARRAY);
  formatType->size = 1;
  formatType->type = newType(T_CHAR);
  Type *intType = newType(T_INT);
  installFunction(table, (void *)printfFunction, "printf", 1, intType, 1, formatType);

  // 2. time: secondsSinceEpoch
  installFunction(table, (void *)secondsSinceEpoch, "time", 0, intType, 0);

  // 3. regex: match a regex
  Type *returnType = newType(T_ARRAY);
  returnType->type = newType(T_CHAR);
  returnType->size = 100;
  installFunction(table, (void *)regexMatch, "regex", 0, intType, 2, formatType, formatType);

  // 4. rand: random number
  installFunction(table, (void *)randomInt, "rand", 0, intType, 2, intType, intType);

  // 5. exit: exit the program
  installFunction(table, (void *)exitFunction, "exit", 0, intType, 1, intType);

  // Scan functions
  installFunction(table, (void *)scanInt, "scanInt", 0, intType, 0);
  installFunction(table, (void *)scanFloat, "scanFloat", 0, newType(T_FLOAT), 0);
  installFunction(table, (void *)scanChar, "scanChar", 0, newType(T_CHAR), 0);
  installFunction(table, (void *)scanString, "scanString", 0, returnType, 0);
}

void exitFunction(VMValue **params, int n)
{
  store(mainReturnValue->id, params[0]->value);
  VMValue *mainReturnIp;
  VMValue *v = vm.stack;
  while (v)
  {
    mainReturnIp = v;
    v = v->next;
  }
  vm.ip = FROM_UINTPTR(mainReturnIp->value, int);
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
      case 'l':
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
        written += printf("%ld", FROM_UINTPTR(param->value, long int));
        break;
      }
      case 's':
      {
        n--;
        CHECK(n);
        VMValue *stringValue = *(params++);
        if (stringValue->type->op != T_ARRAY)
        {
          runtimeMessage("printf called with non-string argument\n");
          // point_at_in_line(stringValue->src.line - 1, stringValue->src.col - 1, stringValue->src.col + 6);
          // exit(1);
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
  // return milliseconds;
  int ms = (int)milliseconds;
  RETURN_VALUE(ms);
  // RETURN_VALUE(sec_microsecs);
}

char *uintToString(uintptr_t arr)
{
  char *str = malloc(sizeof(char) * 100);
  char *strbase = str;
  uintptr_t *arrBase = FROM_UINTPTR(arr, uintptr_t *);
  while ((*arrBase) != 0)
  {
    char c = FROM_UINTPTR(*arrBase, char);
    *str = c;
    str++;
    arrBase++;
  }
  *str = '\0';
  return strbase;
}
uintptr_t *stringToUintptr(char *str, int len)
{
  uintptr_t *arr = malloc(sizeof(uintptr_t) * (len + 1));
  uintptr_t *arrBase = arr;
  for (int i = 0; i < len; i++)
  {
    *arrBase = TO_UINTPTR(*str);
    arrBase++;
    str++;
  }
  *arrBase = 0;
  return arr;
}
int match(const char *string, char *pattern)
{
  int status;
  regex_t re;

  if (regcomp(&re, pattern, REG_EXTENDED | REG_NOSUB) != 0)
  {
    return (0); /* Report error. */
  }
  status = regexec(&re, string, (size_t)0, NULL, 0);
  regfree(&re);
  if (status != 0)
  {
    return (0); /* Report error. */
  }
  return (1);
}
void regexMatch(VMValue **params, int n)
{
  VMValue *regexValue = params[0];
  VMValue *str = params[1];
  if (regexValue->type->op != T_ARRAY || str->type->op != T_ARRAY)
  {
    runtimeMessage("Expected string parameters for regexMatch\n");
    exit(1);
  }
  char *regexStr = uintToString(regexValue->value);
  char *strStr = uintToString(str->value);
  int matchResult = match(strStr, regexStr);
  RETURN_VALUE(matchResult);
}

void randomInt(VMValue **params, int n)
{
  int max = FROM_UINTPTR(params[1]->value, int);
  int r = (rand() % max) + FROM_UINTPTR(params[0]->value, int);
  RETURN_VALUE(r);
}

void scanInt(VMValue **params, int n)
{
  int i;
  scanf("%d", &i);
  RETURN_VALUE(i);
}
void scanFloat(VMValue **params, int n)
{
  float i;
  scanf("%f", &i);
  RETURN_VALUE(i);
}
void scanChar(VMValue **params, int n)
{
  char i;
  scanf("%c", &i);
  RETURN_VALUE(i);
}
void scanString(VMValue **params, int n)
{
  char *i = malloc(100);
  scanf("%[^\n]s", i);
  uintptr_t *arr = stringToUintptr(i, strlen(i));
  uintptr_t arrBase = TO_UINTPTR(arr);
  char *str = uintToString(arrBase);
  RETURN_VALUE(arrBase);
}