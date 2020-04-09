CC=gcc
CFLAGS=-Wall -g
DEPS= opt.h handler.h fxor_types.h xor.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: main.o opt.o handler.o xor.o
	$(CC) $(CFLAGS) -o fxor main.o opt.o handler.o xor.o

clean:
	rm *.o fxor
