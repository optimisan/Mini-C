#ifndef __OPTIONS
#define __OPTIONS
extern int dumpAST;
extern int dumpIR;
extern int dumpTokens;

char *parseOptions(int argc, char **argv);

#endif