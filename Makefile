CC=gcc
CFLAGS=-g3 -std=c11 -Wall -Wextra -Werror -lm -D_GNU_SOURCE
OBJECTS=cpu.o stopwatch.o mem.o userinfo.o temp.o home.o fan.o battery.o network.o macspoof.o
LIBS=block.c

all: $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) $< $(LIBS) -o $@

clean:
	rm -f *.o
