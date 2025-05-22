CC=gcc
CFLAGS=-Wall -pthread -g

all: test_A test_B test_C

test_A: main.c coffee.c impl_A.c
	$(CC) $(CFLAGS) -DMANAGER_FUNC=manager_A -DBARISTA_FUNC=barista_A \
		-o test_A main.c coffee.c impl_A.c

test_B: main.c coffee.c impl_B.c
	$(CC) $(CFLAGS) -DMANAGER_FUNC=manager_B -DBARISTA_FUNC=barista_B \
		-o test_B main.c coffee.c impl_B.c


test_C: main.c coffee.c impl_C.c
	$(CC) $(CFLAGS) -DMANAGER_FUNC=manager_C -DBARISTA_FUNC=barista_C \
		-o test_C main.c coffee.c impl_C.c
