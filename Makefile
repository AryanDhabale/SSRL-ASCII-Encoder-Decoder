CC = gcc
CFLAGS = -std=c17 -Wall -g

SRC = src
BIN = bin

SRCS = $(wildcard $(SRC)/*.c)
BINS = $(SRCS:$(SRC)/%.c=$(BIN)/%)

# Default target
all: $(BINS)

# Rule to compile .c files into .exe files
$(BIN)/%: $(SRC)/%.c
	$(CC) $(CFLAGS) -o $@ $<

# Clean up compiled executables
clean:
	rm -f $(BIN)/*
	rm -f $(OUTPUT)output/outputImage.png
	truncate -s 0 output/output.txt

# Make the bin directory if it doesn't exist
$(BIN):
	mkdir -p $(BIN)
