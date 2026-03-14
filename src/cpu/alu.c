#include "alu.h"

bool negativeFlag = 0;
bool carryFlag = 0;
bool zeroFlag = 0;

void add(unsigned short *reg, unsigned short *n) {
  *reg += *n;

  zeroFlag = false;
  carryFlag = false;

  if (*reg == 0)        zeroFlag = true;
  if (*reg + *n > 255)  carryFlag = true;
}

void sub(unsigned short *reg, unsigned short *n) {
  *reg -= *n;

  zeroFlag = false;
  carryFlag = false;

  if (*reg == 0)      zeroFlag = true;
  if (*reg - *n < 0)  carryFlag = true;
}

void cmp(unsigned short *reg, unsigned short *n) {
  zeroFlag = false;
  carryFlag = false;

  if (*reg - *n == 0) zeroFlag = true;
  if (*reg - *n < 0)  carryFlag = true;
}
