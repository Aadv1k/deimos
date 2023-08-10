#include "../include/edge-detection/laplacian.h"

#include "../include/smoothing/blur.h"
#include "../include/smoothing/box.h"

#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void cv_apply_laplacian_filter(Image *img, float sigma, int kernSize) {
    int width = img->width;
    int height = img->height;
    int channels = img->channels;

    int kernSize1 = kernSize * 1.5 + 1;

    (void)sigma;
    //cv_apply_gaussian_blur(img, sigma, kernSize1);
    cv_apply_box_filter(img, kernSize1);

    Image copiedImage;
    copiedImage.width = width;
    copiedImage.height = height;
    copiedImage.channels = channels;

    size_t dataSize = width * height * channels * sizeof(unsigned char);
    copiedImage.bytes = malloc(dataSize);
    memcpy(copiedImage.bytes, img->bytes, dataSize);

    //cv_apply_gaussian_blur(&copiedImage, sigma, kernSize);
    cv_apply_box_filter(&copiedImage, kernSize);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            for (int c = 0; c < channels; c++) {
                int index = (i * width + j) * channels + c;
                img->bytes[index] = img->bytes[index] - copiedImage.bytes[index];
            }
        }
    }

    free(copiedImage.bytes);
}
