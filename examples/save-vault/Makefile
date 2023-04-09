TARGET := save-vault

SOURCE_DIR := ../../source
OBJECT_DIR := obj
BUILD_DIR  := build

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SOURCE_FILES := $(call rwildcard,$(SOURCE_DIR),*.c) main.c
OBJECT_FILES := $(patsubst $(SOURCE_DIR)/%.c,$(OBJECT_DIR)/%.o,$(SOURCE_FILES))

CC := gcc
CFLAGS := -fno-exceptions -fshort-enums

ifeq ($(OS),Windows_NT)
    RM = cmd /C rmdir /Q /S
else
    RM = rm -rf
endif

all: executable

debug: CFLAGS += -DDEBUG -g
debug: executable 

executable: $(OBJECT_FILES) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$(TARGET) $(OBJECT_FILES)

$(OBJECT_DIR):
	$(shell mkdir $(OBJECT_DIR))

$(BUILD_DIR):
	$(shell mkdir $(BUILD_DIR))

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.c | $(OBJECT_DIR)
	$(shell mkdir -p $(@D))
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJECT_DIR)
	$(RM) $(BUILD_DIR)
