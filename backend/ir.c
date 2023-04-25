#include "../util/AST.h"
#include "../util/symbol.h"
#include "../util/token.h"
#include "ir.h"
#include "../util/map.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int nextId = 0;
// Since variables in a function won't be used outside,
// we can reset the nextId back to the number of global variables
// on parsing a function (and starting a new one)
int savedNextId = 0;

void beginFunction()
{
  savedNextId = nextId;
}
void endFunction()
{
  nextId = savedNextId;
}

IR *newIR(char *sourceFileName)
{
  IR *ir = (IR *)malloc(sizeof(IR));
  ir->size = 0;
  ir->capacity = 10;
  ir->instructions = (Instruction *)malloc(sizeof(Instruction) * ir->capacity);
  ir->sourceFileName = sourceFileName;
  ir->map = hashmap_create();
  return ir;
}

Instruction *newInstruction(InstType op, Address *arg1, Address *arg2, Address *result)
{
  Instruction *instruction = (Instruction *)malloc(sizeof(Instruction));
  instruction->op = op;
  instruction->arg1 = arg1;
  instruction->arg2 = arg2;
  instruction->result = result;
  return instruction;
}
Address *newIntAddress(TypeEnum type, int value, Coordinate src)
{
  return newValueAddress(type, &value, src);
}
Address *newCharAddress(TypeEnum type, char value, Coordinate src)
{
  return newValueAddress(type, &value, src);
}
Address *newFloatAddress(TypeEnum type, float value, Coordinate src)
{
  return newValueAddress(type, &value, src);
}
Address *newValueAddress(TypeEnum type, void *value, Coordinate src)
{
  Address *address = (Address *)malloc(sizeof(Address));
  address->id = 0; // nextId++;
  address->isConstant = 1;
  address->src = src;
  address->type = newType(type);
  switch (type)
  {
  case T_INT:
    address->as.integer = *(int *)value;
    break;
  case T_FLOAT:
    address->as.floating = *(float *)value;
    break;
  case T_CHAR:
    address->as.character = *(char *)value;
    break;
  }
  return address;
}
Address *functionAddress(Symbol *symbol, IR *ir)
{
  Address *address = (Address *)malloc(sizeof(Address));
  uintptr_t id = nextId++;
  hashmap_get_set(ir->map, symbol, sizeof(Symbol *), &id);
  address->id = id;
  address->isConstant = 0;
  address->src = symbol->src;
  address->type = symbol->type;
  return address;
}
Address *symbolAddress(Symbol *symbol, IR *ir)
{
  Address *address = (Address *)malloc(sizeof(Address));
  uintptr_t id = nextId++;
  hashmap_get_set(ir->map, symbol, sizeof(Symbol *), &id);
  address->id = id;
  address->isConstant = 0;
  address->src = symbol->src;
  address->type = symbol->type;
  return address;
}
Address *newTempAddress(Type *type)
{
  Address *address = (Address *)malloc(sizeof(Address));
  address->id = nextId++;
  address->isConstant = 0;
  address->src = (Coordinate){0, 0, 0};
  address->type = type;
  return address;
}

char *addressString(Address *address)
{
  if (address->isConstant)
  {
    char *str = (char *)malloc(sizeof(char) * 10);
    switch (address->type->op)
    {
    case T_INT:
      sprintf(str, "%d", address->as.integer);
      break;
    case T_FLOAT:
      sprintf(str, "%f", address->as.floating);
      break;
    case T_CHAR:
      sprintf(str, "%c", address->as.character);
      break;
    }
    return str;
  }
  else
  {
    char *str = (char *)malloc(sizeof(char) * 10);
    sprintf(str, "t%d", address->id);
    return str;
  }
}

void addInstruction(IR *ir, Instruction *instruction)
{
  if (ir->size == ir->capacity)
  {
    ir->capacity *= 2;
    ir->instructions = (Instruction *)realloc(ir->instructions, sizeof(Instruction) * ir->capacity);
  }
  ir->instructions[ir->size++] = *instruction;
}
Address *addLabel(IR *ir)
{
  Address *label = newTempAddress(newType(T_INT));
  addInstruction(ir, newInstruction(OP_LABEL, NULL, NULL, label));
  return label;
}
static char *instTypeToString(InstType type)
{
  switch (type)
  {
  case OP_MINUS:
    return "OP_MINUS";
  case OP_GOTO:
    return "OP_GOTO";
  case OP_IF:
    return "OP_IF";
  case OP_IF_FALSE:
    return "OP_IF_FALSE";
  case OP_PARAM:
    return "OP_PARAM";
  case OP_CALL:
    return "OP_CALL";
  case OP_RETURN:
    return "OP_RETURN";
  case OP_LABEL:
    return "OP_LABEL";
  case OP_ASSIGN:
    return "OP_ASSIGN";
  case OP_FUNC:
    return "OP_FUNC";
  case OP_ARRAY_DECL:
    return "OP_ARRAY_DECL";
  case OP_ARRAY_INDEX:
    return "OP_ARRAY_INDEX";
  default:
    char *s = malloc(sizeof(char));
    *s = type;
    return s;
  }
}
void printInstruction(Instruction *instruction, FILE *file)
{
  fprintf(file, "%s ", instTypeToString(instruction->op));
  if (instruction->arg1)
  {
    fprintf(file, "%s ", addressString(instruction->arg1));
  }
  if (instruction->arg2)
  {
    fprintf(file, "%s ", addressString(instruction->arg2));
  }
  if (instruction->result)
  {
    fprintf(file, "%s ", addressString(instruction->result));
  }
  fprintf(file, "\n");
}
void printIR(IR *ir, FILE *file)
{
  fprintf(file, "IR for %s\n", ir->sourceFileName);
  for (int i = 0; i < ir->size; i++)
  {
    printInstruction(&ir->instructions[i], file);
  }
}
void freeIR(IR *ir)
{
  free(ir->instructions);
  free(ir);
}
void writeIRtoFile(IR *ir)
{
  char *filename = malloc(strlen(ir->sourceFileName) + 4);
  strcpy(filename, ir->sourceFileName);
  strcat(filename, ".ir");
  FILE *file = fopen(filename, "w");
  printIR(ir, file);
}