CC = gcc
CFLAGS = -Wall -g -Iheader `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lm

# Source files
SRC = src/main.c src/map.c src/player.c

# Object files
OBJ = $(SRC:.c=.o)

# Executable
EXEC = raycasting_game

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXEC) $(OBJ)

.PHONY: all clean
