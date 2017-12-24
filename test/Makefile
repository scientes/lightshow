CC=gcc
DEBUG_OPTS=-g
OPTIMIZATION_OPTS=-O3
CC_DEFAULT_OPTS=-Wall -Wextra -std=c99 -pedantic $(DEBUG_OPTS) \
	$(OPTIMIZATION_OPTS)
LINKER_OPTS=-lSDL2 -lm

OBJS=Show.o

.c.o:
	$(CC) $(CC_DEFAULT_OPTS) -c $<

all: $(OBJS)
	$(CC) *.o -o Show $(LINKER_OPTS)


clear:
	rm -f *.o main
