# Makefile for elkhound
# see license.txt for copyright and terms of use

# I uncomment this temporarily to just build certain modules
#tmp: mlsstr

# main targets: elkhound, and some examples
all: elkhound libelkhound.a forbid.gr.gen.out arith c cc2/cc2.exe
	@echo BUILD FINISHED


# ------------------------- Configuration --------------------------
# Directories of other components.
SMBASE    = ../smbase
SMFLEXDIR = ../smflex
AST       = ../ast

# C++ compiler.
CXX = g++

# Flags to control generation of debug info.
DEBUG_FLAGS = -g

# Flags to enable dependency generation of .d files.
GENDEPS_FLAGS = -MMD

# Flags to control optimization.
#
# TODO: I previously identified a problem with enabling optimization.
# I doubt that has been fixed.  Investigate.
OPTIMIZATION_FLAGS =

# Flags to control compiler warnings.
WARNING_FLAGS =

# Flags for C++ standard to use.
CXX_STD_FLAGS = -std=c++11

# Preprocessing flags.
#
# "-I." is needed so files compiled in subdirectories can include files
# in the top-level directory.
#
# "-Ic" is needed for binaries that use $(support-set).
#
CPPFLAGS = -I$(SMBASE) -I$(AST) -I. -Ic

# Flags for the C++ compiler and preprocessor.
#
# Note: $(GENDEPS_FLAGS) are not included because these flags are used
# for linking too, and if that used $(GENDEPS_FLAGS) then the .d files
# for .o files would be overwritten with info for .exe files.
CXXFLAGS = $(DEBUG_FLAGS) $(OPTIMIZATION_FLAGS) $(WARNING_FLAGS) $(CXX_STD_FLAGS) $(CPPFLAGS)

# Libraries to link with when creating test executables.
LIBS = $(LIBAST) $(LIBSMBASE)

# Flags to add to a link command *in addition* to either $(CFLAGS) or
# $(CXXFLAGS), depending on whether C++ modules are included.
LDFLAGS =

# external tools
PERL   = perl
AR     = ar
RANLIB = ranlib


# ---- Options within this Makefile ----
# This variable is a parameter that can be passed on the 'make' command
# line.  It becomes part of the -tr argument to 'elkhound'.  By default,
# it's set to the flag to generate a debug dump of the LR parse tables.
TRGRAMANL = ,lrtable


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
# Get rid of (some...) built-in rules.
.SUFFIXES:

# Delete a target when its recipe fails.
.DELETE_ON_ERROR:

# Do not remove "intermediate" targets.
.SECONDARY:


# Things in other components.
LIBSMBASE = $(SMBASE)/libsmbase.a
SMFLEX    = $(SMFLEXDIR)/smflex
LIBAST    = $(AST)/libast.a
ASTGEN    = $(AST)/astgen


# compile .cc to .o
%.o: %.cc
	$(CXX) -c -o $@ $(CXXFLAGS) $<
	@perl depend.pl -o $@ $(CXXFLAGS) $< >$*.d


# ----------------- sets of related object files ---------------------
# files needed to represent a grammar in memory
grammar-set := \
  asockind.o \
  grammar.o
-include $(grammar-set:.o=.d)

# in addition to grammar-set, files needed to parse a grammar description
# and emit action code
grampar-set := \
  emitcode.o \
  mlsstr.o \
  genml.o \
  gramast.ast.gen.o \
  gramlex.yy.o \
  grampar.o \
  grampar.tab.o
-include $(grampar-set:.o=.d)

# minimal runtime files needed to do GLR parsing; these get
# combined to form libelkhound.a, the Elkhound runtime library
glr-set := \
  cyctimer.o \
  glr.o \
  parsetables.o \
  useract.o
-include $(glr-set:.o=.d)

# utility modules useful with elkhound, though not necessary
util-set := \
  ptreenode.o \
  ptreeact.o
-include $(util-set:.o=.d)

# additional modules borrowed from the C parser for the trivial grammars,
# and the C++ parser based on the Standard grammar
support-set := \
  c/cc_lang.o \
  c/parssppt.o \
  c/lexer1.o \
  c/lexer1.lex.o \
  c/lexer2.o

#-include $(support-set:.o=.d)
#
# The above include is deliberately missing.  There is a problem with
# the generated .d files when the source lives in a directory other
# than the current one, and I have not tracked down precisely when and
# why this occurs.  Unfortunately, it means that some changes
# (especially in smbase) require a 'make clean'...


# ---------------------- generic rules ----------------------
# intermediate files for an ast spec
# (this have been commented-out and instantiated with the specific
# rules for gramast.ast, because I only need once instance, and
# because the cygwin version of make-3.80 fails to recognize the
# applicability of this pattern for some reason)
# %.ast.gen.cc %.ast.gen.h: %.ast $(AST)/astgen
# 	rm -f $*.ast.gen.*
# 	$(AST)/astgen -o$*.ast.gen $*.ast
# 	chmod a-w $*.ast.gen.h $*.ast.gen.cc

# intermediate files for a grammar
# TRGRAMANL: extra trace flags specified by user; starts with "," if defined
# ('chmod a-w' is so I don't accidentally edit it)
%.gr.gen.cc %.gr.gen.h %.gr.gen.y: %.gr elkhound
	rm -f $*.gr.gen.*
	./elkhound -v -tr bison,NOconflict$(TRGRAMANL) -o $*.gr.gen $*.gr
	chmod a-w $*.gr.gen.h $*.gr.gen.cc

# bison parser from the a given grammar; the 'sed' is because Bison
# already interpretes 0 as EOF, and if my rule names it explicitly
# then it gets mad
%.y: %.gr.gen.y
	echo '%{' >$@
	echo '#include "trivbison.h"' >>$@
	echo '%}' >>$@
	sed -e 's/"EOF" {/{/' <$*.gr.gen.y >>$@

# run Bison; the 'sed' command is to silence a spurious warning about
# 'yyval' being used uninitialized; I also compile here (instead of
# relying on another pattern rule) because I want to control exactly
# how the compilation happens (to ensure the Bison-parser is compiled
# with flags to make it a fair performance test with my own stuff)
#
# When enabled, this rule gets used to compile grampar.y, even though
# I have a non-pattern rule below for that file.  There do not seem to
# be any other .y files here currently, so I'm just disabling this
# entire rule.
#%.tab.c %.tab.o %.tab.h: %.y
#	bison -d -v $*.y
#	mv $*.tab.c $*.tab.c.orig
#	sed -e 's/__attribute__ ((__unused__))//' \
#	  <$*.tab.c.orig >$*.tab.c
#	rm $*.tab.c.orig
#	g++ -c -o $*.tab.o $(YYDEBUG) $*.tab.c $(CXXFLAGS)

# run the trivial-grammar helper
%.gr: %.gr.in make-trivparser.pl
	rm -f $@
	perl ./make-trivparser.pl $(notdir $*) <$*.gr.in >$@
	chmod a-w $@

%.tree.gr: %.gr.in make-trivparser.pl
	rm -f $@
	perl ./make-trivparser.pl -ptree $(notdir $*) <$*.gr.in >$@
	chmod a-w $@

# make a parser for testing some grammar, using trivial lexer
trivparse-deps := trivmain.cc trivlex.o libelkhound.a
%.gr.exe: %.gr.gen.o $(trivparse-deps) $(LIBS)
	$(CXX) -o $@ -DGRAMMAR_NAME=\"$*.bin\" $(CXXFLAGS) $(LDFLAGS) $*.gr.gen.o $(support-set) $(trivparse-deps) $(LIBS)

# similar, for Bison as the parser-generator
trivbison-deps := trivbison.o trivlex.o lexer2.o libelkhound.a
%.bison.exe: %.tab.o $(trivbison-deps)
	$(CXX) -o $@ $(CXXFLAGS) $(LDFLAGS) $*.tab.o $(trivbison-deps)


# ------------------- intermediate files --------------------
# Rule for running smflex.
%.yy.cc %.yy.h: %.lex
	$(SMFLEX) -o$*.yy.cc $*.lex

# grammar description AST (manual instantiation of above
# commented-out pattern rule)
%.ast.gen.cc %.ast.gen.h: %.ast $(AST)/astgen.exe
	$(AST)/astgen.exe -o$*.ast.gen $*.ast
	chmod a-w $*.ast.gen.h $*.ast.gen.cc

# bison implementation of grammar parser.
# I have to make some changes to the generated output so it will compile
# with a C++ compiler, and want to extract the codes so they're available
# separately without having to know about all of the types in YYSTYPE.
#
# TODO: This multi-target rule is not safe.
grampar.tab.cc grampar.tab.h grampar.codes.h: grampar.y
	bison -d -v grampar.y
	@#
	@# I will be compiling the output as C++.
	@#
	mv -f grampar.tab.c grampar.tab.cc
	@#
	@# This extracts the declaration of "enum yytokentype" and
	@# puts it into agrampar.codes.h.  That way I can use the
	@# token codes in the lexer without also having to declare
	@# everything that is in the YYSTYPE union.
	@#
	sed -n -e '/enum yytokentype/,/};/p' < grampar.tab.h > grampar.codes.h

# new C++ grammar with treebuilding actions
#
# TODO: This multi-target rule is not safe.
cc2/cc2t.gr.gen.cc cc2/cc2t.gr.gen.h cc2/cc2t.gr.gen.y: cc2/cc2.gr c/c.tok elkhound
	rm -f cc2/cc2t*
	sed -e 's/cc2\.gr\.gen\.h/cc2t.gr.gen.h/' <cc2/cc2.gr >cc2/cc2t.gr
	./elkhound -v -tr treebuild$(TRGRAMANL) -o cc2/cc2t.gr.gen cc2/cc2t.gr
	chmod a-w cc2/cc2t.gr*


# ----------------- extra dependencies -----------------
# These dependencies ensure that automatically-generated code is
# created in time to be used by other build processes which need it.
# I had been maintaining the list by hand, but now I've got a script
# to build it.  The list may need to be rebuilt from time to time; if
# you get compile errors after 'make clean' because of missing files
# that are automatically generated, rebuild extradep.mk after a full
# compilation succeeds.

extradep.mk:
	perl ./find-extra-deps *.d cc2/*.d >$@

-include extradep.mk


# --------------------- test programs ----------------------
# grammar lexer test program
gramlex-dep := gramlex.yy.cc $(AST)/gramlex.cc
gramlex: ../ast/gramlex.h $(gramlex-dep) $(LIBS)
	$(CXX) -o $@ -DTEST_GRAMLEX $(CXXFLAGS) $(LDFLAGS) $(gramlex-dep) $(LIBS)

# cycle timer test
cyctimer: cyctimer.cc cyctimer.h
	$(CXX) -o $@ -DTEST_CYCTIMER $(CXXFLAGS) $(LDFLAGS) cyctimer.cc $(LIBS)

# ML lexical parser
mlsstr: mlsstr.cc mlsstr.h
	$(CXX) -o $@ -DTEST_MLSSTR $(CXXFLAGS) $(LDFLAGS) mlsstr.cc $(LIBS)

# test grammar for 'forbid' (there is no executable for this, I just look
# at the Elkhound output)
forbid.gr.gen.out: forbid.gr
	./elkhound -tr requireExactStats -o forbid.gr.gen forbid.gr


# -------------------- exported library ----------------
# glr parsing engine
libelkhound.a: $(glr-set) $(util-set)
	rm -f $@
	$(AR) -r $@ $(glr-set) $(util-set)
	-$(RANLIB) $@


# --------------------- executables ---------------------
# reads the grammar and emits C++ code for semantic functions;
# this is the main parser generator binary
elkhound-dep := gramanl.cc gramexpl.o $(grammar-set) $(grampar-set) parsetables.o
elkhound: $(elkhound-dep) grammar.h gramanl.h $(LIBS)
	$(CXX) -o $@ $(CXXFLAGS) $(LDFLAGS) -DGRAMANL_MAIN $(elkhound-dep) $(LIBS)

# C++ parser based on Standard grammar
cc2-deps := cc2/cc2main.o cc2/cc2.gr.gen.o libelkhound.a
cc2/cc2.exe: $(cc2-deps) $(LIBS)
	$(CXX) -o $@ $(CXXFLAGS) $(LDFLAGS) $(support-set) $(cc2-deps) $(LIBS)

# new C++ parser with treebuilding
cc2t-deps := cc2/cc2main.o cc2/cc2t.gr.gen.o libelkhound.a
cc2/cc2t.exe: $(cc2t-deps) $(LIBS)
	$(CXX) -o $@ $(CXXFLAGS) $(LDFLAGS) $(support-set) $(cc2t-deps) $(LIBS)


# ---------------------- Elkhound examples ------------------
.PHONY: c
c: elkhound libelkhound.a
	$(MAKE) -C c

c.in/c.in4c: c.in/c.in4b
	rm -f $@
	for n in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18; do \
	  cat $< >>$@; \
	done

c.in/c.in4d: c.in/c.in4c
	rm -f $@
	for n in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18; do \
	  cat $< >>$@; \
	done

# stuff in examples directory
.PHONY: examples arith
arith: elkhound libelkhound.a
	$(MAKE) -C examples/arith

examples: all glrmain.o arith gcom
	$(MAKE) -C examples/cexp
	$(MAKE) -C examples/cdecl
	$(MAKE) -C examples/scannerless

.PHONY: ocaml
ocaml:
	$(MAKE) -C ocaml


# ---------------------------- gcom -----------------------
# guarded command example from tutorial
.PHONY: gcom gcom-clean
gcom:
	$(MAKE) -C examples/gcom1 all check
	$(MAKE) -C examples/gcom4 all check
	$(MAKE) -C examples/gcom5 all check
	$(MAKE) -C examples/gcom all check
	$(MAKE) -C examples/gcom7 all check

gcom-clean:
	$(MAKE) -C examples/gcom1 clean
	$(MAKE) -C examples/gcom4 clean
	$(MAKE) -C examples/gcom5 clean
	$(MAKE) -C examples/gcom clean
	$(MAKE) -C examples/gcom7 clean
	$(MAKE) -C examples/scannerless clean


# ----------------------------- EFa -----------------------
# input for EFa
triv/efa.in:
	mkdir $@
	perl -e 'foreach $$n (500, 1000, 1500, 2000, 2500, 5000, 10000, 20000, 50000, 100000, 200000, 500000, 1000000) {  \
	           $$name = sprintf("%07d", $$n);            \
	           open(OUT, ">$@/$$name.in") or die $!; \
	           print OUT "A";                            \
	           for($$i=0; $$i < $$n; $$i++) {            \
	             print OUT ("PA");                       \
	           }                                         \
	           close(OUT);                               \
	         }'

EFA_TESTS := triv/efa.perf.txt triv/efa.notree.perf.txt triv/efa.bison.tree.perf.txt triv/efa.bison.notree.perf.txt

#.PHONY: $(EFA_TESTS) all-efa

# run all the EFa tests; the whole batch runs in less than a minute
# (well, they did before I put in the loop from 1 to 5 ...)
all-efa: $(EFA_TESTS)

# performance test for EFa
triv/efa.perf.txt:
	rm -f $@
	for fn in triv/efa.in/*; do \
	  for count in 1 2 3 4 5; do \
	    triv/EFa.tree.gr.exe -tr progress -count $$fn 2>&1 | \
	      sed "s,^,$$fn: ," >> $@ ; \
	  done; \
	done

triv/efa.notree.perf.txt:
	rm -f $@
	for fn in triv/efa.in/*; do \
	  for count in 1 2 3 4 5; do \
	    triv/EFa.tree.gr.exe -tr progress,trivialActions $$fn 2>&1 | \
	      sed "s,^,$$fn: ," >> $@ ; \
	  done; \
	done

triv/efa.bison.tree.perf.txt:
	rm -f $@
	for fn in triv/efa.in/*; do \
	  for count in 1 2 3 4 5; do \
	    triv/EFa.tree.bison.exe $$fn 2>&1 | \
	      sed "s,^,$$fn: ," >> $@ ; \
	  done; \
	done

triv/efa.bison.notree.perf.txt:
	rm -f $@
	for fn in triv/efa.in/*; do \
	  for count in 1 2 3 4 5; do \
	    triv/EFa.bison.exe $$fn 2>&1 | \
	      sed "s,^,$$fn: ," >> $@ ; \
	  done; \
	done

%.csv: %.txt
	cat $^ | grep cycles | \
	  perl -p -e 's/^[^:]*\D(\d+)\D.*:.*\D(\d+)_(\d+) cycles.*$$/$$1, $$2$$3/' >$@

all-efa-csv: $(EFA_TESTS:.txt=.csv)


# --------------------------- EEb -----------------------
# input for EEb
triv/eeb.in:
	mkdir $@
	perl -e 'foreach $$n (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 20, 50, 100, 200, 300, 400, 500) {  \
	           open(OUT, ">$@/$$n.in") or die $!;    \
	           print OUT "B";                            \
	           for($$i=0; $$i < $$n; $$i++) {            \
	             print OUT ("PB");                       \
	           }                                         \
	           close(OUT);                               \
	         }'

# performance test for EEb
triv/eeb.perf.txt:
	rm -f $@
	for n in 10 20 50 100 200 300 400 500; do \
	  triv/EEb.tree.gr.exe -tr progress -count triv/eeb.in/$$n.in 2>&1 | \
	    sed "s/^/$$n: /" >> $@ ; \
	done

triv/eeb.notree.perf.txt:
	rm -f $@
	for n in 10 20 50 100 200 300 400 500; do \
	  triv/EEb.tree.gr.exe -tr progress,trivialActions triv/eeb.in/$$n.in 2>&1 | \
	    sed "s/^/$$n: /" >> $@ ; \
	done


# --------------------------- SSx ----------------------
# input for SSx
triv/ssx.in:
	mkdir $@
	perl -e 'for($$n=1; $$n <= 99; $$n += 2) {           \
	           open(OUT, ">$@/$$n.in") or die $!;        \
	           for($$i=0; $$i < $$n; $$i++) {            \
	             print OUT ("X");                        \
	           }                                         \
	           close(OUT);                               \
	         }'

# performance test for SSx
triv/ssx.perf.txt:
	rm -f $@
	for n in 15 25 35 45 55 65 75 85 99; do \
	  triv/SSx.tree.gr.exe -tr progress -count triv/ssx.in/$$n.in 2>&1 | \
	    sed "s/^/$$n: /" >> $@ ; \
	done

triv/ssx.notree.perf.txt:
	rm -f $@
	for n in 15 25 35 45 55 65 75 85 99; do \
	  triv/SSx.tree.gr.exe -tr progress,trivialActions triv/ssx.in/$$n.in 2>&1 | \
	    sed "s/^/$$n: /" >> $@ ; \
	done



# --------------------------- SSSx ----------------------
# input for SSSx
triv/sssx.in:
	mkdir $@
	perl -e 'for($$n=1; $$n <= 99; $$n += 1) {           \
	           open(OUT, ">$@/$$n.in") or die $!;        \
	           for($$i=0; $$i < $$n; $$i++) {            \
	             print OUT ("X");                        \
	           }                                         \
	           close(OUT);                               \
	         }'

triv/sssx.perf.txt:
	rm -f $@
	for n in 5 10 15 20 25 30 35 40 45 50; do \
	  triv/SSSx.tree.gr.exe -tr progress -count triv/sssx.in/$$n.in 2>&1 | \
	    sed "s/^/$$n: /" >> $@ ; \
	done

triv/sssx.notree.perf.txt:
	rm -f $@
	for n in 5 10 15 20 25 30 35 40 45 50; do \
	  triv/SSSx.tree.gr.exe -tr progress,trivialActions triv/sssx.in/$$n.in 2>&1 | \
	    sed "s/^/$$n: /" >> $@ ; \
	done


# ------------------------ DeclExpr ----------------------
triv/DeclExpr.perf.txt:
	rm -f $@
	for n in 1 10 100 1000 10000; do \
	  triv/DeclExpr.gr.exe -tr progress,trivialActions triv/DeclExpr.in$$n 2>&1 | \
	    sed "s/^/$$n: /" >> $@ ; \
	done


# ------------------------ documentation -----------------------
# directory of generated documentation
gendoc:
	mkdir gendoc

# dependencies for 'elkhound', the parser generator executable
gendoc/elkhound_dep.dot:
	perl $(SMBASE)/scan-depends.pl -r -I$(AST) gramanl.cc >$@

# dependencies for 'glr.h', the entry point to the runtime library
gendoc/glr.dot:
	perl $(SMBASE)/scan-depends.pl -r -I$(AST) glr.h >$@

# check to see if they have dot
.PHONY: dot
dot:
	@if ! which dot >/dev/null; then \
	  echo "You don't have the 'dot' tool.  You can get it at:"; \
	  echo "http://www.research.att.com/sw/tools/graphviz/"; \
	  exit 2; \
	fi

# use 'dot' to lay out the graph
%.ps: %.dot dot
	dot -Tps <$*.dot >$@

# use 'convert' to make a PNG image with resolution not to exceed
# 1000 in X or 700 in Y ('convert' will preserve aspect ratio); this
# also antialiases, so it looks very nice (it's hard to reproduce
# this using 'gs' alone)
%.png: %.ps
	convert -geometry 1000x700 $^ $@

# glr is much smaller
gendoc/glr.png: gendoc/glr.ps
	convert -geometry 500x400 $^ $@

gendoc/configure.txt: configure
	./configure --help >$@

# "make doc" should build whatever we have that needs building
.PHONY: doc
doc: gendoc gendoc/elkhound_dep.png gendoc/glr.png gendoc/configure.txt
	@echo "built documentation"

# some other random phony targets (I hate this clutter..)
.PHONY: clean distclean check


# -------------------- clean, check, etc. ------------------
# things to remove from all directories
CLEAN_PATTERNS := \
  *.o  \
  *~ \
  *.d \
  *.exe \
  *.gen.* \
  *.bin \
  *.output \
  a.out \
  core

clean: gcom-clean
	rm -f $(CLEAN_PATTERNS)
	rm -f elkhound glr gramlex cyctimer
	rm -f grampar.output grampar tlexer
	rm -f gramlex.yy.cc gramlex.yy.h
	rm -f libelkhound.a
	rm -f gdb.log gprof.out gmon.out test-bad-tmp.c *.tmp
	rm -f examples/crash1.{cc,h}
	rm -f c.in/c.in4c c.in/c.in4d
	cd cc2; rm -f $(CLEAN_PATTERNS)
	cd triv; rm -f $(CLEAN_PATTERNS) *.y *.gr
	for dir in arith cdecl cexp; do \
	  (cd examples/$$dir; $(MAKE) clean); \
	done
	$(MAKE) -C c clean

distclean: clean
	rm -f config.mk config.status config.summary glrconfig.h
	cd triv; rm -rf sssx.in ssx.in eeb.in
	$(MAKE) -C c distclean
	rm -rf gendoc
	rm -f c.in/c.in4{c,d}

# 'clean', plus remove distributed output files from bison
toolclean: clean
	rm -f grampar.tab.cc grampar.tab.h grampar.codes.h
	$(MAKE) -C examples/arith toolclean
	$(MAKE) -C c toolclean

check: all mlsstr
	./mlsstr
	MAKE=$(MAKE) ./regrtest
	@echo ""
	@echo "Regression tests passed."

# remake the generated config.mk if its inputs have changed
config.mk: config.mk.in config.status
	./config.status

# reconfigure if the configure script has changed
config.status: configure.pl sm_config.pm
	./config.status -reconfigure


# --------------- random other stuff --------------------
# test for rcptr
trcptr: rcptr.h trcptr.cc
	$(CXX) -o $@ trcptr.cc