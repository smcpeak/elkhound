# Makefile for scannerless example grammar

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
all: sless.exe


%.o: %.cc
	g++ -c -o $@ $(CCFLAGS) $*.cc

sless.h sless.cc: sless.gr
	$(ELKHOUND)/elkhound.exe sless.gr

main.o: sless.h

SLESS_OBJS := main.o sless.o
sless.exe: $(SLESS_OBJS)
	g++ -o $@ $(SLESS_OBJS) $(LDFLAGS)

# I get a segfault when running this.  I'm not sure when it broke.
check: sless.exe
	echo "TODO: this is broken"
	exit 2
	echo "a aa a aaa" | ./sless.exe

clean:
	rm -f *.exe *.o sless.h sless.cc

