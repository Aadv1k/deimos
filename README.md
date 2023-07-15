# Computer Vision in C

Experimental computer vision library in C

I am trying to distill my knowledge into the [the cv.c wiki](https://github.com/Aadv1k/cv.c/wiki), as a simple guide for folks like myself looking to get started with this topic, feel free to critique and/or provide suggestions to my writings. 

- Smoothing
  - Gaussian blur: higher kernel will lead to more blurring, at the cost of speed
  - Median filter: higher sigma will give a smoother image 
  - Bilateral Filter: similar to Median but more performant
  - Box Filter: higher kernel size will give a more blurred image 
- Edge detection
  - Unsharp mask: emphasises the edges, higher sigma will make edges more pronounced at the cost of pixel tearing
  - Laplacian Filter (Difference of Gaussian): higher the kernel size thicker the edges. 
    Higher the sigma, less noisier the image.
  - Sobel operator: creates an image which emphasizes the edge, somewhat similar to Laplacian Filter
    but computationally better
- Color
  - Greyscale: convert image from RGB to 0..255 scale


> **Note**
> Almost all the functions of this library are arbitary and based on whatever came up on searching "image filtering algoritms"


## Build (windows)

```console
git clone git@github.com:aadv1k/cv.c
cd cv.c/
.\build.bat
```

## Build (unix)

```console
git clone git@github.com:aadv1k/cv.c
cd cv.c/
$ ./build.sh
```

## Examples

> **Note**
> The filters are un-optimized, they work best on smaller images

```console
.\cv --gray ..\data\gex.png .\output.png
.\cv --sharpen --sigma 3 ..\data\gex.png .\output.png
.\cv --gray --blur --kernel 9 --sigma 5 ..\data\gex.png .\output.png
```

## Usage

```console
$ ./cv.exe
Usage:
        cv.exe <args> input output
Examples:
        cv.exe --blur --sigma 3.4 --kernel 5 input.png output.png
        cv.exe --gray input.png output.png
        cv.exe --median --kernel 3 input.png output.png
        cv.exe --sharpen --sigma 0.6 --kernel 3 input.png output.png
Options:
        --help                print this help message
        --blur, --gaussian    apply gaussian blur to the image
        --median              apply median filter to the image
        --sobel               apply sobel filter to the image
        --bilateral           apply bilateral filter to the image
        --box, --mean         apply box filter onto the image
        --laplacian           apply laplacian filter onto the image
        --gray                convert image to grayscale
        --sharpen             sharpen image via an unsharp mask
        --sigma               specify the sigma for the convolutions
        --radius              define the kernel size for convolutions (if applicable)
```

## Credits

gex.png: https://www.ign.com/games/gex-enter-the-gecko-gbc/articles

