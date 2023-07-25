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

void draw_circle(Image* img, int center_x, int center_y, int radius, unsigned char color) {
    int x = radius - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);

    while (x >= y) {
        img->bytes[(center_x + x) * img->width + center_y + y] = color;
        img->bytes[(center_x + y) * img->width + center_y + x] = color;
        img->bytes[(center_x - y) * img->width + center_y + x] = color;
        img->bytes[(center_x - x) * img->width + center_y + y] = color;
        img->bytes[(center_x - x) * img->width + center_y - y] = color;
        img->bytes[(center_x - y) * img->width + center_y - x] = color;
        img->bytes[(center_x + y) * img->width + center_y - x] = color;
        img->bytes[(center_x + x) * img->width + center_y - y] = color;

        if (err <= 0) {
            y++;
            err += dy;
            dy += 2;
        }
        if (err > 0) {
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }
}


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
    cv_apply_gaussian_blur(img, 3, 3);

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

            if (R < threshold) continue;

            // Perform non-maximum suppression
            float angle = atan2(sumY, sumX); // Calculate the gradient angle
            float angle_degrees = angle * 180.0 / M_PI;
            if (angle_degrees < 0) angle_degrees += 180.0;

            int neighborhood_size = 1; // Reduce the neighborhood size for better results

            int max_in_neighborhood = 1;
            for (int y = -neighborhood_size; y <= neighborhood_size && max_in_neighborhood; y++) {
                for (int x = -neighborhood_size; x <= neighborhood_size; x++) {
                    if (R < img->bytes[(i + y) * width + j + x]) {
                        max_in_neighborhood = 0;
                        break;
                    }
                }
            }

            if (max_in_neighborhood && (angle_degrees < 45.0 || angle_degrees > 135.0)) {
                img->bytes[i * width + j] = 0;
            }

            //else {img->bytes[i * width + j] = 0;}

        }
    }
}
