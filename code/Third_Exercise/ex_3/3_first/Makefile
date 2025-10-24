CC = gcc
CFLAGS = -I.
LDFLAGS = -lm
DEPS = gen.h parser.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
all: ex_3_1 ex_3_2

ex_3_1: ex_3_1.o 
	$(CC) -o ex_3_1 ex_3_1.o $(LDFLAGS)
	
ex_3_2: ex_3_2.o
	$(CC) -o ex_3_2 ex_3_2.o $(LDFLAGS)
	
run: all
	./ex_3_1
	./ex_3_2
