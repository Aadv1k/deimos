@echo off

IF NOT EXIST "bin/" MKDIR "bin/"

SET CC=gcc
SET CFLAGS=-Wall -Werror
SET LIB=-lm

SET FILTERS_SRC=.\filters\blur.c .\filters\grayscale.c .\filters\median.c .\filters\bilateral.c .\filters\box.c
SET EDGE_DETECTORS_SRC=.\edge-detectors\sharpen.c .\edge-detectors\laplacian.c .\edge-detectors\sobel.c
SET SRCS=main.c image.c %FILTERS_SRC% %EDGE_DETECTORS_SRC%

%CC% %CFLAGS% %SRCS% -o bin/cv.exe %LIB%
