#ifndef __IR
#define __IR
#include "../util/AST.h"
#include "../util/symbol.h"
#include "../util/token.h"
#include "../util/map.h"
#include <stdio.h>

extern int nextId, nextLabelId;

typedef struct
{
  int id;
  short isConstant;
  Coordinate src;
  Type *type;
  Symbol *sym;
  union
  {
    int integer;
    float floating;
    char character;
  } as;
} Address;

typedef enum
{
  OP_MINUS,
  OP_GOTO,
  OP_IF_GOTO,
  OP_IF_FALSE_GOTO,
  OP_PARAM,
  OP_CALL,
  OP_RETURN,
  OP_LABEL,
  OP_ASSIGN,
  OP_FUNC,
  // sYNTAX IS OP_ARRAY_DECL[numberOfElements, elementSize, resultAddress]
  OP_ARRAY_DECL,
  // Syntax is OP_ARRAY_INDEX[address, index, result]
  OP_ARRAY_INDEX,
  OP_ARRAY_ASSIGN,
  OP_FUNC_END, //=13
  // math are ascii
} InstType;

typedef struct
{
  // ASCII for math operators
  InstType op;
  Address *arg1;
  Address *arg2;
  Address *result;
} Instruction;

typedef struct
{
  int size;
  int capacity;
  Instruction *instructions;
  // Maps addresses to ids
  hashmap *map;
  char *sourceFileName;
} IR;

Address *newValueAddress(TypeEnum type, void *value, Coordinate src);
Address *newLabelAddress();
Address *newIntAddress0(int value);
Address *newIntAddress(int value, Coordinate src);
Address *newCharAddress(char value, Coordinate src);
Address *newFloatAddress(float value, Coordinate src);
Address *symbolAddress(Symbol *symbol, IR *ir);
Address *functionAddress(Symbol *symbol, IR *ir);
Address *newTempAddress(Type *type);

// Call this before generating IR for a function
// Saves the global id counter.
void beginFunction();

// Call this after generating IR for a function
// Resets the id counter to reuse ids.
void endFunction();
IR *newIR(char *sourceFileName);
Instruction *newInstruction(InstType op, Address *arg1, Address *arg2, Address *result);
void addInstruction(IR *ir, Instruction *instruction);
Address *addLabel(IR *ir);
void printInstruction(Instruction *instruction, FILE *file);
void printIR(IR *ir, FILE *file);
void freeIR(IR *ir);

void writeIRtoFile(IR *ir);

#endif