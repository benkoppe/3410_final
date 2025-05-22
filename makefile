CC=gcc
CFLAGS=-Wall -pthread -g

all: test_A

test_A: main.c coffee.c impl_A.c
	$(CC) $(CFLAGS) -o test_A main.c coffee.c impl_A.c
