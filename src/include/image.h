#ifndef IMAGE_H
#define IMAGE_H

typedef struct {
    unsigned char *bytes;
    const char *path;
    int width;
    int height;
    int channels;
} Image;

void cv_load_image(Image *image);
void cv_free_image(Image *image);
void cv_write_image(Image *image, const char *name);

Image *cv_deepcopy_image(const Image *original);
void cv_free_deepcopy_image(Image *img);

#endif
