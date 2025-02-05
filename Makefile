# Compiler and flags
CC = cc
CFLAGS = -O2 -Wall -std=c2x
LDFLAGS = 

# Targets
TARGET = tetris
OBJ = tetris.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o $@ $(LDFLAGS)

tetris.o: tetris.c tetris.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)