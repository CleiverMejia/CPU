#ifndef CPU_H
#define CPU_H

/* Registers */
extern unsigned short ax;
extern unsigned short bx;
extern unsigned short cx;
extern unsigned short dx;
extern unsigned short ip;  // Instruction pointer
extern unsigned short sp; // Stack pointer
extern unsigned short bp; // Base pointer

void cpuRun();

#endif