CC = gcc

CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lncurses

TARGET = tetris

SRC = $(wildcard *.c)

OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

rebuild: clean all
