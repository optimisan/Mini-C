#ifndef __VM
#define __VM
#include "../backend/ir.h"
#include "../util/map.h"

typedef struct VMValue
{
  uintptr_t value;
  Type *type;
  Coordinate src;
  struct VMValue *next;
} VMValue;

typedef struct VM
{
  IR *ir;
  int ip;
  VMValue *stack;
} VM;

#define TO_UINTPTR(x) (*(uintptr_t *)(&x))
#define FROM_UINTPTR(x, type) (*(type *)(&x))

// Labels: id -> ip
// Registers: id -> uintptr_t
// Functions: id -> ip
extern hashmap *registers, *labels, *functions;

uintptr_t getAddrValue(Address *addr);
int getAddrIntValue(Address *addr);
// Store a value in a register
void store(int reg, uintptr_t value);
// Load from register
uintptr_t load(int reg);
// Save a label and its ip
void saveLabel(Address *addr);
// Save a function and its ip
void saveFunction(Address *addr);
// Get the ip of a label
int getLabelIP(Address *addr);
// Get the ip of a function
int getFunctionIP(Address *addr);

// Stack operations
void push(Address *addr);
VMValue *pop();
uintptr_t popValue();
// Initialize the VM
void initVM(IR *ir);
void runVM();

void runtimeMessage(char *message, ...);
void runtimeError(char *message, ...);
// void freeVM();

#endif