CC = gcc
OBJ = main.o stack.o space.o

EXE = run
# all: $(EXE)
.c.o: $(CC) -c *.c

$(EXE):$(OBJ)
	$(CC) -o $@ $(OBJ)

clean:
	rm *.o $(EXE)