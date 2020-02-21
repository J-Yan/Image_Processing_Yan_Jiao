# Image Compression with KMeans
I only implemented 'kmeans.py', other codes were provided by course instructor.
## Goal
Compress images like below:
![compress image](https://backto1995.com/temp_img/bab.png)
input image size: 787 KB

compressed image: 215 KB
## How to run (MacOS Terminal):
Using Python3

```
python3 kmeansTest.py
```

The compressed image will be in the 'plots' folder

## KMeans for image compression introduction
- Find the clusters' centroids of all pixel values
- simply replace each pixel value with the closest centroid's value
