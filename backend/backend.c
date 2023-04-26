#include "backend.h"
#include "irgen.h"
#include "ir.h"
#include <stdio.h>
#include <stdlib.h>

void backend(Node *astRootNode, char *sourceFileName)
{
  printNode(astRootNode);
  printf("\nDone print\n");
  printf("Generating IR...\n");
  IR *ir = generateIR(astRootNode, sourceFileName);
  printf("Writing IR...\n");
  writeIRtoFile(ir);
}