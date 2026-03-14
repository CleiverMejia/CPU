#include <unistd.h>
#include <stdio.h>
#include "../ram/ram.h"
#include "unit_control.h"
#include "alu.h"
#include "cpu.h"

unsigned short *registers[4] = {&ax, &bx, &cx, &dx};

unsigned char *fetch(unsigned char *pc)
{
  return &memory[*pc];
}

void decode(unsigned char *inst_pointer, unsigned char *inst)
{
  inst[0] = inst_pointer[0];
  ip++;

  if (*inst != HALF &&
      *inst != SYSCALL &&
      !(*inst >= PUSH_A && *inst <= POP_C) &&
      *inst != PUSH_D)
  {
    inst[1] = inst_pointer[1];
    inst[2] = inst_pointer[2];
    ip += 2;
  }
}

void execute(unsigned char *inst)
{
  // printf("0x%.2x\n", *inst);

  short value = (inst[2] << 8) | inst[1];

  switch (*inst)
  {
  case LOAD_A:
  case LOAD_B:
  case LOAD_C:
  case LOAD_D:
    *registers[*inst] = value;
    break;
  case STORE_A:
  case STORE_B:
  case STORE_C:
  case STORE_D:
    if (value >= TEXT_LIMIT)
      memory[value] = *registers[*inst - STORE_A];
    break;
  case ADD_A:
  case ADD_B:
  case ADD_C:
  case ADD_D:
    add(registers[*inst - ADD_A], &value);
    break;
  case SUB_A:
  case SUB_B:
  case SUB_C:
  case SUB_D:
    sub(registers[*inst - SUB_A], &value);
    break;
  case CMP_A:
  case CMP_B:
  case CMP_C:
  case CMP_D:
    cmp(registers[*inst - CMP_A], &value);
    break;
  case JE:
    if (zeroFlag)
      ip = value;
    break;
  case JNE:
    if (!zeroFlag)
      ip = value;
    break;
  case JA:
    if (carryFlag)
      ip = value;
    break;
  case JB:
    if (!carryFlag)
      ip = value;
    break;
  case LEA_A:
  case LEA_B:
  case LEA_C:
  case LEA_D:
    *registers[*inst - LEA_A] = memory[value];
    break;
  case PUSH:
    memory[sp--] = value >> 8;
    memory[sp--] = value;
    break;
  case PUSH_A:
  case PUSH_B:
  case PUSH_C:
  case PUSH_D:
    memory[sp--] = *registers[*inst - PUSH_A] >> 8;
    memory[sp--] = *registers[*inst - PUSH_A];
    break;
  case POP_A:
  case POP_B:
  case POP_C:
  case POP_D:
    *registers[*inst - POP_A] = memory[sp + 2] << 8 | memory[sp + 1];
    sp += 2;
    break;
  case HALF:
    _exit(0);
    break;
  case SYSCALL:
    switch (ax)
    {
    case 1:
      _exit(bx);
      break;
    case 4:
      write(bx, &memory[cx], dx);
      break;
    }
    break;
  }
}
