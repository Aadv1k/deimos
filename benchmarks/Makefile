SRC_DIR := ../src
BIN_DIR := ../bin

CC := gcc
CFLAGS := -Wall -Werror -Wextra -std=c99
LIBS := -lm

.PHONY: all smoothing/box

all: smoothing/box

smoothing/box:
	$(CC) $(CFLAGS) $(SRC_DIR)/smoothing/box.c $(SRC_DIR)/image.c ./boxFilter.c -o $(BIN_DIR)/smoothing_box.benchmark.exe
