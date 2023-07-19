#include "../include/smoothing/box.h"

#include <stdlib.h>
#include <string.h>

void cv_apply_box_filter(Image *img, int kernSize) {
    int width = img->width, height = img->height, ch = img->channels, halfKernSize = kernSize / 2;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int sumR = 0, sumG = 0, sumB = 0;
            int count = 0;

            for (int y = -halfKernSize; y <= halfKernSize; y++) {
                for (int x = -halfKernSize; x <= halfKernSize; x++) {
                    int yy = i + y;
                    int xx = j + x;

                    if (yy < 0 || yy >= height || xx < 0 || xx >= width)
                        continue;

                    sumR += img->bytes[(yy * width + xx) * ch + 0];
                    sumG += img->bytes[(yy * width + xx) * ch + 1];
                    sumB += img->bytes[(yy * width + xx) * ch + 2];
                    count++;
                }
            }

            img->bytes[(i * width + j) * ch + 0] = (unsigned char)(sumR / count);
            img->bytes[(i * width + j) * ch + 1] = (unsigned char)(sumG / count);
            img->bytes[(i * width + j) * ch + 2] = (unsigned char)(sumB / count);
        }
    }
}
