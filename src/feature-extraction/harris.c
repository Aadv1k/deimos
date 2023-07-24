#include "../include/feature-extraction/harris.h"
#include "../include/smoothing/blur.h"
#include "../include/smoothing/grayscale.h"

#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>

#define SOBEL_K_SIZE 3
#define HARRIS_K_CONST 0.04

static int kernelX[SOBEL_K_SIZE][SOBEL_K_SIZE] = {
    {-1, 0, 1},
    {-2, 0, 2},
    {-1, 0, 1}
};

static int kernelY[SOBEL_K_SIZE][SOBEL_K_SIZE] = {
    {1, 2, 1},
    {0, 0, 0},
    {-1, -2, -1}
};


void cv_harris_detect_corners(Image* img, float threshold) {
    cv_apply_grayscale(img);
    cv_apply_gaussian_blur(img, 3, 9);

    int height = img->height,
        width = img->width;

    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {

        int sumX = 0, sumY = 0;

        for (int y = 0; y < SOBEL_K_SIZE; y++) {
          for (int x = 0; x < SOBEL_K_SIZE; x++) {
            unsigned char currentPixel = img->bytes[(i + y) * width + x + j];
            sumX += kernelX[y][x] * currentPixel;
            sumY += kernelY[y][x] * currentPixel;
          }
        }


        int Ixx = sumX * sumX; 
        int Ixy = sumX * sumY;
        int Iyy = sumY * sumY;

        int detM = (Ixx * Iyy) - (Ixy * Ixy);
        int traceM = Ixx + Iyy;
        float R = detM - HARRIS_K_CONST * (traceM * traceM);

        if (R > threshold) {
          img->bytes[(i * width) + j] = 0;
        }
      }
    }
}
