# Computer Vision in C

Experimental computer vision library in C

- Filters
  - Gaussian blur
  - Greyscale
  - Unsharp mask (sharpening)
  - Median filter (smoothing)

## Build (windows)

```console
$ .\build
```

## Example

> **Note**
> The filters are un-optimized, they work best on smaller images

```console
$ .\cv.exe --gray ..\data\gex.png .\output.png
$ .\cv.exe --gray --blur --sigma 5 ..\data\gex.png .\output.png
```

## Usage

```console
$ ./cv.exe
Usage:
        .\cv.exe <args> input output
Examples:
        .\cv.exe --blur --sigma 3.4 input.png output.png
        .\cv.exe --gray input.png output.png
Options:
        --blur        apply gaussian blur to the image
        --median      apply median filter to the image
        --gray        convert image to grayscale
        --sharpen     sharpen image via an unsharp mask
        --strength    the strength for the sharpening (default 0.5)
        --radius      specify the radius for the blur (default 1.0)
```

## Credits

gex.png: https://www.ign.com/games/gex-enter-the-gecko-gbc/articles

