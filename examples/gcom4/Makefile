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

gcom.h gcom.cc: gcom.gr tokens.tok
	$(ELKHOUND)/elkhound.exe gcom.gr

parser.o: gcom.h

PARSER_OBJS := lexer.o parser.o gcom.o
parser.exe: $(PARSER_OBJS)
	g++ -o $@ $(PARSER_OBJS) $(LDFLAGS)

check: lexer.exe parser.exe
	echo "2 + 3" | ./lexer.exe
	echo "2 + 3" | ./parser.exe

clean:
	rm -f *.exe *.o tokens.tok gcom.h gcom.cc gmon.out

