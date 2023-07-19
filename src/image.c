#include "include/image.h"

#include <stdlib.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "lib/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "lib/stb_image_write.h"

#include "include/logging.h"

void cv_load_image(Image *image) {
    image->bytes = (unsigned char *)stbi_load(image->path, &(image->width), &(image->height),
                                              &(image->channels), 0);
    if (image->bytes == NULL) {
        CV_ERROR("unable to load image %s", image->path);
        exit(1);
    }
}

Image *cv_deepcopy_image(const Image *original) {
    Image *copy = (Image *)malloc(sizeof(Image));

    int dataSize = original->width * original->height * original->channels;
    copy->bytes = (unsigned char *)malloc(dataSize);

    memcpy(copy->bytes, original->bytes, dataSize);
    copy->path = strdup(original->path);
    copy->width = original->width;
    copy->height = original->height;
    copy->channels = original->channels;
    return copy;
}

void cv_free_deepcopy_image(Image *img) {
    free(img->bytes);
    free((void *)img->path);
    free(img);
}

void cv_write_image(Image *image, const char *name) {
    if (stbi_write_jpg(name, image->width, image->height, image->channels, image->bytes, 0) == 0) {
        CV_ERROR("unable to write PNG file %s", name);
        exit(1);
    }
}

void cv_free_image(Image *image) { free(image->bytes); }
