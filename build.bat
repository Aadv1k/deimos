@echo off

IF NOT EXIST "bin/" MKDIR "bin/"

SET CC=gcc
SET CFLAGS=-Wall -Werror -Wextra -std=c99
SET LIB=-lm

SET SMOOTHING_SRC=.\smoothing\blur.c .\smoothing\grayscale.c .\smoothing\median.c .\smoothing\bilateral.c .\smoothing\box.c
SET EDGE_DETECTION_SRC=.\edge-detection\sharpen.c .\edge-detection\laplacian.c .\edge-detection\sobel.c
SET SRCS=main.c image.c %SMOOTHING_SRC% %EDGE_DETECTION_SRC%

%CC% %CFLAGS% %SRCS% -o bin/cv.exe %LIB%
