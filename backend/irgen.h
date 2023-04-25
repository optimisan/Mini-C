#ifndef __IRGEN
#define __IRGEN

#include "../util/AST.h"
#include "../util/symbol.h"
#include "ir.h"

// IRGen
// =====
// IRGen is the interface to the intermediate representation generator.
// It is responsible for generating the IR for a given AST.
extern IR *ir;

IR *generateIR(Node *rootNode, char *sourceFilename);

#endif