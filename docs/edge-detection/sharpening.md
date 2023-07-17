# Sharpening

If we think about sharpening an image what comes in mind? a [deep fried image](https://i.kym-cdn.com/photos/images/original/002/562/129/204.jpg)? well probably not. Sharpening refers to accentuating the edges of an image such that they appear more prominent their sorroundings. This has several use cases, from enhancing the quality of the images to identifying and making out shapes from grainy footage.

*Unsharp mask* is one such technique to get this done. We first copy the original image, we then apply blur on this image. If you think about it sharpening is really just taking the prominent edges from a blurred image using their prominence as a weight factor to highlight the edges of the original images. These prominent features are known as "High-Pass" since in a blurred image they are more prominent than "low-Pass" features which get smoothed out.


## Implementation

```c
void cv_apply_sharpening(Image *img, float strength, int kernSize) {
  cv_apply_grayscale(img);

  /* ... */

  cv_apply_gaussian_blur(img, strength, kernSize);

  for (size_t i = 0; i < imgSize; i++) {
    originalImage[i] += (originalImage[i] - blurredImage[i]) * strength;
  }
  /* ... */
}
```

- We first convert the image to grayscale, which is one of the preprocessing steps commonly used for image sharpening. Grayscale conversion simplifies the calculations and allows us to ignore things like lighthing

- Apply the Gaussian Blur to obtain an image where the smaller details get smoothed out in comparision to more prominent features (eg the shape of a flower, but not the texture)

- We then iteratively add the difference of the origianl image and the blurred image to the original image, this difference will be lower in case of smooth regions, and higher in case of more prominent regions, we multiply this with a `sigma` factor which allows us to control the strength of the effect.
