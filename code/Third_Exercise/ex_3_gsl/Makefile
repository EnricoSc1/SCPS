CC = gcc
CFLAGS = -I.
LDFLAGS = -lhdf5 -lgsl -lgslcblas -lm
DEPS = gen.h parser.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
all: ex_3_1_hdf5 ex_3_2_hdf5

ex_3_1_hdf5: ex_3_1_hdf5.o 
	$(CC) -o ex_3_1_hdf5 ex_3_1_hdf5.o $(LDFLAGS)
	
ex_3_2_hdf5: ex_3_2_hdf5.o
	$(CC) -o ex_3_2_hdf5 ex_3_2_hdf5.o $(LDFLAGS)
	
run: all
	./ex_3_1_hdf5
	./ex_3_2_hdf5
