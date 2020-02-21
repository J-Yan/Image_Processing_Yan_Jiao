import numpy as np
from data_loader import toy_dataset, load_digits
from kmeans import KMeans, KMeansClassifier, get_k_means_plus_plus_center_indices as k_plus, get_lloyd_k_means as k_vanilla, transform_image
from sklearn.linear_model import LogisticRegression
from sklearn.neighbors import KNeighborsClassifier
from utils import Figure
from sklearn.metrics import mean_squared_error

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

################################################################################
# KMeans for image compression
# Here we use k-means for compressing an image
# We load an image 'baboon.tiff',  scale it to [0,1] and compress it.
################################################################################

def kmeans_image_compression():

    print("[+] K-Means Image Compression")
    im = plt.imread('baboon.tiff')
    N, M = im.shape[:2]
    im = im / 255

    # convert to RGB array
    data = im.reshape(N * M, 3)

    k_means = KMeans(n_cluster=16, max_iter=100, e=1e-6)
    centroids, _, i = k_means.fit(data)

    print('[+] RGB centroids computed in {} iteration'.format(i))
    plt.imsave('plots/compressed_baboon1.png', im)
    new_im = transform_image(im, centroids)
    plt.imsave('plots/compressed_baboon2.png', im)

    assert new_im.shape == im.shape, \
        'Shape of transformed image should be same as image'

    mse = np.sum((im - new_im)**2) / (N * M)
    print(np.unique(im[:,:,0:2]))
    print(np.unique(new_im[:,:,0:2]))
    print('[+] Mean square error per pixel is {}\n'.format(mse))
    plt.imsave('plots/compressed_baboon.png', new_im)


if __name__ == '__main__':
    kmeans_image_compression()
