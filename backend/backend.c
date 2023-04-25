#include "backend.h"
#include "irgen.h"
#include "ir.h"
#include <stdio.h>
#include <stdlib.h>

void backend(Node *astRootNode, char *sourceFileName)
{
  printf("Generating IR...\n");
  printNode(astRootNode);
  // return;
  IR *ir = generateIR(astRootNode, sourceFileName);
  writeIRtoFile(ir);
}