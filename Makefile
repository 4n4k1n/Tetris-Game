# Compiler to use
CC = gcc

# Compiler and linker flags
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lncurses

# Target executable
TARGET = tetris

# Automatically find all .c files
SRC = $(wildcard *.c)

# Object files corresponding to source files
OBJ = $(SRC:.c=.o)

# Default target
all: $(TARGET)

# Rule to create the executable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(TARGET)

# Rule to compile object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean up
clean:
	rm -f $(OBJ) $(TARGET)

# Rule to rebuild everything
rebuild: clean all
