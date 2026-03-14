#include <stdio.h>
#include "ram/ram.h"
#include "cpu/cpu.h"
#include "cpu/alu.h"

void loadASM(const char *path);

int main(int argc, char const *argv[])
{
    loadASM(argv[1]);

    cpuRun();

    printf("\nRegisters\n");
    printf("|AX: %.2X |BX: %.2X |CX: %.2X |DX: %.2X |SP: %2X |\n", ax, bx, cx, dx, sp);

    printf("Flags\n");
    printf("|ZF: %.2X |NF: %.2X |CF: %.2X |\n", zeroFlag, negativeFlag, carryFlag);

    return 0;
}

void loadASM(const char *path)
{
    FILE *asmFile = fopen(path, "r");

    if (asmFile == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    char byte = 0;
    size_t pos = 0;

    while (fread(&byte, sizeof(byte), 1, asmFile) == 1)
    {
        memory[pos++] = byte;
    }

    fclose(asmFile);
}