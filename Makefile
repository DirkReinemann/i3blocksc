CC=gcc
CFLAGS=-g3 -std=c11 -Wall -Wextra -Werror -lm -D_GNU_SOURCE
OBJECTS=$(patsubst %.c,%.o,$(filter-out block.c, $(wildcard *.c)))
SCRIPTS=$(filter-out helper.sh, $(wildcard *.sh))
INSTALLDIR=$(HOME)/.config/i3/blocks
LIBS=block.c

all: $(OBJECTS)

compile: $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) $< $(LIBS) -o $@

clean:
	rm -f *.o

install: compile
	-mkdir -p $(INSTALLDIR)
	-cp $(OBJECTS) $(INSTALLDIR)
	-cp $(SCRIPTS) $(INSTALLDIR)

uninstall:
	@$(foreach obj,$(OBJECTS),rm -f $(INSTALLDIR)/$(obj);)
	@$(foreach scr,$(SCRIPTS),rm -f $(INSTALLDIR)/$(scr);)
