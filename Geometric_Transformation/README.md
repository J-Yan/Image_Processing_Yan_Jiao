# Geometric Transformation
## Goal
Put the image patches back into the original image:
![lighthouse](https://backto1995.com/temp_img/lighthouse.png)
## How to run (MacOS Terminal):
- Using C++
- lighthouse*.raw -- rotated patches
- lighthouse.raw -- original image with holes
- out.raw -- complete image

Step 1:
```
g++ -Wall -std=c++17 Geometric_Trans.cpp -o custom_name.o
```
Step 2:
```
./custom_name.o lighthouse1.raw lighthouse2.raw lighthouse3.raw lighthouse.raw out.raw
```
## Transform idea
- Find the corners of patches and holes
- Apply the rotate transform to the patches
- Apply the scale transform to the patches
- Put these patches back

###### Note:
- Because of the rotation, the corner might get blurred. We need to pick the darkest pixel in the blurred corner area
- There maybe some white lines around the patched areas, we can apply some small scale adjustment to fix the white line.  
