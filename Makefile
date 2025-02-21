CC = gcc
CFLAGS = -std=c17 -Wall -g

SRC = src
BIN = bin

SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(SRCS:$(SRC)/%.c=$(BIN)/%.o)
TARGET = $(BIN)/program

# Default target
all: $(TARGET)

# Rule to compile all .c files into a single executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to compile .c files into .o object files
$(BIN)/%.o: $(SRC)/%.c | $(BIN)
	$(CC) $(CFLAGS) -c -o $@ $<

# Rule to run the compiled program
run: $(TARGET)
	@echo "Running $(TARGET)..."
	@$(TARGET)

# Clean up compiled files
clean:
	rm -f $(BIN)/*
	rm -f $(OUTPUT)output/outputImage.png
	truncate -s 0 output/output.txt

# Make the bin directory if it doesn't exist
$(BIN):
	mkdir -p $(BIN)