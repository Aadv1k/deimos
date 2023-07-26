SRC_DIR := src
INC_DIR := ./src/include
OBJ_DIR := obj
BIN_DIR := bin

CC := gcc
CFLAGS := -Wall -Werror -Wextra -std=c99
LIBS := -lm

SRCS := $(wildcard $(SRC_DIR)/*.c)
SRCS += $(wildcard $(SRC_DIR)/smoothing/*.c)
SRCS += $(wildcard $(SRC_DIR)/edge-detection/*.c)
SRCS += $(wildcard $(SRC_DIR)/thresholding/*.c)
SRCS += $(wildcard $(SRC_DIR)/feature-extraction/*.c)
SRCS += $(wildcard $(SRC_DIR)/transformations/*.c)

OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

EXEC := $(BIN_DIR)/deimos

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
ifeq ($(OS), Windows_NT)
		IF NOT EXIST "$(BIN_DIR)" MKDIR "$(BIN_DIR)"
else
		mkdir -p $(BIN_DIR)
endif
	$(CC) $(CFLAGS) -I$(INC_DIR) $^ -o $@ $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
ifeq ($(OS), Windows_NT)
		IF NOT EXIST "$(@D)" MKDIR "$(@D)"
else
		mkdir -p $(@D)
endif
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

clean:
ifeq ($(OS), Windows_NT)
		rmdir /s /q $(OBJ_DIR)
		rmdir /s /q $(BIN_DIR)
else
		rm -rf $(OBJ_DIR) $(BIN_DIR)
endif
