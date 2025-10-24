CC = gcc
CFLAGS = -I.
DEPS = gen.h parser.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
all: first second

first: thi_fir.o 
	$(CC) -o first thi_fir.o
	
second: thi_sec.o
	$(CC) -o second thi_sec.c 
	
run: all
	./first
	./second
