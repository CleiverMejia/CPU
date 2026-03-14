#ifndef UNIT_CONTROL_H
#define UNIT_CONTROL_H

#define LOAD_A  0x0
#define LOAD_B  0x1
#define LOAD_C  0x2
#define LOAD_D  0x3
#define STORE_A 0x4
#define STORE_B 0x5
#define STORE_C 0x6
#define STORE_D 0x7


#define HALF    0xA
#define SYSCALL 0xB
#define ADD_A   0xC
#define ADD_B   0xD
#define ADD_C   0xE
#define ADD_D   0xF
#define SUB_A   0x10
#define SUB_B   0x11
#define SUB_C   0x12
#define SUB_D   0x13
#define CMP_A   0x14
#define CMP_B   0x15
#define CMP_C   0x16
#define CMP_D   0x17
#define JE      0x18
#define JNE     0x19
#define JA      0x1A
#define JB      0x1B
#define LEA_A   0x1C
#define LEA_B   0x1D
#define LEA_C   0x1E
#define LEA_D   0x1F

unsigned char *fetch(unsigned char *pc);
void decode(unsigned char *inst_pointer, unsigned char *inst);
void execute(unsigned char *inst);

#endif // !UNIT_CONTROL_H
