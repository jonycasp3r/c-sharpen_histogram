# c-photoshop

Introduction

Imagine working as a software engineer in a company that develops image editing applications similar to Photoshop or GIMP. The performance and clarity of the editor are crucial for attracting users and staying competitive. In this context, a key component of the application is the implementation of convolution operations at the core of the program. Convolution is an essential image processing technique that calculates the value of each pixel as a weighted sum of its neighboring pixels. Each color channel is processed separately. Another task involves computing the histogram of the processed image.

Convolution is widely used in image processing for tasks such as sharpening, blurring, or edge detection. For more details on how convolution works, you can refer to: http://setosa.io/ev/image-kernels/
.

Code Overview

The code applies a sharpening convolution mask to an input image, optimizing memory usage to improve cache performance. The mask used is:

0  -1  0
-1  5 -1
0  -1  0


Pixels along the edges of the image are copied directly from the original image whenever the convolution kernel extends beyond the image boundaries. This ensures proper handling of border cases without introducing artifacts.

After applying the convolution, the program converts the resulting image to grayscale using the standard luminance model:

Y = round(0.2126*R + 0.7152*G + 0.0722*B)


It then computes a histogram of the grayscale values, dividing the range [0, 255] into 5 intervals:

Interval	0–50	51–101	102–152	153–203	204–255

The histogram counts the number of pixels falling into each interval.

The input image is read in binary PPM format (P6). The file contains the header P6, followed by the image width, height, the maximum intensity value (255), and the RGB data for each pixel, with one byte per color channel. The input file is specified as a command-line argument.

The program outputs two files:

output.ppm – the sharpened image in PPM format.

output.txt – the grayscale histogram values separated by spaces.

Performance Considerations

The code is optimized to reduce cache misses at various levels (L1 data and instruction cache, and L2 cache). The optimization focuses on efficient memory access patterns when applying the convolution mask, particularly to take advantage of the cache lines.

The program assumes the following cache configuration for optimization:

L1 caches (separate instruction and data caches): 32 KB each, 8-way set associative, 64 B block size.

L2 cache: 1 MB, 16-way set associative, 64 B block size, inclusive of both L1 caches.

Replacement policy: LRU.

Performance is measured based on the number of cache references and misses, and a scoring formula evaluates the efficiency of memory usage.

Summary

The implementation demonstrates:

Applying a convolution kernel for image sharpening.

Proper handling of image borders.

Converting RGB images to grayscale.

Computing a histogram of grayscale intensities.

Optimizing memory access to improve cache efficiency.

This design ensures that the image processing operations are both correct and efficient, suitable for integration into a real-time image editing application.
