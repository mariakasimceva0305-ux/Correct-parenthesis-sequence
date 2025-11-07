CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99
INCLUDE = -Iinclude
SRC_DIR = src
TEST_DIR = test
LIB_DIR = lib

SOURCES = $(SRC_DIR)/cbs.c
TEST_SOURCE = $(TEST_DIR)/test.c

LIBRARY = $(LIB_DIR)/libcbs.a
TEST_EXEC = $(TEST_DIR)/run

all: $(LIBRARY) $(TEST_EXEC)

$(LIBRARY): $(SOURCES)
	@mkdir -p $(LIB_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $(SOURCES) -o $(SRC_DIR)/cbs.o
	ar rcs $(LIBRARY) $(SRC_DIR)/cbs.o

$(TEST_EXEC): $(TEST_SOURCE) $(LIBRARY)
	@mkdir -p $(TEST_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(TEST_SOURCE) -L$(LIB_DIR) -lcbs -o $(TEST_EXEC)

test: $(TEST_EXEC)
	./$(TEST_EXEC)

clean:
	rm -rf $(LIB_DIR) $(TEST_EXEC) $(SRC_DIR)/*.o

.PHONY: all test clean
