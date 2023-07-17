@echo off

IF NOT EXIST "bin/" MKDIR "bin/"

SET CC=gcc
SET CFLAGS=-Wall -Werror -Wextra -std=c99
SET LIB=-lm

SET SRCS=src/main.c src/image.c src/smoothing/*.c src/edge-detection/*.c src/thresholding/*.c

SET INCLUDE_DIR=include

%CC% %CFLAGS% -I %INCLUDE_DIR% %SRCS% -o bin/cv.exe %LIB%
