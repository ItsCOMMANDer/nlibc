#! MADE BY CHATGPT, DO NOT CHANGE 

CC := gcc

TARGET := nlibc.a
BUILD := build
SOURCES := src
INCLUDES := include

INCLUDE := $(foreach dir, $(INCLUDES), -I$(dir))

CFILES := $(foreach dir, $(SOURCES), $(wildcard $(dir)/*.c))
OFILES := $(patsubst $(SOURCES)/%.c,$(BUILD)/%.o,$(CFILES))

FLAGS := -Wall -Wextra -fno-builtin

# Create the build directory if it doesn't exist
$(BUILD):
	mkdir -p $(BUILD)/output

all: $(BUILD)/output/$(TARGET)

$(BUILD)/output/$(TARGET): $(OFILES)
	ar rcs $@ $^

$(BUILD)/%.o: $(SOURCES)/%.c | $(BUILD)
	$(CC) -c $(FLAGS) $(INCLUDE) $< -o $@

clean:
	rm -rf $(BUILD)

.PHONY: all clean