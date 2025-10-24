CC = gcc
CFLAGS = -I.
LDFLAGS = -lhdf5 -lgsl -lgslcblas -lm
DEPS = gen.h parser.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
all: ex_3_1_gsl ex_3_2_gsl

ex_3_1_gsl: ex_3_1_gsl.o 
	$(CC) -o ex_3_1_gsl ex_3_1_gsl.o $(LDFLAGS)
	
ex_3_2_gsl: ex_3_2_gsl.o
	$(CC) -o ex_3_2_gsl ex_3_2_gsl.o $(LDFLAGS)
	
run: all
	./ex_3_1_gsl
	./ex_3_2_gsl
