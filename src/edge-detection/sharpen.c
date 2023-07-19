
#include "../include/edge-detection/sharpen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/image.h"
#include "../include/smoothing/blur.h"
#include "../include/smoothing/grayscale.h"

void cv_apply_sharpening(Image *img, float strength, int kernSize) {
    // cv_apply_grayscale(img);

    size_t imgSize = img->width * img->height * img->channels;
    unsigned char *originalImage = (unsigned char *)malloc(imgSize * sizeof(unsigned char));
    memcpy(originalImage, img->bytes, imgSize * sizeof(unsigned char));

    cv_apply_gaussian_blur(img, strength, kernSize);

    unsigned char *blurredImage = (unsigned char *)malloc(imgSize * sizeof(unsigned char));
    memcpy(blurredImage, img->bytes, imgSize * sizeof(unsigned char));

    for (size_t i = 0; i < imgSize; i++) {
        int sharpenedValue = originalImage[i] + strength * (originalImage[i] - blurredImage[i]);
        if (sharpenedValue < 0)
            sharpenedValue = 0;
        if (sharpenedValue > 255)
            sharpenedValue = 255;
        img->bytes[i] = sharpenedValue;
    }

    free(originalImage);
    free(blurredImage);
}
