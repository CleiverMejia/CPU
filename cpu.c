#include <stdio.h>
#include <stdlib.h>
#include "ram.h"
#include "unit_control.h"

unsigned char regA = 0;
unsigned char regB = 0;
unsigned char regC = 0;
unsigned char regD = 0;

int main() {
  unsigned char *inst = malloc(3 * sizeof(char));

  while (pointer_counter < MEMORY_SIZE) {
    unsigned char *inst_pointer = fetch(&pointer_counter);
    
    decode(inst_pointer, inst);

    if (inst[0] == HALF) break;

    execute(inst);
   }

  printf("\nRegisters\n");
  printf("|A: %.2X\t|B: %.2X\t|C: %.2X\t|D: %.2X|\n", regA, regB, regC, regD);

  printf("Flags\n");
  printf("|ZF: %.2X\t|NF: %.2X\t|CF: %.2X\t|\n", (flags&ZF), (flags&NF), (flags&CF));

  free(inst);

  return 0;
}
