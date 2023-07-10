@echo off

IF NOT EXIST "bin/" MKDIR "bin/"

SET CC=gcc
SET CFLAGS=-Wall -Werror

SET SRCS=main.c

%CC% %CFLAGS% %SRCS% -o bin/output.exe

.\bin\output.exe
