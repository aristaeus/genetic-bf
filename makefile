CC=g++
OUT=brainfuck
LIB=
CXXFLAGS=-g -Wall -Wextra -std=c++11
BUILDIR=build/
SRCDIR=src/
INCDIR=include/

FILE=$(notdir $(basename $(shell ls $(SRCDIR)*)))
OBJ=$(addprefix $(BUILDIR),$(addsuffix .o, $(FILE)))

all: $(OBJ)
	$(CC) $(OBJ) $(LIB) -o $(BUILDIR)$(OUT)

build/%.o: src/%.cpp
	$(CC) $(CXXFLAGS) -c -o  $@ $< -I$(INCDIR)

clean:
	rm -rf $(BUILDIR)*
