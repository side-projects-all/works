ASM = nasm
LD = ld 

SRC = snake.asm
OBJ = snake.o
OUT = snake

all: $(OUT)

$(OBJ): $(SRC)
	$(ASM) -f elf64 $(SRC) -o $(OBJ)

$(OUT): $(OBJ)
	$(LD) $(OBJ) -o $(OUT)

clean:
	rm $(OBJ) $(OUT)

