#include "../util/AST.h"
#include "../util/symbol.h"
#include "../util/token.h"
#include "ir.h"
#include "../util/map.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int nextId = 0, nextLabelId = 0;
// Since variables in a function won't be used outside,
// we can reset the nextId back to the number of global variables
// on parsing a function (and starting a new one)
int savedNextId = 0;

void beginFunction()
{
  // savedNextId = nextId;
}
void endFunction()
{
  // nextId = savedNextId;
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
Address *newIntAddress0(int value)
{
  return newValueAddress(T_INT, &value, (Coordinate){0, 0, 0});
}

Address *newIntAddress(int value, Coordinate src)
{
  return newValueAddress(T_INT, &value, src);
}
Address *newCharAddress(char value, Coordinate src)
{
  return newValueAddress(T_CHAR, &value, src);
}
Address *newFloatAddress(float value, Coordinate src)
{
  return newValueAddress(T_FLOAT, &value, src);
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
  address->sym = symbol;
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
  address->sym = symbol;
  address->src = symbol->src;
  address->type = symbol->type;
  return address;
}
Address *newLabelAddress()
{
  Address *address = (Address *)malloc(sizeof(Address));
  address->id = nextLabelId++;
  address->isConstant = 2;
  address->src = (Coordinate){0, 0, 0};
  address->type = newType(T_INT);
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
  if (address->isConstant == 2)
  {
    // it is a label
    char *str = (char *)malloc(sizeof(char) * 10);
    sprintf(str, "L%d", address->id);
    return str;
  }
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
    if (address->type->op != T_FUNCTION)
    {
      sprintf(str, "t%d", address->id);
    }
    else
    {
      sprintf(str, "f%d", address->id);
    }
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
  case OP_IF_GOTO:
    return "OP_IF_GOTO";
  case OP_IF_FALSE_GOTO:
    return "OP_IF_FALSE_GOTO";
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
  case OP_ARRAY_ASSIGN:
    return "OP_ARRAY_ASSIGN";
  case OP_FUNC_END:
    return "OP_FUNC_END";
  case OPR_EQ:
    return "OPR_EQ";
  default:
    char *s = malloc(sizeof(char) * 2);
    s[0] = type;
    s[1] = 0;
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
  // printf("IR for %s\n", ir->sourceFileName);
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
  fclose(file);
}