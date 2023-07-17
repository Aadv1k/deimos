#include "../include/smoothing/median.h"
#include <assert.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

void swap(unsigned char* a, unsigned char* b) {
    unsigned char temp = *a;
    *a = *b;
    *b = temp;
}

int partition(unsigned char arr[], int low, int high) {
    unsigned char pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(unsigned char arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

unsigned char calculate_median(unsigned char* pixelValues, int size) {
    quickSort(pixelValues, 0, size - 1);

    unsigned char median;
    if (size % 2 == 0) {
        median = (pixelValues[size / 2 - 1] + pixelValues[size / 2]) / 2;
    } else {
        median = pixelValues[size / 2];
    }
    return median;
}

void cv_apply_median_filter(Image* img, int size) {
    assert(size > 0 && "Size can't be zero");

    int ch = img->channels;

    unsigned char* tempBytes = (unsigned char*)malloc(img->width * img->height * ch * sizeof(unsigned char));

    for (int i = 0; i < img->height; ++i) {
        for (int j = 0; j < img->width; ++j) {
            unsigned char* pixelValues = (unsigned char*)malloc(size * size * ch * sizeof(unsigned char));
            int pixelCount = 0;

            for (int k = 0; k < size; ++k) {
                for (int l = 0; l < size; ++l) {
                    int row = i + k - size / 2;
                    int col = j + l - size / 2;

                    if (row >= 0 && row < img->height && col >= 0 && col < img->width) {
                        for (int c = 0; c < ch; ++c) {
                            pixelValues[pixelCount++] = img->bytes[(row * img->width + col) * ch + c];
                        }
                    }
                }
            }

            for (int c = 0; c < ch; ++c) {
              unsigned char medianValue = calculate_median(pixelValues, pixelCount);
              tempBytes[(i * img->width + j) * ch + c] = medianValue;
            }

            free(pixelValues);
        }
    }

    memcpy(img->bytes, tempBytes, img->width * img->height * ch * sizeof(unsigned char));
    free(tempBytes);
}
