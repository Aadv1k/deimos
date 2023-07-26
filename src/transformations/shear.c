#include "../include/transformations/shear.h" 
#include <assert.h>
#include <stdlib.h> 

#define UNUSED(x) (void)(x)

void deimos_apply_horizontal_shearing(Image * img, int factor) {
    int width = img->width,
        height = img->height,
        ch = img->channels;

    // Calculate the new width after shearing
    int new_width = width + (int)(factor * height);

    // Create a new image with the sheared dimensions
    Image* sheared_img = (Image*)malloc(sizeof(Image));
    sheared_img->width = new_width;
    sheared_img->height = height;
    sheared_img->channels = ch;
    sheared_img->bytes = (unsigned char*)malloc(new_width * height * ch);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < new_width; j++) {
            for (int c = 0; c < ch; c++) {
                int original_x = (int)(j - factor * i);

                if (original_x < 0) original_x = 0;
                if (original_x >= width) original_x = width - 1;

                sheared_img->bytes[(i * new_width + j) * ch + c] = img->bytes[(i * width + original_x) * ch + c];
            }
        }
    }

    free(img->bytes);

    img->width = sheared_img->width;
    img->height = sheared_img->height;
    img->channels = sheared_img->channels;
    img->bytes = sheared_img->bytes;

    free(sheared_img);
}


void deimos_apply_vertical_shearing(Image* img, int factor) {
    int width = img->width,
        height = img->height,
        ch = img->channels;

    int new_height = height + (int)(factor * width);

    Image* sheared_img = (Image*)malloc(sizeof(Image));
    sheared_img->width = width;
    sheared_img->height = new_height;
    sheared_img->channels = ch;
    sheared_img->bytes = (unsigned char*)malloc(width * new_height * ch);

    for (int i = 0; i < new_height; i++) {
        for (int j = 0; j < width; j++) {
            for (int c = 0; c < ch; c++) {
                int original_y = (int)(i - factor * j);

                if (original_y < 0) original_y = 0;
                if (original_y >= height) original_y = height - 1;

                sheared_img->bytes[(i * width + j) * ch + c] = img->bytes[(original_y * width + j) * ch + c];
            }
        }
    }

    free(img->bytes);

    img->width = sheared_img->width;
    img->height = sheared_img->height;
    img->channels = sheared_img->channels;
    img->bytes = sheared_img->bytes;

    free(sheared_img);
}
