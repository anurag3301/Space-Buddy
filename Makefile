# Directories
SRC_DIR := src
OBJ_DIR := obj
INCLUDE_DIR := include

# Compiler and flags
CC := gcc
CFLAGS := -I$(INCLUDE_DIR) -g -Wall -Wextra -std=c99 -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Executable name
EXEC := spacebuddy

# Find all source files and corresponding object files
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Default target
all: $(EXEC)

# Link object files to create the final executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create the obj directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean up build artifacts
clean:
	rm -f $(OBJ_DIR)/*.o $(EXEC)

# Phony targets
.PHONY: all clean

