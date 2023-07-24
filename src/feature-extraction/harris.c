#include "../include/feature-extraction/harris.h"
#include "../include/smoothing/blur.h"
#include "../include/smoothing/grayscale.h"

#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>

#define SOBEL_K_SIZE 3

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

bool isLocalMaximum(float R, int row, int col, Image* img) {
    int windowSize = 3;
    int halfWindow = windowSize / 2;

    for (int i = -halfWindow; i <= halfWindow; i++) {
        for (int j = -halfWindow; j <= halfWindow; j++) {
            if (i == 0 && j == 0) continue;
            int neighborRow = row + i;
            int neighborCol = col + j;
            if (neighborRow >= 0 && neighborRow < img->height &&
                neighborCol >= 0 && neighborCol < img->width) {
                float neighborR = img->bytes[neighborRow * img->width + neighborCol];
                if (R <= neighborR) {
                    return false;
                }
            }
        }
    }
    return true;
}

void cv_harris_detect_corners(Image* img, float threshold) {
    cv_apply_grayscale(img);
    cv_apply_gaussian_blur(img, 10, 9);

    for (int i = 1; i < img->height - 1; i++) {
        for (int j = 1; j < img->width - 1; j++) {

            int sumX = 0, sumY = 0;

            for (int y = 0; y < SOBEL_K_SIZE; y++) {
                for (int x = 0; x < SOBEL_K_SIZE; x++) {
                    int currentPixel = ((i + y - 1) * img->width) + (j + x - 1);
                    sumX += img->bytes[currentPixel] * kernelX[y][x];
                    sumY += img->bytes[currentPixel] * kernelY[y][x];
                }
            }

            float Ixx = sumX * sumX;
            float Ixy = sumX * sumY;
            float Iyy = sumY * sumY;

            float k = 0.04;
            float detM = (Ixx * Iyy) - (Ixy * Ixy);
            float traceM = Ixx + Iyy;
            float R = detM - k * (traceM * traceM);

            if (R > threshold) {

                if (isLocalMaximum(R, i, j, img)) {
                    img->bytes[i * img->width + j] = 0;
                }
            }
        }
    }
}
