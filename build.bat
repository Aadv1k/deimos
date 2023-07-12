@echo off

IF NOT EXIST "bin/" MKDIR "bin/"

SET CC=gcc
SET CFLAGS=-Wall -Werror

SET SRCS=main.c image.c .\filters\blur.c .\filters\grayscale.c .\filters\sharpen.c .\filters\median.c

%CC% %CFLAGS% %SRCS% -o bin/cv.exe
