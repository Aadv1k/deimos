#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/image.h"

#include "include/smoothing/blur.h"
#include "include/smoothing/grayscale.h"
#include "include/smoothing/median.h"
#include "include/smoothing/box.h"
#include "include/smoothing/bilateral.h"

#include "include/edge-detection/sharpen.h"
#include "include/edge-detection/laplacian.h"
#include "include/edge-detection/sobel.h"

#include "include/thresholding/global.h"
#include "include/thresholding/otsu.h"

#include "include/feature-extraction/harris.h"

#include "include/logging.h"

void usage(const char *caller) {
  printf("Usage:\n");
  printf("  %s <command> <args> input output\n\n", caller);

  // printf("Examples:\n");
  // printf("  %s blur --sigma 3.4 --kernel 5 input.png output.png\n", caller);
  // printf("  %s gray input.png output.png\n", caller);
  // printf("  %s median --kernel 3 input.png output.png\n", caller);
  // printf("  %s sharpen --sigma 0.6 --kernel 3 input.png output.png\n\n", caller);

  printf("Commands:\n");
  printf("  Smoothing:\n");
  printf("    blur, gaussian    Apply Gaussian blur to the image.\n");
  printf("    median            Apply median filter to the image.\n");
  printf("    bilateral         Apply bilateral filter to the image.\n");
  printf("    box, mean         Apply box filter onto the image.\n\n");

  printf("  Edge Detection:\n");
  printf("    sobel             Apply Sobel filter to the image.\n");
  printf("    laplacian         Apply Laplacian filter onto the image.\n");
  printf("    sharpen           Sharpen image via an unsharp mask.\n\n");

  printf("  Thresholding:\n");
  printf("    global-threshold  Apply the global threshold filter over the image. 'sigma' would be the threshold.\n");
  printf("    otsu-threshold    Apply Otsu's threshold filter over the image.\n\n");

  printf("  Feature Extraction:\n");
  printf("    harris-corners    Detect corners within the image via Harris corner detection.\n\n");

  printf("Other Commands:\n");
  printf("    gray              Convert image to grayscale.\n");
  printf("    help              Print this help message.\n\n");

  printf("Options:\n");
  printf("  --sigma             Specify the primary modifier for the convolutions.\n");
  printf("  --kernel            Define the kernel size for convolutions (if applicable).\n");
}

int main(int argc, char *argv[]) {
  const char *program = argv[0];

  if (argc <= 1) {
    usage(program);
    exit(1);
  }

  const char *operation = argv[1];
  float sigma = 1.0;
  int kernelSize = 3;
  char *input_path = NULL;
  char *output_path = NULL;

  for (int i = 2; i < argc; i++) {
    if (strcmp(argv[i], "--sigma") == 0) {
      if (i + 1 < argc) {
        sigma = atof(argv[i + 1]);
        i++;
      } else {
        CV_ERROR("--sigma requires a value.");
        exit(1);
      }
    } else if (strcmp(argv[i], "--kernel") == 0) {
      if (i + 1 < argc) {
        kernelSize = atoi(argv[i + 1]);
        i++;
      } else {
        CV_ERROR("--kernel requires a value.");
        exit(1);
      }
    } else {
      if (!input_path) {
        input_path = argv[i];
      } else if (!output_path) {
        output_path = argv[i];
      } else {
        CV_ERROR("Unknown option or extra argument provided.");
        usage(program);
        exit(1);
      }
    }
  }

  if (!input_path) {
    CV_ERROR("Input image path not provided.");
    exit(1);
  }

  if (!output_path) {
    CV_ERROR("Output image path not provided.");
    exit(1);
  }

  Image img = {.path = input_path};
  cv_load_image(&img);

  if (strcmp(operation, "blur") == 0 || strcmp(operation, "gaussian") == 0) {

    CV_INFO("applying gaussian blur of intensity %.2f, kernel size %d", sigma, kernelSize);
    cv_apply_gaussian_blur(&img, sigma, kernelSize);

  } else if (strcmp(operation, "bilateral") == 0)  {
    CV_INFO("applying bilateral filter of strength %.2f, kernel size %d", sigma, kernelSize);
    cv_apply_bilateral_filter(&img, sigma, kernelSize);
  } else if (strcmp(operation, "harris-corners") == 0)  {
    CV_INFO("extracting corners via Harris corner detection");
    cv_harris_detect_corners(&img);
  } else if (strcmp(operation, "median") == 0) {
    CV_INFO("applying median filter of kernel size %d", kernelSize);
    cv_apply_median_filter(&img, kernelSize);
  } else if (strcmp(operation, "box") == 0 || strcmp(operation, "mean") == 0) {
    CV_INFO("applying box filter of kernel size %d", kernelSize);
    cv_apply_box_filter(&img, kernelSize);
  } else if (strcmp(operation, "laplacian") == 0) {
    CV_INFO("applying Laplacian filter of strength %.2f, kernel size %d", sigma, kernelSize);
    cv_apply_laplacian_filter(&img, sigma, kernelSize);
  } else if (strcmp(operation, "sobel") == 0) {
    CV_INFO("applying Sobel filter of magnitude %d", (int)sigma);
    cv_apply_sobel_filter(&img, (int)sigma);
  } else if (strcmp(operation, "sharpen") == 0) {
    CV_INFO("applying sharpening of strength %.2f, kernel size %d", sigma, kernelSize);
    cv_apply_sharpening(&img, sigma, kernelSize);
  } else if (strcmp(operation, "gray") == 0) {
    CV_INFO("converting image to grayscale");
    cv_apply_grayscale(&img);
  } else if (strcmp(operation, "global-threshold") == 0) {
    CV_INFO("applying global threshold of %d", (int)sigma);
    cv_apply_global_threshold(&img, (int)sigma);
  } else if (strcmp(operation, "otsu-threshold") == 0) {
    CV_INFO("applying Otsu threshold filter");
    cv_apply_otsu_threshold(&img);
  } else {
    usage(program);
    exit(1);
  }

  cv_write_image(&img, output_path);
  cv_free_image(&img);
  return 0;
}
