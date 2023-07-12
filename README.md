# Computer Vision in C

Experimental computer vision library in C

## Build (windows)

```shell
$ .\build
```

## Example

> **Note**
> The filters are un-optimized, they work best on smaller images


```shell
$ .\cv.exe --gray ..\data\gex.png .\output.png
$ .\cv.exe --gray --blur --sigma 5 ..\data\gex.png .\output.png
```

## Usage

```shell
$ ./cv.exe
Usage:
        .\cv.exe <args> input output
Examples:
        .\cv.exe --blur --sigma 3.4 input.png output.png
        .\cv.exe --gray input.png output.png
Options:
        --blur     apply gaussian blur to the image
        --gray     convert image to grayscale
        --sigma    specify the sigma for the blur (default 1.0)

```

## Credits

gex.png: https://www.ign.com/games/gex-enter-the-gecko-gbc/articles

