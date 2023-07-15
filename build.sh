#!/bin/bash

# Create the bin directory if it doesn't exist
if [ ! -d "bin" ]; then
        mkdir bin
        fi

# Set the compiler and flags
CC=gcc
CFLAGS="-Wall -Werror"
LIBS="-lm"

# Set the source files

SRCS="main.c image.c filters/blur.c filters/grayscale.c filters/sharpen.c filters/median.c filters/bilateral.c"

# Compile the source files
$CC $CFLAGS $SRCS -o bin/cv $LIBS

