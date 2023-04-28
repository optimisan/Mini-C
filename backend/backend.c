#include "backend.h"
#include "irgen.h"
#include "ir.h"
#include "../vm/vm.h"
#include <stdio.h>
#include <stdlib.h>

void backend(Node *astRootNode, char *sourceFileName)
{
  printf(ANSI_COLOR_BOLD ANSI_COLOR_CYAN "Parsed successfully\n==== Backend ====\n" ANSI_COLOR_RESET);
  printNode(astRootNode);
  printf(ANSI_COLOR_BOLD ANSI_COLOR_BLUE "\n==== Generating IR ====\n" ANSI_COLOR_RESET);
  IR *ir = generateIR(astRootNode, sourceFileName);
  printf("\nWriting IR... ");
  writeIRtoFile(ir);
  printf("See %s for the IR\n" ANSI_COLOR_BOLD ANSI_COLOR_GREEN "==== Executing IR... ====\n" ANSI_COLOR_RESET, sourceFileName);
  initVM(ir);
  runVM();
}