# Compiler
CC = clang

# Compiler flags
CFLAGS = -Wall -g -std=c23 -Iinclude 

# Source files

COMMON_SRC = src/common.c src/sysmodel.c src/parse.c src/file.c

MAIN_SRC = $(COMMON_SRC) src/main.c

TEST_SRC = $(COMMON_SRC) src/munit.c src/tests.c


# Object files
OBJ = $(MAIN_SRC:.c=.o)

# The output executable
TARGET = bin/sysinv
TEST_TARGET = bin/tests
DB_FILE = system.db


# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Compile each source file into an object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJ) $(TARGET) $(TEST_TARGET)
	rm -rf bin/*.dSYM
	rm -rf $(DB_FILE)

test:
	$(CC) $(CFLAGS) ${TEST_SRC} -o $(TEST_TARGET) && ./$(TEST_TARGET)


leaks:
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)