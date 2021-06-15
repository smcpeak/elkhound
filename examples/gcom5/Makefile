# Makefile for guarded-command example grammar

# directories
ELKHOUND := ../..
SMBASE   := ../../../smbase

# libraries
LIBELKHOUND := $(ELKHOUND)/libelkhound.a
LIBSMBASE   := $(SMBASE)/libsmbase.a

# compilation flags
CCFLAGS := -g -Wall
CCFLAGS += -I$(ELKHOUND) -I$(SMBASE)
LDFLAGS := -g -Wall $(LIBELKHOUND) $(LIBSMBASE)

# default make targets
all: lexer.exe parser.exe


%.o: %.cc
	g++ -c -o $@ $(CCFLAGS) $*.cc

tokens.tok: lexer.h $(ELKHOUND)/make-tok
	perl $(ELKHOUND)/make-tok TokenCode <lexer.h >$@

lexer.exe: lexer.cc
	g++ -o $@ $(CCFLAGS) -DTEST_LEXER lexer.cc $(LDFLAGS)

# This is written as a pattern rule because multi-target non-pattern
# rules are broken.
%.h %.cc: %.gr tokens.tok
	test "x$*" = "xgcom"
	$(ELKHOUND)/elkhound.exe gcom.gr

parser.o: gcom.h

PARSER_OBJS := lexer.o parser.o gcom.o
parser.exe: $(PARSER_OBJS)
	g++ -o $@ $(PARSER_OBJS) $(LDFLAGS)

check: lexer.exe parser.exe
	echo "x := 2 + 3 + 4; print x" | ./lexer.exe
	echo "x := 2 + 3 + 4; print x" | ./parser.exe
	echo "x := 2 + 3 + 4; print x" | ./parser.exe -tree

clean:
	rm -f *.exe *.o tokens.tok gcom.h gcom.cc gmon.out

