#include <stdio.h>
#include <stdlib.h>
#include "../ram/ram.h"
#include "alu.h"
#include "unit_control.h"

unsigned short ax = 0;
unsigned short bx = 0;
unsigned short cx = 0;
unsigned short dx = 0;
unsigned short sp = MEMORY_SIZE - 1;
unsigned char ip = 0;

void cpuRun()
{
  unsigned char *inst = malloc(sizeof(char[3]));

  while (ip < TEXT_LIMIT)
  {
    unsigned char *inst_pointer = fetch(&ip);

    decode(inst_pointer, inst);

    if (*inst == HALF)
      break;

    execute(inst);
  }

  free(inst);
}
