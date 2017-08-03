CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline

intersect: intersect.c intersect.h
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f intersect
