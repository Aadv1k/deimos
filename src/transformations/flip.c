#include "../include/transformations/rotate.h"
#include "../include/transformations/rotate.h"

#include <assert.h>


void deimos_flipX(Image * img) {
    int width = img->width,
        height = img->height,
        ch = img->channels;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width / 2; j++) {
            for (int c = 0; c < ch; c++) {
                rotationSwap(
                    &img->bytes[(i * width + j) * ch + c],
                    &img->bytes[(i * width + (width - j - 1)) * ch + c]
                );
            }
        }
    }
}

void deimos_flipY(Image * img) {
    int width = img->width,
        height = img->height,
        ch = img->channels;

    for (int i = 0; i < height / 2; i++) {
        for (int j = 0; j < width; j++) {
            for (int c = 0; c < ch; c++) {
                rotationSwap(
                    &img->bytes[(i * width + j) * ch + c],
                    &img->bytes[((height - i - 1) * width + j) * ch + c]
                );
            }
        }
    }
}
