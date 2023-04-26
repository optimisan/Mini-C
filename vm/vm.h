#ifndef __VM
#define __VM
#include "../backend/ir.h"

typedef struct
{
  TypeEnum type;
  int size;
  int elementSize;
  union
  {
    int i;
    float f;
    void *s;
  } as;
} VMValue;
typedef struct VM
{
  IR *ir;
  int ip;
} VM;

void initVM(IR *ir);
void runVM();
void freeVM();

#endif