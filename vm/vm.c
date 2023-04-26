#include "vm.h"
#include "../util/symbol.h"
#include "../backend/ir.h"

VM vm;

void initVM(IR *ir)
{
  vm.ir = ir;
  vm.ip = 0;
}
#define READ_INSTRUCTION() (vm.ir->instructions[vm.ip++])
#define IS_AT_END() (vm.ip >= vm.ir->size)

void runVM()
{
  while (!IS_AT_END())
  {
    Instruction instruction = READ_INSTRUCTION();
  }
}