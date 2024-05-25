all:build

# For extending, see TODOs.

CC = gcc
CFLAGS = -g -Wall -Wextra -pedantic -std=c99
CFLAGS_BUILD = $(CFLAGS) -fpic -c

SRC_DIR = src
TEST_DIR = test
BIN_DIR = bin

mk_bin_dir:
	mkdir -p $(BIN_DIR)

# TODO: add test_{type}. E.g.: test_double
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

# TODO: Create 2 vars, one for the test output executable name and the other for the source code file
# test_{type}_exec = $(BIN_DIR)/da_test_{type}
# E.g.:
# test_double_exec = $(BIN_DIR)/da_test_double
#
# TODO:
# test_{type}_src = $(SRC_DIR)/da.c $(SRC_DIR)/da_{type}.c $(TEST_DIR)/da_test_{type}.c
# E.g.:
# test_double_src = $(SRC_DIR)/da.c $(SRC_DIR)/da_double.c $(TEST_DIR)/da_test_double.c
#
# TODO: Create the build step
# test_{type}:$(test_{type}_src) mk_bin_dir
#	$(CC) $(CFLAGS) -o $(test_{type}_exec) $(test_{type}_src)
#	./$(test_{type}_exec)
# E.g.:
# test_double:$(test_double_src) mk_bin_dir
#   $(CC) $(CFLAGS) -o $(test_double_src) $(test_double_src)
#   ./$(test_double_exec)

build_exec = $(BIN_DIR)/libda.a

da_src = $(SRC_DIR)/da.c
da_o = $(BIN_DIR)/da.o

da_int_src = $(SRC_DIR)/da_int.c
da_int_o = $(BIN_DIR)/da_int.o

da_float_src = $(SRC_DIR)/da_float.c
da_float_o = $(BIN_DIR)/da_float.o

# TODO: To add a new type implementation to the library output make 2 vars:
# da_{type}_src = $(SRC_DIR)/da_{type}.c
# da_{type}_o = $(BIN_DIR)/da_{type}.o
# E.g.:
# da_double_src = $(SRC_DIR)/da_double.c
# da_double_o = $(BIN_DIR)/da_double.o

build_src = $(da_src) $(da_int_src) $(da_float_src) mk_bin_dir test
build:$(build_src)
	$(CC) $(CFLAGS_BUILD) -o $(da_o) $(da_src)
	$(CC) $(CFLAGS_BUILD) -o $(da_int_o) $(da_int_src)
	$(CC) $(CFLAGS_BUILD) -o $(da_float_o) $(da_float_src)
	# TODO: add build command for the c file.
	# $(CC) $(CFLAGS_BUILD) -o $(da_{type}_o) $(da_{type}_src)
	# E.g.:
	# $(CC) $(CFLAGS_BUILD) -o $(da_double_o) $(da_double_src)
	#
	# TODO: add $(da_{type}_o) to the end of the following line.
	# ar -rc $(build_exec) $(da_o) $(da_int_o) $(da_float_src) $(da_{type}_o)
	# E.g.:
	# ar -rc $(build_exec) $(da_o) $(da_int_o) $(da_float_o) $(da_double_o)
	ar -rc $(build_exec) $(da_o) $(da_int_o) $(da_float_o)
