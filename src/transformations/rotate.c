#include "../include/transformations/rotate.h"
#include <assert.h>
#include <stdlib.h>

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
     case (DEG_90):
        Image* rotated_img = (Image*)malloc(sizeof(Image));
        rotated_img->width = height;
        rotated_img->height = width;
        rotated_img->channels = ch;
        rotated_img->bytes = (unsigned char*)malloc(rotated_img->width * rotated_img->height * rotated_img->channels);

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                for (int c = 0; c < ch; c++) {
                    rotated_img->bytes[(j * rotated_img->width + (height - 1 - i)) * ch + c] = img->bytes[(i * width + j) * ch + c];
                }
            }
        }

        free(img->bytes);

        img->width = rotated_img->width;
        img->height = rotated_img->height;
        img->channels = rotated_img->channels;
        img->bytes = rotated_img->bytes;

        free(rotated_img);
        break;
       break;
    default:
        assert(0 && "Not a valid degree");
    }
}
