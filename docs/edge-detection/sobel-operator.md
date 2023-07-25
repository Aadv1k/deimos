# Sobel operator

Next on our list we have the sobel filter, yet another filter which serves to extract an outline map of the original image. The filter works quite simply,we just colvolvue a kernel of a determinate length, (3 for most cases) against a particular set of values. We sum this up and assign the current pixel the value after applying the gradient magnitue formula over it.

Comparing the Sobel Filter to the [Laplacian Filter](./laplacian-filter.md), we find that the Sobel operator is faster and generally produces cleaner output. However, there is a trade-off, as it may lose certain finer details in the image. This makes the Sobel filter particularly useful when we only need to focus on extracting the edges of larger objects in the image. For instance, in a self-driving car system, where detecting the car's boundaries is crucial, neglecting dust, scratches, or other minor details in favor of clear object boundaries becomes more important.


## Implementation

The sobel filter is implemented at [src/edge-detection/sobel.c](../../src/edge-detection/sobel.c) 


```c
void cv_apply_sobel_filter(Image *img, int magnitude) {
    cv_apply_grayscale(img);

    /* ... */
    
    for (int i = 0; i <= height; i++) {
        for (int j = 0; j <= width; j++) {

            for (int x = 0; x < SOBEL_K_SIZE; x++) {
                for (int y = 0; y < SOBEL_K_SIZE; y++) {

                    /* ... */

                    sumX += img->bytes[currentPixel] * kernelX[y][x];
                    sumY += img->bytes[currentPixel] * kernelY[y][x];
                }
            }

            int gradientMagnitude = sqrt((sumX * sumX) + (sumY * sumY));

            /* ... */

            img->bytes[i * width + j] = gradientMagnitude;
        }
    }
}
```

As you can see, we first convert the image to grayscale, looping across each pixel we then convulve each with an area of `SOBEL_K_SIZE` which in this case is `3`, we then add to the `sumX` and the `sumY` the kernels.

Let's actually loook at the kernels in question

```c

static int kernelY[3][3] = {
  {-1, 0, 1}
  (-2, 0, 2}
  {-1, 0, 1}
};

static int kernelX[3][3] = {
  {1, 2, 1}
  (0, 0, 0}
  {-1, -2, -1}

}
```

Each kernel serves to calculate the gradient of the image in a particular direction, this will create a "ghost" like imprint of the edges for each of the gradient directions, on extracting the root of the squared sum we can effectively extract the edges.

```
int gradientMagnitude = sqrt((sumX * sumX) + (sumY * sumY));
```

### Result


```bash
.\bin\cv.exe sobel --sobel-disable .\data\img1.jpg .\docs\.gitbook\assets\sobel.jpg
```

<div>

<figure><img src="../.gitbook/assets/img1.jpg" alt=""><figcaption><p>Original image</p></figcaption></figure>
<figure><img src="../.gitbook/assets/sobel.jpg" alt=""><figcaption><p>Sobel filter</p></figcaption></figure>

</div>
