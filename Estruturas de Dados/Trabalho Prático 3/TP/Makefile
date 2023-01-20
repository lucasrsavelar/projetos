CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/funcoes.o $(OBJ)/main.o
HDRS = $(INC)/funcoes.hpp
CFLAGS = -pg -Wall -c -I$(INC)

EXE = $(BIN)/tp3.exe

#all: gprof #perf 

#perf: $(EXE)
#	$(EXE) /tmp/tp1.out 

#gprof: $(BIN)/tp2.exe
#	$(EXE) -i C:\Users\Lucas\Desktop\entrada.txt -o out.txt -s 2 -m 2 /tmp/tp2gprof.out
#	gprof $(EXE) gmon.out > /tmp/tp2gprof.txt
	
$(BIN)/tp3.exe: $(OBJS)
	$(CC) -pg -o $(BIN)/tp3.exe $(OBJS) $(LIBS) 

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp 

$(OBJ)/funcoes.o: $(HDRS) $(SRC)/funcoes.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/funcoes.o $(SRC)/funcoes.cpp