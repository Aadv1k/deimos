#include "../include/feature-extraction/harris.h"
#include "../include/smoothing/blur.h"
#include "../include/smoothing/grayscale.h"

#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


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
    cv_apply_gaussian_blur(img, 3, 5);

    int height = img->height,
        width = img->width;

    for (int i = 1; i < height - 1; i++) {
        for (int j = 1; j < width - 1; j++) {

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

            int neighborhood_size = 3; // Adjust this as needed for the size of the neighborhood

            if (R < threshold) continue;

            // Perform non-maximum suppression
            float angle = atan2(sumY, sumX); // Calculate the gradient angle
            float angle_degrees = angle * 180.0 / M_PI;
            if (angle_degrees < 0) angle_degrees += 180.0;

            int max_in_neighborhood = 1;
            for (int y = -neighborhood_size; y <= neighborhood_size && max_in_neighborhood; y++) {
                for (int x = -neighborhood_size; x <= neighborhood_size; x++) {
                    if (R < img->bytes[(i + y) * width + j + x]) {
                        max_in_neighborhood = 0;
                        break;
                    }
                }
            }

            // Check if the gradient angle is close to horizontal or vertical (corner-like)
            // If not, set the pixel intensity to 0, else retain it as a corner
            if (max_in_neighborhood && (angle_degrees < 45.0 || angle_degrees > 135.0)) {
                img->bytes[i * width + j] = 255; // Replace this with a suitable value for corner visualization
            } else {
                img->bytes[i * width + j] = 0;
            }

        }
    }
}
