# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g -Iheader `sdl2-config --cflags`

# Linker flags
LDFLAGS = `sdl2-config --libs` -lm

# Executable name
TARGET = raycasting_game

# Source files
SRCS = $(wildcard src/*.c)

# Rule to build the executable
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)

# Clean rule
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: clean
