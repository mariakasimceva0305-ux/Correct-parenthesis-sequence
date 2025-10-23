CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SRC_DIR = src
TEST_DIR = test
LIB_DIR = lib

SRCS = $(SRC_DIR)/cbs.c
OBJS = $(SRC_DIR)/cbs.o

TEST_SRC = $(TEST_DIR)/test.c
TEST_EXEC = $(TEST_DIR)/run

all: $(LIB_DIR)/libcbs.a $(TEST_EXEC)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

$(OBJS): $(SRCS) | $(LIB_DIR)
	$(CC) $(CFLAGS) -c $(SRCS) -o $(OBJS)

$(LIB_DIR)/libcbs.a: $(OBJS)
	ar rcs $@ $(OBJS)

$(TEST_EXEC): $(TEST_SRC) $(LIB_DIR)/libcbs.a
	$(CC) $(CFLAGS) -o $@ $(TEST_SRC) -L$(LIB_DIR) -lcbs

test: $(TEST_EXEC)
	./$(TEST_EXEC)

clean:
	rm -rf $(LIB_DIR) $(TEST_EXEC) $(OBJS)

.PHONY: all test clean