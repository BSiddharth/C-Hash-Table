CFLAGS = -Wall -Werror -Wno-unused-variable
CC = gcc

hashmap.o: hashmap.c
	$(CC) $(CFLAGS) -c hashmap.c

test.o: test.c
	$(CC) $(CFLAGS) -c test.c

murmurhash.o: murmurhash.c
	$(CC) $(CFLAGS) -c murmurhash.c

test: hashmap.o test.o murmurhash.o
	$(CC) $(CFLAGS) test.o hashmap.o murmurhash.o -o test

runtest: test
	test.exe

clean:
	del test.o hashmap.o murmurhash.o test.exe
