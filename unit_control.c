#include <unistd.h>
#include <stdio.h>
#include "ram.h"
#include "unit_control.h"

unsigned char pointer_counter = 0; 
char flags = 0;

void update_flags(unsigned char v) {
  flags = 0;

  if (v & 0)    flags |= 8;
  if (v & 0x80) flags |= 4;
  if (v > 255)  flags |= 2;
}

void add(unsigned char *reg, unsigned char *n) {
  *reg += *n;

  update_flags(*reg);
}

unsigned char *fetch(unsigned char *pc) {
  return &memory[*pc];
}

void decode(unsigned char *inst_pointer, unsigned char *inst) {
  inst[0] = inst_pointer[0];
  pointer_counter++;

  switch (inst[0]) {
    case LOAD_A:
    case LOAD_B:
    case LOAD_C:
    case LOAD_D:
    case STORE_A:
    case STORE_B:
    case STORE_C:
    case STORE_D:
    case ADD_A:
    case ADD_B:
    case ADD_C:
    case ADD_D:
    case SUB_A:
    case SUB_B:
    case SUB_C:
    case SUB_D:
    case CMP_A:
    case CMP_B:
    case CMP_C:
    case CMP_D:
    case JE:
    case JNE:
    case JA:
    case JB:
      inst[1] = inst_pointer[1];
      pointer_counter++;
      break;
  }
}

void execute(unsigned char *inst) {
  printf("0x%.2x\n", inst[0]);
  switch (inst[0]) {
    case LOAD_A:
      regA = inst[1];
      break;
    case LOAD_B:
      regB = inst[1];
      break;
    case LOAD_C:
      regC = inst[1];
      break;
    case LOAD_D:
      regD = inst[1];
      break;
    case STORE_A:
      memory[inst[1]] = regA;
      break;
    case STORE_B:
      memory[inst[1]] = regB;
      break;
    case STORE_C:
      memory[inst[1]] = regC;
      break;
    case STORE_D:
      memory[inst[1]] = regD;
      break;
    case ADD_A:
      add(&regA, &inst[1]);
      break;
    case ADD_B:
      add(&regB, &inst[1]);
      break;
    case ADD_C:
      add(&regC, &inst[1]);
      break;
    case ADD_D:
      add(&regD, &inst[1]);
      break;
    case SUB_A:
      regA -= inst[1];
      break;
    case SUB_B:
      regB -= inst[1];
      break;
    case SUB_C:
      regC -= inst[1];
      break;
    case SUB_D:
      regD -= inst[1];
      break;
    case CMP_A:
      update_flags(regA - inst[1]);
      break;
    case CMP_B:
      update_flags(regB - inst[1]);
      break;
    case CMP_C:
      update_flags(regC - inst[1]);
      break;
    case CMP_D:
      update_flags(regD - inst[1]);
      break;
    case JE:
      if (flags & ZF) {
        pointer_counter = inst[1];
      }
      break;
    case JNE:
      if (!(flags & ZF)) {
        pointer_counter = inst[1];
      }
      break;
    case HALF:
      _exit(0);
      break;
    case SYSCALL:
      switch (regA) {
        case 0:
          break;
        case 1:
          _exit(regB);
          break;
        case 4:
          write(regB, &memory[regC], regD);
          break;
      }
      break;
  }
}
