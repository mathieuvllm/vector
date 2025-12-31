CC = gcc
CFLAGS = -Wall -Wextra -std=c11

OBJS = vec.o tests.o

tests: $(OBJS)
	$(CC) $(CFLAGS) -o tests $(OBJS)

vec.o: vec.c vec.h
	$(CC) $(CFLAGS) -c vec.c

tests.o: tests.c vec.h
	$(CC) $(CFLAGS) -c tests.c

clean:
	rm -f *.o tests
