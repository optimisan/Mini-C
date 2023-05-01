#include "../util/options.h"
#include "backend.h"
#include "irgen.h"
#include "ir.h"
#include "../vm/vm.h"
#include <stdio.h>
#include <stdlib.h>

void backend(Node *astRootNode, char *sourceFileName)
{
  if (dumpAST)
  {
    printf(ANSI_COLOR_BOLD ANSI_COLOR_CYAN "Parsed successfully\n======== AST ========\n" ANSI_COLOR_RESET);
    printNode(astRootNode);
  }
  IR *ir = generateIR(astRootNode, sourceFileName);
  if (!dumpIR)
  {
    printf(ANSI_COLOR_BOLD ANSI_COLOR_BLUE "\n====== Generating IR ======\n" ANSI_COLOR_RESET);
    printf("Writing IR... ");
    writeIRtoFile(ir);
    printf("See %s.ir for the IR\n", sourceFileName);
  }
  else
  {
    printIR(ir, stdout);
  }
  printf(ANSI_COLOR_BOLD ANSI_COLOR_GREEN "====== Executing IR... ======\n" ANSI_COLOR_RESET);
  initVM(ir);
  runVM();
}