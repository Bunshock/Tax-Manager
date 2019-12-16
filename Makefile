CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -Wno-unused-function -g
OBJ = tax.o info.o test.o types.o
HEADERS = $(wildcard *.h)

test: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ):$(HEADERS)

clean:
	rm -f $(OBJ) test

.PHONY: clean