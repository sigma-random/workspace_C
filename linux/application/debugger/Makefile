
CC = cc



SINGLE_STEP = single_step
OBJ-SINGLE_STEP = $(SINGLE_STEP).o
SRC-SINGLE_STEP = single_step-dbg.c
BIN-SINGLE_STEP = $(SINGLE_STEP)

CONTINUE = continue
OBJ-CONTINUE = $(CONTINUE).o
SRC-CONTINUE = continue-dbg.c
BIN-CONTINUE = $(CONTINUE)

GET_REGS = get_regs
OBJ-GET_REGS = $(GET_REGS).o
SRC-GET_REGS = get_regs-dbg.c
BIN-GET_REGS = $(GET_REGS)


BRKPOINT = breakpoint
OBJ-BRKPOINT = $(BRKPOINT).o
SRC-BRKPOINT = breakpoint-dbg.c
BIN-BRKPOINT = $(BRKPOINT)

ATTACH = attach
OBJ-ATTACH = $(ATTACH).o
SRC-ATTACH = attach-dbg.c
BIN-ATTACH = $(ATTACH)


all:$(SINGLE_STEP)\
	$(CONTINUE)\
	$(GET_REGS)\
	$(BRKPOINT)\
	$(ATTACH)\
	



$(SINGLE_STEP): $(OBJ-SINGLE_STEP)
	$(CC) $(OBJ-SINGLE_STEP) -o $(BIN-SINGLE_STEP)
$(OBJ-SINGLE_STEP): $(SRC-SINGLE_STEP)
	$(CC) -c $(SRC-SINGLE_STEP) -o $(OBJ-SINGLE_STEP)

$(CONTINUE): $(OBJ-CONTINUE)
	$(CC) $(OBJ-CONTINUE) -o $(BIN-CONTINUE)
$(OBJ-CONTINUE): $(SRC-CONTINUE)
	$(CC) -c $(SRC-CONTINUE) -o $(OBJ-CONTINUE)

$(GET_REGS): $(OBJ-GET_REGS)
	$(CC) $(OBJ-GET_REGS) -o $(BIN-GET_REGS)
$(OBJ-GET_REGS): $(SRC-GET_REGS)
	$(CC) -c $(SRC-GET_REGS) -o $(OBJ-GET_REGS)

$(BRKPOINT): $(OBJ-BRKPOINT)
	$(CC) $(OBJ-BRKPOINT) -o $(BIN-BRKPOINT)
$(OBJ-BRKPOINT): $(SRC-BRKPOINT)
	$(CC) -c $(SRC-BRKPOINT) -o $(OBJ-BRKPOINT)

$(ATTACH): $(OBJ-ATTACH)
	$(CC) $(OBJ-ATTACH) -o $(BIN-ATTACH)
$(OBJ-ATTACH): $(SRC-ATTACH)
	$(CC) -c $(SRC-ATTACH) -o $(OBJ-ATTACH)




clean:
	rm 		*.o\
			$(BIN-SINGLE_STEP)\
			$(BIN-CONTINUE)\
			$(BIN-GET_REGS)\
			$(BIN-BRKPOINT)\
			$(BIN-ATTACH)\
