all:build

CC = gcc
CFLAGS = -g -Wall -Wextra -pedantic -std=c99
CFLAGS_BUILD = $(CFLAGS) -fpic -c

SRC_DIR = src
TEST_DIR = test
BIN_DIR = bin

mk_bin_dir:
	mkdir -p $(BIN_DIR)

test:test_generic test_int test_float

test_generic_exec = $(BIN_DIR)/da_test
test_generic_src = $(SRC_DIR)/da.c $(TEST_DIR)/da_test.c
test_generic:$(test_generic_src) mk_bin_dir
	$(CC) $(CFLAGS) -o $(test_generic_exec) $(test_generic_src)
	./$(test_generic_exec)

test_int_exec = $(BIN_DIR)/da_test_int
test_int_src = $(SRC_DIR)/da.c $(SRC_DIR)/da_int.c $(TEST_DIR)/da_test_int.c
test_int:$(test_int_src) mk_bin_dir
	$(CC) $(CFLAGS) -o $(test_int_exec) $(test_int_src)
	./$(test_int_exec)

test_float_exec = $(BIN_DIR)/da_test_float
test_float_src = $(SRC_DIR)/da.c $(SRC_DIR)/da_float.c $(TEST_DIR)/da_test_float.c
test_float:$(test_float_src) mk_bin_dir
	$(CC) $(CFLAGS) -o $(test_float_exec) $(test_float_src)
	./$(test_float_exec)


build_exec = $(BIN_DIR)/libda.a

da_src = $(SRC_DIR)/da.c
da_o = $(BIN_DIR)/da.o

da_int_src = $(SRC_DIR)/da_int.c
da_int_o = $(BIN_DIR)/da_int.o

da_float_src = $(SRC_DIR)/da_float.c
da_float_o = $(BIN_DIR)/da_float.o

build_src = $(da_src) $(da_int_src) $(da_float_src) mk_bin_dir test
build:$(build_src)
	$(CC) $(CFLAGS_BUILD) -o $(da_o) $(da_src)
	$(CC) $(CFLAGS_BUILD) -o $(da_int_o) $(da_int_src)
	$(CC) $(CFLAGS_BUILD) -o $(da_float_o) $(da_float_src)
	ar -rc $(build_exec) $(da_o) $(da_int_o) $(da_float_o)
