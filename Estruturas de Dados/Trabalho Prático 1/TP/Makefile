CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/funcoes.o $(OBJ)/main.o
HDRS = $(INC)/funcoes.hpp
CFLAGS = -pg -Wall -c -I$(INC)

EXE = $(BIN)/tp1.exe

#all: perf gprof

#perf: $(EXE)
#	$(EXE) /tmp/tp1.out 

#gprof: $(BIN)/tp1.exe
#	$(EXE) /tmp/tp1gprof.out
#	gprof $(EXE) gmon.out > /tmp/tp1gprof.txt
	
$(BIN)/tp1.exe: $(OBJS)
	$(CC) -pg -o $(BIN)/tp1.exe $(OBJS) $(LIBS) 

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp 

$(OBJ)/funcoes.o: $(HDRS) $(SRC)/funcoes.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/funcoes.o $(SRC)/funcoes.cpp