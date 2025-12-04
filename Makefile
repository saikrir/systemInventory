# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g -Iinclude

# Source files
SRC = src/main.c src/munit.c

# Object files
OBJ = $(SRC:.c=.o)

# The output executable
TARGET = bin/sysinv

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
	rm -f $(OBJ) $(TARGET)

leaks:
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)