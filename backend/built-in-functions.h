#include "../util/symbol.h"
#include "../vm/vm.h"

void installBuiltInFunctions(SymbolTable *table);
void dispatchNativeFunction(VM vm, Instruction callInstruction);