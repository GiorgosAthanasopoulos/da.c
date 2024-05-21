all:da_test

da_test:src/da.c test/da_test.c
	mkdir -p bin
	gcc src/da.c test/da_test.c -g -Wall -Wextra -pedantic -std=c99 -o bin/da_test
	./bin/da_test
