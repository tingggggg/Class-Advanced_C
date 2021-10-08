CC = gcc
OBJ = main.o list.o

EXE = run
all: $(EXE)
.c.o: $(CC) -c *.c

$(EXE): $(OBJ)
	$(CC) -o $@ $(OBJ)

clean:
	rm *.o $(EXE)