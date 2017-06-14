
SRC = $(wildcard *.c)
BIN = $(SRC:.c=)
LDFLAGS =
CFLAGS =-Wall -g -I/usr/include 
CC=gcc

all: $(BIN)

%.html: %.c
	highlight -i $< -o $@ --style edit-emacs --inline-css

test: all
	@for test in $(BIN); do \
	  echo - $$test; \
	  ./$$test; \
	done

clean:
	$(RM) $(BIN) *.o *~
