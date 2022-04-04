CC = gcc
CFLAGS = -Wall -Wextra -O2

mac422shell: mac422shell.c
	$(CC) -o $@ $< $(CFLAGS)

clean:
	rm -f mac422shell
