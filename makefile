CFLAGS = -Wall -Werror -Wno-unused-variable

hashmap.o: hashmap.c
	gcc $(CFLAGS) -c hashmap.c

test.o: test.c
	gcc $(CFLAGS) -c test.c

murmurhash.o: murmurhash.c
	gcc $(CFLAGS) -c murmurhash.c

test: hashmap.o test.o murmurhash.o
	gcc $(CFLAGS) test.o hashmap.o murmurhash.o -o test

runtest: test
	test.exe

clean:
	del test.o hashmap.o murmurhash.o test.exe
