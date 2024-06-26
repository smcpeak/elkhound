# elkhound/c/Makefile
# this is the Makefile for the Elkhound-based C Parser

# main target: an Elkhound-based C parser
all: cparse.exe


# ------------------------- Configuration --------------------------
# directories of other software
SMBASE   = ../../smbase
AST      = ../../ast
ELKHOUND = ..

# stuff inside those other directories
LIBSMBASE   = $(SMBASE)/libsmbase.a
LIBAST      = $(AST)/libast.a
LIBELKHOUND = $(ELKHOUND)/libelkhound.a

# C++ compiler.
CXX = g++

# Flags to control generation of debug info.
DEBUG_FLAGS = -g

# Flags to enable dependency generation of .d files.
GENDEPS_FLAGS = -MMD

# Flags to control optimization.
OPTIMIZATION_FLAGS = -O2

# Flags to control compiler warnings.
WARNING_FLAGS =

# Flags for C++ standard to use.
#
# C++17 is needed because that is what smbase uses and it affects
# mangled names (at least when using GCC).
CXX_STD_FLAGS = -std=c++17

# Preprocessing flags.
CPPFLAGS = -I$(SMBASE) -I$(AST) -I$(ELKHOUND)

# Flags for the C++ compiler and preprocessor.
#
# Note: $(GENDEPS_FLAGS) are not included because these flags are used
# for linking too, and if that used $(GENDEPS_FLAGS) then the .d files
# for .o files would be overwritten with info for .exe files.
CXXFLAGS = $(DEBUG_FLAGS) $(OPTIMIZATION_FLAGS) $(WARNING_FLAGS) $(CXX_STD_FLAGS) $(CPPFLAGS)

# Libraries to link with when creating executables.
LIBS = $(LIBELKHOUND) $(LIBAST) $(LIBSMBASE)

# Flags to add to a link command *in addition* to either $(CFLAGS) or
# $(CXXFLAGS), depending on whether C++ modules are included.
LDFLAGS =

# Other tools.
SMFLEX = ../../smflex/smflex


# ---- Automatic Configuration ----
# Pull in settings from ./configure.  They override the defaults above,
# and are in turn overridden by personal.mk, below.
ifeq ($(wildcard config.mk),)
  $(error The file 'config.mk' does not exist.  Run './configure' before 'make'.)
endif
include config.mk


# ---- Customization ----
# Allow customization of the above variables in a separate file.  Just
# create personal.mk with desired settings.
#
# Common things to set during development:
#
#   WERROR = -Werror
#   WARNING_FLAGS = -Wall $(WERROR)
#   OPTIMIZATION_FLAGS =
#
-include personal.mk


# ----------------------------- Rules ------------------------------
# Get rid of some built-in rules.
.SUFFIXES:

# Delete a target when its recipe fails.
.DELETE_ON_ERROR:

# Do not remove "intermediate" targets.
.SECONDARY:

# Compile .cc to .o, also generating dependency files.
%.o: %.cc
	$(CXX) -c -o $@ $(GENDEPS_FLAGS) $(CXXFLAGS) $<


# ----------------------- lexer2 -------------------
# run smflex on the lexer description
%.lex.cc %.lex.h: %.lex
	$(SMFLEX) -o$*.lex.cc $*.lex


# modules needed for lexer2 stand-alone
LEXER2_OBJS := \
  lexer1.o \
  lexer1.lex.o \
  cc_lang.o

# lexer2 stand-alone binary
lexer2.exe: lexer2.cc lexer2.h $(LEXER2_OBJS) $(LIBS)
	$(CXX) -o $@ $(CXXFLAGS) -DTEST_LEXER2 $(LDFLAGS) lexer2.cc $(LEXER2_OBJS) $(LIBS)


# ------------------------- cparse ---------------------
# run lexer2 stand-alone to generate token list
c.tok: lexer2.exe
	./lexer2.exe -myparser >$@

# run astgen to generate the AST implementation
%.ast.gen.h %.ast.gen.cc: %.ast
	$(AST)/astgen.exe -o$*.ast.gen $*.ast


# run elkhound to generate the parser
%.gr.gen.h %.gr.gen.cc %.gr.gen.y: %.gr %.tok
	$(ELKHOUND)/elkhound.exe -tr bison -v -o $*.gr.gen $*.gr


# list of modules needed for the parser
CPARSE_OBJS := \
  lexer1.o \
  lexer1.lex.o \
  cc_lang.o \
  lexer2.o \
  parssppt.o \
  c.ast.gen.o \
  c_env.o \
  cc_flags.o \
  c_type.o \
  cparse.o \
  exprequal.o \
  exprvisit.o \
  paths.o \
  postorder.o \
  stubs.o \
  tcheck.o \
  treeout.o \
  c_variable.o \
  c.gr.gen.o \
  main.o

# Dependencies on generated code.
c_env.o: c.ast.gen.h
cparse.o: c.ast.gen.h
exprequal.o: c.ast.gen.h
exprvisit.d: c.ast.gen.h
main.o: c.gr.gen.h c.ast.gen.h
paths.o: c.ast.gen.h
postorder.d: c.ast.gen.h
stubs.d: c.ast.gen.h
tcheck.d: c.ast.gen.h


# parser binary
cparse.exe: $(CPARSE_OBJS) $(LIBS)
	$(CXX) -o $@ $(CXXFLAGS) $(CPARSE_OBJS) $(LDFLAGS) $(LIBS)
	./$@ $(ELKHOUND)/c.in/c.in1


# ----------------------- bcparse ---------------------
# NOTE: This target ('bcparse') is not built by default because
# I don't want the default build to require Bison.

# bison parser from the same grammar; the 'sed' is because Bison
# already interpretes 0 as EOF, and if my rule names it explicitly
# then it gets mad
bcparse.y: c.gr.gen.y
	echo '%{' >$@
	echo '#include "bcparse.h"' >>$@
	echo '%}' >>$@
	sed -e 's/File L2_EOF/File/' <c.gr.gen.y >>$@

# run Bison; the 'sed' command is to silence a spurious warning about
# 'yyval' being used uninitialized; I also compile here (instead of
# relying on another pattern rule) because I want to control exactly
# how the compilation happens (to ensure the Bison-parser is compiled
# with flags to make it a fair performance test with my own stuff)
%.tab.c %.tab.o %.tab.h: %.y
	bison -d -v $*.y
	mv $*.tab.c $*.tab.c.orig
	sed -e 's/YYSTYPE yyval;/YYSTYPE yyval = 0;/' \
	    -e 's/__attribute__ ((__unused__))//' \
	  <$*.tab.c.orig >$*.tab.c
	rm $*.tab.c.orig
	$(CXX) -c -g -o $*.tab.o -O2 -DNDEBUG -Wall $(YYDEBUG) $*.tab.c

# C-without-typedefs parser, using Bison
bcparse-deps := bcparse.cc bcparse.tab.o lexer1.o lexer1.lex.o lexer2.o cc_lang.o
bcparse.exe: $(bcparse-deps) $(LIBS)
	$(CXX) -o $@ $(CXXFLAGS) $(LDFLAGS) $(bcparse-deps) $(LIBS)
	./$@ $(ELKHOUND)/c.in/c.in1


# -------------------- clean, etc. -------------------
clean:
	rm -f *.o *.d *.exe *.gen.* *.tab.* *.output
	rm -f bcparse.y c.tok
	rm -f lexer1.lex.cc lexer1.lex.h

distclean: clean
	rm -f config.mk

check:
	@echo "The C parser doesn't have an independent 'make check'."
	@echo "Run 'make check' in Elkhound to run the C parser tests."
