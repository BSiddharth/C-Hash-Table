CFLAGS = -Wall -Werror -Wno-unused-variable

hashmap.o: hashmap.c
	gcc $(CFLAGS) -c hashmap.c

test.o: test.c
	gcc $(CFLAGS) -c test.c

test: hashmap.o test.o
	gcc $(CFLAGS) test.o hashmap.o -o test

runtest: test
	test.exe

clean:
	del test.o hashmap.o test.exe
