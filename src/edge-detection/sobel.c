#include "../include/edge-detection/sobel.h"
#include "../include/smoothing/grayscale.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define SOBEL_K_SIZE 3


static int kernelX[SOBEL_K_SIZE][SOBEL_K_SIZE] = {
  {-1, 0, 1},
  {-2, 0, 2},
  {-1, 0, 1}
};

static int kernelY[SOBEL_K_SIZE][SOBEL_K_SIZE] = {
  {-1, -2, -1},
  {0, 0, 0},
  {1, 2, 1}
};

void cv_apply_sobel_filter(Image* img, int magnitude) {
  cv_apply_grayscale(img);

  int width = img->width,
      height = img->height;

  for (int i = 1; i <= height - 4; i++) {
    for (int j = 1; j <= width - 4; j++) {
      int sumX = 0, sumY = 0;

      for (int x = 0; x < SOBEL_K_SIZE; x++) {
        for (int y = 0; y < SOBEL_K_SIZE; y++) {
            int currentPixel = ((i + y) * width) + j + x;
            sumX += img->bytes[currentPixel] * kernelX[y][x];
            sumY += img->bytes[currentPixel] * kernelY[y][x];
        }
      }

      int gradientMagnitude = sqrt((sumX * sumX) + (sumY * sumY));
      //int gradientDirection = atan2(sumY, sumX);

      img->bytes[i * width + j] = gradientMagnitude > magnitude ? 255 : 0;
    }
  }
}

