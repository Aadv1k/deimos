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

#include "include/logging.h"

void usage(const char *caller) {
  printf("Usage:\n");
  printf("\t%s <args> input output\n", caller);
  printf("Examples:\n");
  printf("\t%s --blur --sigma 3.4 --kernel 5 input.png output.png\n", caller);
  printf("\t%s --gray input.png output.png\n", caller);
  printf("\t%s --median --kernel 3 input.png output.png\n", caller);
  printf("\t%s --sharpen --sigma 0.6 --kernel 3 input.png output.png\n", caller);
  printf("Options:\n");
  printf("\t--help                print this help message\n");
  printf("\t--blur, --gaussian    apply gaussian blur to the image\n");
  printf("\t--median              apply median filter to the image\n");
  printf("\t--sobel               apply sobel filter to the image\n");
  printf("\t--bilateral           apply bilateral filter to the image\n");
  printf("\t--box, --mean         apply box filter onto the image\n");
  printf("\t--laplacian           apply laplacian filter onto the image\n");
  printf("\t--gray                convert image to grayscale\n");
  printf("\t--sharpen             sharpen image via an unsharp mask\n");
  printf("\t--global-threshold    apply the global threshold filter over the image, `sigma` would be the threshold\n");
  printf("\t--otsu-threshold      apply the Otsu's threshold filter over the image\n");
  printf("\t--sigma               specify the sigma for the convolutions\n");
  printf("\t--kernel              define the kernel size for convolutions (if applicable)\n");
}

int main(int argc, char **argv) {
  const char *caller = argv[0];

  if (argc == 1) {
    usage(caller);
    exit(1);
  }

  int enableBlur = 0;
  int enableGrayscale = 0;
  int enableSharpen = 0;
  int enableMedian = 0;
  int enableBilateral = 0;
  int enableBox = 0;
  int enableLaplacian = 0;
  int enableSobel = 0;
  int enableGlobalThreshold = 0;
  int enableOtsuThreshold = 0;

  int cmdc = 0;

  float sigma = 1.0;
  int kernelSize = 3;

  for (int i = 1; i < argc; i++) {
    const char *current = argv[i];

    if (strcmp(current, "--blur") == 0 || strcmp(current, "--gaussian") == 0) {
      enableBlur = 1;
      cmdc++;
    } else if (strcmp(current, "--bilateral") == 0)  {
      enableBilateral = 1;
      cmdc++;
    } else if (strcmp(current, "--median") == 0) {
      enableMedian = 1;
      cmdc++;
    } else if (strcmp(current, "--box") == 0 || strcmp(current, "--mean") == 0) {
      enableBox = 1;
      cmdc++;
    } else if (strcmp(current, "--laplacian") == 0) {
      enableLaplacian = 1;
      cmdc++;
    } else if (strcmp(current, "--sobel") == 0) {
      enableSobel = 1;
      cmdc++;
    } else if (strcmp(current, "--sharpen") == 0) {
      enableSharpen = 1;
      cmdc++;
    } else if (strcmp(current, "--gray") == 0) {
      enableGrayscale = 1;
      cmdc++;
    } else if (strcmp(current, "--global-threshold") == 0) {
      enableGlobalThreshold = 1;
      cmdc++;
    } else if (strcmp(current, "--otsu-threshold") == 0) {
      enableOtsuThreshold = 1;
      cmdc++;
    }
    else if (strcmp(current, "--sigma") == 0) {
      cmdc += 2;
      if (i + 1 < argc) {
        sigma = atof(argv[i + 1]);
        i++;
      } else {
        fprintf(stderr, "Error: --sigma requires a value.\n");
        exit(1);
      }
    } else if (strcmp(current, "--kernel") == 0) {
      cmdc += 2;

      if (i + 1 < argc) {
        kernelSize = atoi(argv[i + 1]);
        i++;
      } else {
        fprintf(stderr, "Error: --kernel requires a value.\n");
        exit(1);
      }
    } else if (strcmp(current, "--help") == 0) {
      usage(caller);
      exit(0);
    }
  }

  if (argc - cmdc <= 2) {
    usage(caller);
    exit(1);
  }

  if (kernelSize <= 1)  {
    CV_WARN("kernel can't be less than or equal to one; taking 3");
    kernelSize = 3;
  }

  if (sigma <= 0)  {
    CV_WARN("sigma can't be less than or equal to zero; taking 1");
    sigma = 1;
  }

  const char *input_path = argv[argc - 2];
  const char *output_path = argv[argc - 1];

  Image img = {.path = input_path};
  cv_load_image(&img);

  if (enableGrayscale) {
    CV_INFO("converting image to grayscale");
    cv_apply_grayscale(&img);
  }

  if (enableGlobalThreshold) {
    CV_INFO("applying global threshold of %d", (int)sigma);
    cv_apply_global_threshold(&img, (int)sigma);
  }

  if (enableOtsuThreshold) {
    CV_INFO("applying Otsu threshold filter");
    cv_apply_otsu_threshold(&img);
  }

  if (enableBlur) {
    CV_INFO("applying gaussian blur of intensity %.2f, kernel size %d", sigma, kernelSize);
    cv_apply_gaussian_blur(&img, sigma, kernelSize);
  }

  if (enableBilateral) {
    CV_INFO("applying bilateral filter of strength %.2f, kernel size %d", sigma, kernelSize);
    cv_apply_bilateral_filter(&img, sigma, kernelSize);
  }

  if (enableLaplacian) {
    CV_INFO("applying Laplacian filter of strength %.2f, kernel size %d", sigma, kernelSize);
    cv_apply_laplacian_filter(&img, sigma, kernelSize);
  }

  if (enableBox) {
    CV_INFO("applying box filter of kernel size %d", kernelSize);
    cv_apply_box_filter(&img, kernelSize);
  }

  if (enableSobel) {
    CV_INFO("applying Sobel filter");
    cv_apply_sobel_filter(&img);
  }

  if (enableMedian) {
    CV_INFO("applying median filter of kernel size %d", kernelSize);
    cv_apply_median_filter(&img, kernelSize);
  }

  if (enableSharpen) {
    CV_INFO("applying sharpening of strength %.2f, kernel size %d", sigma, kernelSize);
    cv_apply_sharpening(&img, sigma, kernelSize);
  }

  cv_write_image(&img, output_path);

  cv_free_image(&img);
  return 0;
}
