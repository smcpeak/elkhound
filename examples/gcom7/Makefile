# Makefile for guarded-command example grammar

# directories
ELKHOUND := ../..
AST      := ../../../ast
SMBASE   := ../../../smbase

# libraries
LIBELKHOUND := $(ELKHOUND)/libelkhound.a
LIBAST      := $(AST)/libast.a
LIBSMBASE   := $(SMBASE)/libsmbase.a

# compilation flags
CCFLAGS := -g -Wall
CCFLAGS += -I$(ELKHOUND) -I$(AST) -I$(SMBASE)
LDFLAGS := -g -Wall $(LIBELKHOUND) $(LIBAST) $(LIBSMBASE)

# default make targets
all: lexer.exe parser.exe


# Remove some built-in rules.
.SUFFIXES:

# Do not delete "intermediate" files.
.SECONDARY:

# Remove target if recipe fails.
.DELETE_ON_ERROR:


%.o: %.cc
	g++ -c -o $@ $(CCFLAGS) $*.cc

tokens.tok: lexer.h $(ELKHOUND)/make-tok
	perl $(ELKHOUND)/make-tok TokenCode <lexer.h >$@

lexer.exe: lexer.cc
	g++ -o $@ $(CCFLAGS) -DTEST_LEXER lexer.cc $(LDFLAGS)

%.gr.gen.h %.gr.gen.cc: %.gr tokens.tok
	$(ELKHOUND)/elkhound.exe -o $*.gr.gen $*.gr

%.ast.gen.h %.ast.gen.cc: %.ast
	$(AST)/astgen.exe -o $*.ast.gen $*.ast

parser.o: gcom.gr.gen.h gcom.ast.gen.h

PARSER_OBJS := lexer.o parser.o gcom.gr.gen.o gcom.ast.gen.o eval.o
parser.exe: $(PARSER_OBJS)
	g++ -o $@ $(PARSER_OBJS) $(LDFLAGS)

check: lexer.exe parser.exe
	echo "x := 2 + 3 + 4; print x" | ./lexer.exe
	echo "x := 2 + 3 + 4; print x" | ./parser.exe -ast
	echo "x := 2 + 3 + 4; print x" | ./parser.exe -tree

clean:
	rm -f *.exe *.o tokens.tok *.gen.h *.gen.cc gmon.out

