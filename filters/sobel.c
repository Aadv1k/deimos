#include "./sobel.h"
#include "./grayscale.h"
#include <stdlib.h>
#include <math.h>

unsigned char compute_sobel_from_pixel_3x3(Image* img, int x, int y) {
  int width = img->width;
  int resultX = 0;
  int resultY = 0;

  int sobelX[3][3] = {
    {-1, 0, 1},
    {-2, 0, 2},
    {-1, 0, 1}
  };

  int sobelY[3][3] = {
    {-1, -2, -1},
    {0, 0, 0},
    {1, 2, 1}
  };

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      int currentPixel = img->bytes[(y + i) * width + (x + j)];
      resultX += currentPixel * sobelX[i][j];
      resultY += currentPixel * sobelY[i][j];
    }
  }

  int gradient = abs(resultX) + abs(resultY);
  gradient = gradient > 255 ? 255 : gradient;
  return (unsigned char)(gradient);
}

unsigned char compute_sobel_from_pixel_5x5(Image* img, int x, int y) {
  int width = img->width;
  int resultX = 0;
  int resultY = 0;

  int sobelX[5][5] = {
    {-1, -2, 0, 2, 1},
    {-4, -8, 0, 8, 4},
    {-6, -12, 0, 12, 6},
    {-4, -8, 0, 8, 4},
    {-1, -2, 0, 2, 1}
  };

  int sobelY[5][5] = {
    {-1, -4, -6, -4, -1},
    {-2, -8, -12, -8, -2},
    {0, 0, 0, 0, 0},
    {2, 8, 12, 8, 2},
    {1, 4, 6, 4, 1}
  };

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      int pixel = img->bytes[(y + i) * width + (x + j)];
      resultX += pixel * sobelX[i][j];
      resultY += pixel * sobelY[i][j];
    }
  }

  int gradient = abs(resultX) + abs(resultY);
  gradient = gradient > 255 ? 255 : gradient;
  return (unsigned char)(gradient);
}

void cv_apply_sobel_filter(Image* img) {
  cv_apply_grayscale(img);

  int width = img->width;
  int height = img->height;

  for (int i = 1; i < height - 1; i++) {
    for (int j = 1; j < width - 1; j++) {
      img->bytes[i * width + j] = compute_sobel_from_pixel_5x5(img, j, i);
    }
  }
}

