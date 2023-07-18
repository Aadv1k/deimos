# Gaussian Filter

The Gaussian blur is one of the most popular blurring algorithms, where even applications like Photoshop and Gimp use it as their primary implementation. The Gaussian blur applies the  **Gaussian** or **Normal distribution** which is a function in statistics which distributes values given a `N` across a bell curve, over the pixel values contained within the kernel.


$$
f(x) = \frac{1}{\sigma \sqrt{2\pi}} \cdot e^{-\frac{(x - \mu)^2}{2\sigma^2}}
$$

yet again let's unpack this

```
1/SIGMA*SQRT(2*PI) *
EXP^(-(x-MEAN)^2/2 * SIGMA ^2
```

What this function is essentially doing is giving us some value which is contained within a "bell curve" ; this curve is determined by the  SIGMA and the MEAN. If this sounds too complicated, it's because it is, so let's jump into the code to see what's going on.

### Implementation

The Gaussian filter is implemented at [src/smoothing/blur.c](https://github.com/Aadv1k/cv.c/blob/master/smoothing/blur.c) Let's take a deeper look at it.

```c
void cv_apply_gaussian_blur(Image *image, float sigma, int size) {
  /* ... */
  cv_compute_gaussian_kernel(&kernel, sigma, SIZE);

  for (int i = 0; i < image->height; i++) {
	for (int j = 0; j < image->width; j++) {
  	for (int c = 0; c < image->channels; c++) {
    	for (int k = 0; k < SIZE; k++) {
      	for (int l = 0; l < SIZE; l++) {
        	/* ... */

        	float weight = kernel[k][l];
        	int pixelIndex = (yIndex * image->width + xIndex) * image->channels + c;
        	unsigned char pixelValue = imageBytes[pixelIndex];

        	sum += pixelValue * weight;
        	sumWeight += weight;
      	}
    	}

    	int pixelIndex = (i * image->width + j) * image->channels + c;
    	newImageBytes[pixelIndex] = (unsigned char)(sum / sumWeight);
  	}
	}
  }

  /* ... */
}

```

Stay with me here - We have a kernel of `N` size, we go through each cell of the kernel and assign a value, we compute this value from `sigma` modifier along with the X, and Y coordinates of the pixel.

We then multiply the kernels's value from the neighbours of the current pixel. After this point the process is similar to the **Mean filter** where we sum all the (weighted) values that come within kernel bounds and divide them. That produces the following output.

### Result

```sh
.\bin\cv blur --kernel 9 --sigma 3 .\data\img1.jpg .\img1-gaussian-3-9.png
```

<div>

<figure><img src="../.gitbook/assets/img1.jpg" alt=""><figcaption><p>Original image</p></figcaption></figure>
 
<figure><img src="../.gitbook/assets/gaussian-3-9.jpg" alt=""><figcaption><p>Gaussian Blur of Sigma 3, Kernel 9</p></figcaption></figure>

</div>

The Gaussian Blur is similar to the Box or Mean filter except a `sigma` modifier allows us to control how "sharp" the blur is.
