# Directories
SRC_DIR := src
OBJ_DIR := obj
INCLUDE_DIR := include
RAYLIB_DIR := /home/anurag/try/raylib/src

# Compiler and flags for native build
CC := gcc
CFLAGS := -I$(INCLUDE_DIR) -g -Wall -Wextra -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Emscripten compiler and flags
EMCC := emcc
EMFLAGS := -I$(INCLUDE_DIR) -I$(RAYLIB_DIR) -O3 -s USE_WEBGL2=1 -s USE_SDL=2 -s ALLOW_MEMORY_GROWTH=1 -DPLATFORM_WEB -s USE_GLFW=3

# Executable names
EXEC := spacebuddy
WEB_EXEC := spacebuddy.html

# Find all source files and corresponding object files
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Default target
all: $(EXEC)

# Link object files to create the final executable for native build
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create the obj directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Build for web using Emscripten
web:
	mkdir -p game
	$(EMCC) $(SRCS) -o game/$(WEB_EXEC) -I$(INCLUDE_DIR) -I$(RAYLIB_DIR) -L$(RAYLIB_DIR) -lraylib $(EMFLAGS) --shell-file /home/anurag/try/raylib/src/minshell.html -s ASYNCIFY --preload-file images --preload-file sound

# Clean up build artifacts
clean:
	rm -f $(OBJ_DIR)/*.o $(EXEC) $(WEB_EXEC)

# Phony targets
.PHONY: all clean web
