# Makefile for cexp examples


# -------- external tools and libraries --------
# paths to the relevant subsystems
SMBASE        := ../../../smbase
AST           := ../../../ast
ELKHOUND      := ../..

# Elkhound runtime support library
LIBELKHOUND := $(ELKHOUND)/libelkhound.a


# -------- compiler and linker configuration --------
# preprocessing flags
CPPFLAGS := -I$(ELKHOUND) -I$(ELKHOUND)/c -I$(AST) -I$(SMBASE)

# C++ compilation flags
CCFLAGS := -g -Wall

# linking flags
LDFLAGS := $(LIBELKHOUND) $(AST)/libast.a $(SMBASE)/libsmbase.a


# -------- generic rules --------
# invoke the parser generator
%.gr.gen.cc %.gr.gen.h: %.gr
	$(ELKHOUND)/elkhound.exe -v -o $*.gr.gen $*.gr

# invoke the AST generator
%.ast.gen.cc %.ast.gen.h: %.ast
	$(AST)/astgen.exe -b$*.ast.gen $*.ast

# compile a C++ source file
%.o: %.cc
	g++ -c $(CCFLAGS) $(CPPFLAGS) $*.cc


# -------- targets --------
# main target
all: cexp3ast.ast.gen.h cexp3.exe cexp3b.exe

# extra object files
extras := \
  $(ELKHOUND)/c/parssppt.o \
  $(ELKHOUND)/c/lexer2.o \
  $(ELKHOUND)/c/lexer1.o \
  $(ELKHOUND)/c/lexer1.lex.o \
  $(ELKHOUND)/c/cc_lang.o

# cexp3b: disambiguation using 'merge'
cexp3b.gr: cexp3.gr
	rm -f $@
	grep -v PREC cexp3.gr >$@
	chmod a-w $@

cexp3.exe: $(ELKHOUND)/glrmain.o cexp3.gr.gen.o cexp3mrg.o cexp3ast.ast.gen.o
	g++ -g -o $@ $^ $(extras) $(LDFLAGS)
	./$@ $(ELKHOUND)/in/cexp3.in1 | tee tmp.out
	grep 'result: 7' tmp.out
	rm tmp.out

cexp3b.exe: $(ELKHOUND)/glrmain.o cexp3b.gr.gen.o cexp3mrg.o cexp3ast.ast.gen.o
	g++ -g -o $@ $^ $(extras) $(LDFLAGS)
	./$@ $(ELKHOUND)/in/cexp3.in1 | tee tmpb.out
	grep 'result: 7' tmpb.out
	rm tmpb.out


clean:
	rm -f *.exe cexp3b.gr *.bin *.gen.* *.o
