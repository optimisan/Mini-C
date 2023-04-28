#include "../util/symbol.h"
#include "../vm/vm.h"
#include "../util/map.h"

extern hashmap *functionMap;
void installBuiltInFunctions(SymbolTable *table);
void dispatchNativeFunction(VM vm, Instruction callInstruction);