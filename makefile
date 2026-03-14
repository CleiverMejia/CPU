CC = gcc

SRC = $(wildcard src/**/*.c) $(wildcard src/*.c)

OUT = output/main.exe

all:
	$(CC) $(SRC) -o $(OUT)
	$(OUT) ./asm/a.bin