#include "../include/transformations/rotate.h"
#include <assert.h>

void rotationSwap(unsigned char* x, unsigned char* y) {
    unsigned char temp = *x;
    *x = *y;
    *y = temp;
}

void deimos_apply_rotation(Image* img, RotationDegree deg) {

    int width = img->width,
        height = img->height,
        ch = img->channels;

    switch (deg) {
    case (DEG_180):
        for (int i = 0; i < height / 2; i++) {
            for (int j = 0; j < width; j++) {
                for (int c = 0; c < ch; c++) {
                  rotationSwap(
                               &img->bytes[(i * width + j) * ch + c],
                               &img->bytes[((height - 1 - i) * width + (width - 1 - j)) * ch + c]
                    );
                }
            }
        }
        break;
    default:
        assert(0 && "Not a valid degree");
    }
}
