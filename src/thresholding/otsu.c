#include "../include/thresholding/otsu.h"
#include "../include/thresholding/global.h"
#include "../include/smoothing/grayscale.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

#define GRAYSCALE 256

void cv_apply_otsu_threshold(Image *img) {
    cv_apply_grayscale(img);
    assert(img->channels == 1 && "Image must be grayscale");

    int height = img->height;
    int width = img->width;

    int histogram[GRAYSCALE] = {0};
    for (int i = 0; i < width * height; i++) {
        histogram[img->bytes[i]]++;
    }

    int totalSum = 0;
    int sumSquares = 0;
    int totalPixels = width * height;

    for (int i = 0; i < GRAYSCALE; i++) {
        totalSum += i * histogram[i];
        sumSquares += i * i * histogram[i];
    }

    int optimalThreshold = 0;
    double maximalVariance = -1.0;

    for (int i = 0; i < GRAYSCALE; i++) {
        int bgPixels = 0;
        int bgSum = 0;

        for (int j = 0; j <= i; j++) {
            bgPixels += histogram[j];
            bgSum += j * histogram[j];
        }

        int fgPixels = totalPixels - bgPixels;
        if (fgPixels == 0) {
            continue;
        }

        double bgMean = (double)bgSum / bgPixels;
        double fgMean = (double)(totalSum - bgSum) / fgPixels;

        double variance = (double)(bgPixels * fgPixels) * pow(bgMean - fgMean, 2);

        if (variance > maximalVariance) {
            maximalVariance = variance;
            optimalThreshold = i;
        }
    }

    cv_apply_global_threshold(img, optimalThreshold);
}
