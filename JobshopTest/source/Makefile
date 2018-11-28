CC = g++
CCFLAGS = -Wall -Wextra -ansi -pedantic -g -O2 -std=c++0x
LDFLAGS = -lm
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
EXE = executable

executable:$(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ)

.cpp.o:
	$(CC) $(CCFLAGS) -c $<

dep: 
	$(CC) -MM $(OBJ) > makefile.dep

clean:
	rm -rf $(OBJ)

clear:
	rm -rf $(EXE)

-include makefile.dep
