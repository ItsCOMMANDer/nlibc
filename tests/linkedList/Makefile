SILENTCMD := @
SILENTMSG := @echo

TARGET := linkedListTest

CC := gcc

CFLAGS := -Wall -Werror -Wextra -Wpedantic -Wconversion -Wshadow
LDFLAGS := 

SRC_DIRS := .

SRC_FILES := $(foreach file,$(SRC_DIRS), $(wildcard $(file)/*c))

OBJ_FILES := $(SRC_FILES:.c=.o)

INCLUDE_DIRS := ../../include

INCLUDES := $(foreach include, $(INCLUDE_DIRS), -I$(include))

LIBS_PATHS := ../..

LIB_PATH := $(foreach library_path, $(LIBS_PATHS), -L$(library_path))

LIBS := nlibc

LIB := $(foreach library, $(LIBS), -l$(library))

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(SILENTMSG) $(CC) $^ -o $@ $(LIB_PATH) $(LIB)
	$(SILENTCMD)$(CC) $^ -o $@ $(LIB_PATH) $(LIB)

%.o: %.c
	$(SILENTMSG) $(CC) $(CFLAGS) $(INCLUDES) $(LIB_PATH) -c -o $@ $^
	$(SILENTCMD)$(CC) $(CFLAGS) $(INCLUDES) $(LIB_PATH) -c -o $@ $^

clean:
	$(SILENTMSG) rm $(OBJ_FILES) $(TARGET)
	$(SILENTCMD)rm -f $(OBJ_FILES) $(TARGET)