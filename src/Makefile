CC=gcc
export VERSION = $(shell bash ../scripts/version.sh) # The single, trailing blank is essential
export DATE    = $(shell bash ../scripts/date.sh) #    The single, trailing blank is essential
CFLAGS         = -DVERSION=\"$(VERSION)\" -DDATE=\"$(DATE)\" -O3 -Wall -Wshadow -pedantic -std=gnu99 -g -I../common/ -L../common/ #-pg

SRCFILES  = dnaDist.c interface.c alignment.c distance.c gsl_rng.c sequenceData.c stringUtil.c
OBJFILES  = dnaDist.o interface.o alignment.o distance.o gsl_rng.o sequenceData.o stringUtil.o
LIBS      = -lcommon -lm -lgsl -lblas
EXECFILE  = dnaDist

.PHONY : all
all : $(EXECFILE)
$(EXECFILE) : $(OBJFILES)
	$(CC) $(CFLAGS) -o $(EXECFILE) $(OBJFILES) $(LIBS)
interface.o: interface.h

clean:
	rm -f *.o *~
test:
	bash ../scripts/dnaDist.sh 
