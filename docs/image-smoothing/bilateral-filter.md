# Bilateral Filter

We previously described how the Median filter is poor at performance and bilateral filter is a good supplement to it, to understand why we must look at how the filter works.

The bilateral function takes in a `sigma` this describes the intensity of the smoothing similar to [Gaussian Blur](./gaussian-blur.md) and the kernel size. We then loop through each pixel, and we will subtract each of it's neighbour with the current pixel, we will multiply this with a "weight" and se tthe current pixel to the mean of the value. That is a bit convoluted (ha!) but let's see the implementation.

## Implementation

The Bilateral filter is implemented at [src/smoothing/bilateral.c](../../src/smoothing/bilateral.c)

```c
void cv_apply_bilateral_filter(Image* img, float sigma, int kernSize) {
  /* ... */
  unsigned char* tempBytes = (unsigned char*)malloc(width * height * ch * sizeof(unsigned char));

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      unsigned char R = compute_bilateral_filter_for_channel(img, sigma, kernSize, j, i, 0);
      unsigned char G = compute_bilateral_filter_for_channel(img, sigma, kernSize, j, i, 1);
      unsigned char B = compute_bilateral_filter_for_channel(img, sigma, kernSize, j, i, 2);

      tempBytes[(i * width + j) * ch + 0] = R;
      tempBytes[(i * width + j) * ch + 1] = G;
      tempBytes[(i * width + j) * ch + 2] = B;
    }
  }
  /* ... */
}

```

It's pretty apparent what we are doing here. Let's check the actual bilateral computation 

```c
unsigned char compute_bilateral_filter_for_channel(Image* img, float sigma, int kernSize, int x, int y, int c) {
    /* ... */ 
    for (int i = 0; i < kernSize; i++) {
        for (int j = 0; j < kernSize; j++) {
            if (y + i >= height || x + j >= width)
                continue;

            int currentNeighbour = img->bytes[((y + i) * width + x + j) * ch + c];
            int diff = centerValue - currentNeighbour;

            float rangeWeight = exp(-(diff * diff) / (2 * sigma * sigma));

            totalWeightedSum += rangeWeight * currentNeighbour;
            totalSum += rangeWeight;
        }
    }
    return (unsigned char)(totalWeightedSum / totalSum);
}
```

So let's break down what's going on here

- We loop through the neighbours of the `centerValue`
- We then extract the difference of center value and the current neighbour
- From the difference we extract a `rangeWeight` this will define how "sharp" our smoothing is
- `totalWeightedSum` is the sum of product of weight and current neighbour
- `totalSum` is just the sum of the weights
- We divide the above values and return it. This division is done to "normalize" the image so that it maintains the initial brightness or **photometric symmetry**, a fancier way to say that image shares properites with it's previous state.

From this we achieve the following result

## Result

```bash
.\bin\cv --bilateral --kernel 9 --sigma 30 .\data\img1.jpg ..\output.jpg
```

<div>

<figure><img src="../.gitbook/assets/img1.jpg" alt=""><figcaption><p>Original image</p></figcaption></figure>

<figure><img src="../.gitbook/assets/bilateral-3-9.jpg" alt=""><figcaption><p>Bilateral filter of Sigma 3, Kernel size 9</p></figcaption></figure>

</div>

The performace of this algorithm is a lot better than the one previously discussed.

```
Bilateral filter
----------------
kernelSize = 3: 0.7137557 sec
kernelSize = 5: 2.5828369 sec
kernelSize = 9: 5.3708221l sec
```
