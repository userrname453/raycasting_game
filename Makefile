# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g -Iheader `sdl2-config --cflags`

# Linker flags
LDFLAGS = `sdl2-config --libs` -lSDL2 -lSDL2_image -lm

# Executable name
TARGET = raycasting_game

# Source files
SRCS = src/main.c src/raycasting.c src/draw_walls.c src/draw_sky.c src/draw_floor.c src/map.c src/player.c src/minimap.c src/depth.c

# Rule to build the executable
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

# Clean rule
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: clean
