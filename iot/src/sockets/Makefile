CC       = gcc

CCFLAGS  = -Wall -ggdb
LDFLAGS  = -lstdc++

SRCS     = $(wildcard *.c)
OBJS     = $(SRCS:.c=.o)
EXES     = $(SRCS:.c= )

all: $(EXES)

%.html: %.c
	highlight -i $< -o $@ --style edit-emacs --inline-css


%: %.cc
	$(CC) $(CCFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -rf *.o *~ $(EXES)