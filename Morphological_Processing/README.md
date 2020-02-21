# Morphological Processing
Three mainly morphological processing methods are:
* Thinning
* Shrinking
* Skeletonizing

This repo only includes the skeletonizing process.
The other two processing is similar to skeletonizing: only have to turn on the corresponding masks in the mask table.
## Goal
Skeletonizing images like below:
![Morphological skeletonizing](https://backto1995.com/temp_img/morph.png)
## How to run (Windows Terminal):
- Using C++
- pattern*.raw -- test images
- out*.raw -- skeletonized images

Step 1:
```
g++ -Wall -std=c++17 Skeletonize.cpp -o custom_name.o
```
Step 2:
```
custom_name.o pattern1.raw pattern2.raw pattern3.raw pattern4.raw out1.raw out2.raw out3.raw out4.raw
```
## Binary image Skeletonizing introduction
A skeleton figure representation of an object can be used to describe its structure.
We use a small size square window of 3 * 3 to traverse the input image.

If the pattern of the current windiw location meets the condition to skeletonize, we make all the outer 8 pixels as background.

Loop the upper procedure until the image won't change any more.

Then, we also need to check if the skeletonized image has broken lines, if so, we have to connect these broken lines.
## Reference Images
All images could be found on http://sipi.usc.edu/database/ or http://www.dabi.temple.edu/~shape/MPEG7/dataset.html.
