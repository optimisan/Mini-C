#ifndef __VM
#define __VM
#include "../backend/ir.h"
#include "../util/map.h"

typedef struct VM
{
  IR *ir;
  int ip;
  uintptr_t *stack;
} VM;

#define TO_UINTPTR(x) (*(uintptr_t *)(&x))
#define FROM_UINTPTR(x, type) (*(type *)(&x))

extern hashmap registers;

void store(int reg, uintptr_t value);
uintptr_t load(int reg);

void initVM(IR *ir);
void runVM();
void freeVM();

#endif