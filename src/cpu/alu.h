#ifndef ALU_H
#define ALU_H

#include <stdbool.h>

extern bool negativeFlag;
extern bool carryFlag;
extern bool zeroFlag;

void add(unsigned short *reg, unsigned short *n);
void sub(unsigned short *reg, unsigned short *n);
void cmp(unsigned short *reg, unsigned short *n);

#endif // !ALU_H
