#include "../include/thresholding/otsu.h"
#include "../include/logging.h"
#include "../include/smoothing/grayscale.h"
#include "../include/thresholding/global.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

#define GRAYSCALE 256

void cv_apply_otsu_threshold(Image *img) {
    cv_apply_grayscale(img);

    int imgLength = img->width * img->height * img->channels;

    int histogram[GRAYSCALE] = {0};
    for (int i = 0; i < imgLength; i++) {
        histogram[img->bytes[i]]++;
    }

    float normHistogram[GRAYSCALE] = {0};
    for (int i = 0; i < GRAYSCALE; i++) {
        normHistogram[i] = (float)histogram[i] / imgLength;
    }

    float cumulativeSum = normHistogram[0], cumulativeMean = 0.0;

    float globalMean = 0.0, classVariance = 0.0, maxVariance = 0.0;

    int optimalThreshold = 0;

    for (int i = 0; i < GRAYSCALE; i++) {
        cumulativeSum += normHistogram[i];
        cumulativeMean += i * normHistogram[i];

        globalMean += i * normHistogram[i];

        float mean1 = cumulativeMean / cumulativeSum,
              mean2 = (globalMean - cumulativeMean) / (1 - cumulativeSum);

        classVariance = cumulativeSum * (1 - cumulativeSum) * (mean1 - mean2) * (mean1 - mean2);

        if (classVariance > maxVariance) {
            maxVariance = classVariance;
            optimalThreshold = i;
        }
    }

    CV_INFO("Applying optimal threshold of %d\n", optimalThreshold);
    cv_apply_global_threshold(img, optimalThreshold);
}
