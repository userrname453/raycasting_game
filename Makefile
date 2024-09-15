# Makefile

CC=gcc
CFLAGS=-Iinc -lSDL2
SOURCES=$(wildcard src/*.c)
OBJECTS=$(SOURCES:.c=.o)
TARGET=raycasting_game

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(OBJECTS) $(TARGET)