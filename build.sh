#/usr/bin/env bash 


mkdir -p bin

CC="gcc"
CLFAGS="-Wall -Werror"
SRCS="main.c"

$CC $CFLAGS $SRCS -o bin/output
