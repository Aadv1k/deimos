#include "./include/contrast.h"
#include "./include/smoothing/grayscale.h"

unsigned char get_min_recursive(unsigned char *data, int start, int end, int channels) {
    if (start == end) {
        unsigned char min_value = 255;
        for (int i = 0; i < channels; i++) {
            if (data[start * channels + i] < min_value) {
                min_value = data[start * channels + i];
            }
        }
        return min_value;
    }

    int mid = (start + end) / 2;

    unsigned char min_left = get_min_recursive(data, start, mid, channels);
    unsigned char min_right = get_min_recursive(data, mid + 1, end, channels);

    return (min_left < min_right) ? min_left : min_right;
}

unsigned char get_max_recursive(unsigned char *data, int start, int end, int channels) {
    if (start == end) {
        unsigned char max_value = 0;
        for (int i = 0; i < channels; i++) {
            if (data[start * channels + i] > max_value) {
                max_value = data[start * channels + i];
            }
        }
        return max_value;
    }

    int mid = (start + end) / 2;

    unsigned char max_left = get_max_recursive(data, start, mid, channels);
    unsigned char max_right = get_max_recursive(data, mid + 1, end, channels);

    return (max_left > max_right) ? max_left : max_right;
}

unsigned char get_max(unsigned char *data, int width, int height, int channels) {
    return get_max_recursive(data, 0, width * height - 1, channels);
}

unsigned char get_min(unsigned char *data, int width, int height, int channels) {
    return get_min_recursive(data, 0, width * height - 1, channels);
}

void deimos_increase_contrast(Image* img, float contrast) {
    //cv_apply_grayscale(img);
    //unsigned char maxPixelValue = get_max(img->bytes, img->width, img->height, img->channels);
    unsigned char minPixelValue = get_min(img->bytes, img->width, img->height, img->channels);

    float scaleFactor = ((float)contrast / 100.0) + 1.0;

    for (int i = 0; i < img->width * img->height * img->channels; i++) {
        img->bytes[i] = (unsigned char)((img->bytes[i] - minPixelValue) * scaleFactor + minPixelValue);
    }
}
