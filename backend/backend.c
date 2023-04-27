#include "backend.h"
#include "irgen.h"
#include "ir.h"
#include "../vm/vm.h"
#include <stdio.h>
#include <stdlib.h>

void backend(Node *astRootNode, char *sourceFileName)
{
  printf("==== Backend ====\n");
  printNode(astRootNode);
  printf("\nDone print\n");
  printf("Generating IR...\n");
  IR *ir = generateIR(astRootNode, sourceFileName);
  printf("Writing IR...\n");
  writeIRtoFile(ir);
  printf("Executing IR...\n");
  initVM(ir);
  runVM();
}