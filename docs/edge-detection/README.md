# Edge detection

Edge detection is another crucial aspect of Computer Vision. Imagine you are building a self-driving AI, and you would like to define the car's distance and shape. A basic approach would be to iteratively observe changes in the image, and if the change is above a certain limit, you could assume that it's a car or some kind of object. However, this method is not reliable due to several variables such as image compression, lens flare, and camera shake, which could cause faulty or garbage output.

Edge detection functions come to the rescue by allowing us to highlight the edges of the image, effectively giving us a scaffold that can provide valuable information about the shape of the car, its distance, and other similar parameters. This approach makes it possible to confidently identify the car, disregarding irrelevant factors such as compression artefacts or environmental variables.

So in the upcoming modules we are going to see the functions which will allow us to highlight or extract the edges from an image.
