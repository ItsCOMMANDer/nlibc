SILENTCMD := @
SILENTMSG := @echo

TARGET := nlibc.a

CC := gcc
LD := gcc
AR := ar

CFLAGS := -Wall -Werror -Wextra -Wpedantic -Wconversion -Wshadow
LDFLAGS := 

SRC_DIRS := src

SRC_FILES := $(foreach file,$(SRC_DIRS), $(wildcard $(file)/*c))

OBJ_FILES := $(SRC_FILES:.c=.o)

INCLUDE_DIRS := include

INCLUDES := $(foreach include, $(INCLUDE_DIRS), -I$(include))

LIBS := 

LIB := $(foreach library, $(LIBS), -l$(library))

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(SILENTMSG) $(ar) rcs  $@ $^
	$(SILENTCMD)$(AR) rcs $@ $^

%.o: %.c
	$(SILENTMSG) $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $^
	$(SILENTCMD)$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $^

clean:
	$(SILENTMSG) rm $(OBJ_FILES) $(TARGET)
	$(SILENTCMD)rm -f $(OBJ_FILES) $(TARGET)