all:build

bin_dir:
	mkdir -p bin

test:src/da.c test/da_test.c bin_dir
	gcc src/da.c test/da_test.c -g -Wall -Wextra -pedantic -std=c99 -o bin/da_test
	./bin/da_test

build:src/da.c bin_dir test
	gcc -c src/da.c -g -Wall -Wextra -pedantic -std=c99 -fpic -o bin/da.o
	gcc -shared -o bin/libda.so bin/da.o
