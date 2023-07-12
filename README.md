# Computer Vision in C

Experimental computer vision library in C

## Build (windows)

```shell
$ .\build
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
