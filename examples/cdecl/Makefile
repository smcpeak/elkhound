# Makefile for cdecl example


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


# -------- targets --------
# main target
all: cdecl.exe

# extra object files
extras := \
  $(ELKHOUND)/c/parssppt.o \
  $(ELKHOUND)/c/lexer2.o \
  $(ELKHOUND)/c/lexer1.o \
  $(ELKHOUND)/c/lexer1.lex.o \
  $(ELKHOUND)/c/cc_lang.o

# invoke the parser generator
cdecl.gr.gen.cc cdecl.gr.gen.h: cdecl.gr
	$(ELKHOUND)/elkhound.exe -v -o cdecl.gr.gen cdecl.gr

# compile a C++ source file
%.o: %.cc
	g++ -c $(CCFLAGS) $(CPPFLAGS) $*.cc

# link the driver code with the generated parser and lexer;
# also run it with a test input
cdecl.exe: $(ELKHOUND)/glrmain.o cdecl.gr.gen.o
	g++ -g -o $@ $^ $(extras) $(LDFLAGS)
	./cdecl.exe $(ELKHOUND)/in/cdecl.in1

clean:
	rm -f *.exe *.bin *.gen.* *.o gdb.log
