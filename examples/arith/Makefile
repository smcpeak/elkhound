# Makefile for arith example


# -------- external tools and libraries --------
# paths to the relevant subsystems
SMBASE        := ../../../smbase
SMFLEX        := ../../../smflex
AST           := ../../../ast
ELKHOUND      := ../..

# Elkhound runtime support library
LIBELKHOUND := $(ELKHOUND)/libelkhound.a


# -------- compiler and linker configuration --------
# preprocessing flags
CPPFLAGS := -I$(ELKHOUND) -I$(AST) -I$(SMBASE)

# C++ compilation flags
CCFLAGS := -g -Wall

# linking flags
LDFLAGS := $(LIBELKHOUND) $(SMBASE)/libsmbase.a


# -------- targets --------
# main target
all: arith.exe

# tell 'make' that it cannot compile arith.cc until after
# it has generated arith.gr.gen.h
arith.o: arith.gr.gen.h

# invoke the parser generator
%.gr.gen.cc %.gr.gen.h: %.gr
	$(ELKHOUND)/elkhound.exe -v -o $*.gr.gen $*.gr

# invoke the lexer generator
arithyy.cc: arith.lex
	$(SMFLEX)/smflex -o$@ arith.lex

# compile a C++ source file
%.o: %.cc
	g++ -c $(CCFLAGS) $(CPPFLAGS) $*.cc

# link the driver code with the generated parser and lexer;
# also run it with a test input
arith.exe: arith.o arithyy.o arith.gr.gen.o
	g++ -o $@ -g $^ $(LDFLAGS)
	echo "3 + 4 * 5" | ./arith.exe
	echo "3 + 4 * 5" | ./arith.exe printTree


clean:
	rm -f *.exe *.bin *.gen.* *.o

toolclean: clean
	rm -f arithyy.cc
