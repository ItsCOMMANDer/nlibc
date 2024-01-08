# Thx chat gpt

# Makefile

# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -std=c11

# Directories
SRC_DIR := ./lib
OBJ_DIR := ./build/objects
LIB_DIR := ./build/lib

# Source files
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Targets
all: mystd.lib mystd.a

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Combine object files into mystd.o
mystd.o: $(OBJ_FILES)
	ld -r -o $@ $^

# Create static library (.lib) for Windows
mystd.lib: mystd.o
	ar rcs $(LIB_DIR)/$@ $^

# Create static library (.a) for Linux
mystd.a: mystd.o
	ar rcs $(LIB_DIR)/$@ $^

clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f $(LIB_DIR)/*.lib $(LIB_DIR)/*.a

.PHONY: all clean
