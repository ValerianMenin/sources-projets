from decimal import *
import math
import numpy
import cv2
import copy

# Import de l'image
im1 = cv2.imread('lena_std.tif')
im1 = cv2.cvtColor(im1, cv2.COLOR_BGR2GRAY)
# cv2.imshow("Frame", im1)
# print(im1)

# cv2.waitKey(0)
# cv2.destroyAllWindows()

imarray1 = numpy.array(im1)


def makedummyimage():
    im = numpy.zeros((8, 8))
    im[0, 0] = 139
    im[0, 1] = 144
    im[0, 2] = 149
    im[0, 3] = 153
    im[0, 4] = 155
    im[0, 5] = 155
    im[0, 6] = 155
    im[0, 7] = 155
    im[1, 0] = 144
    im[1, 1] = 151
    im[1, 2] = 153
    im[1, 3] = 156
    im[1, 4] = 159
    im[1, 5] = 156
    im[1, 6] = 156
    im[1, 7] = 156
    im[2, 0] = 150
    im[2, 1] = 155
    im[2, 2] = 160
    im[2, 3] = 163
    im[2, 4] = 158
    im[2, 5] = 156
    im[2, 6] = 156
    im[2, 7] = 156
    im[3, 0] = 159
    im[3, 1] = 161
    im[3, 2] = 162
    im[3, 3] = 160
    im[3, 4] = 160
    im[3, 5] = 159
    im[3, 6] = 159
    im[3, 7] = 159
    im[4, 0] = 159
    im[4, 1] = 160
    im[4, 2] = 161
    im[4, 3] = 162
    im[4, 4] = 162
    im[4, 5] = 155
    im[4, 6] = 155
    im[4, 7] = 155
    im[5, 0] = 161
    im[5, 1] = 161
    im[5, 2] = 161
    im[5, 3] = 161
    im[5, 4] = 160
    im[5, 5] = 157
    im[5, 6] = 157
    im[5, 7] = 157
    im[6, 0] = 162
    im[6, 1] = 162
    im[6, 2] = 161
    im[6, 3] = 163
    im[6, 4] = 162
    im[6, 5] = 157
    im[6, 6] = 157
    im[6, 7] = 157
    im[7, 0] = 162
    im[7, 1] = 162
    im[7, 2] = 161
    im[7, 3] = 161
    im[7, 4] = 163
    im[7, 5] = 158
    im[7, 6] = 158
    im[7, 7] = 158
    return numpy.uint8(im)


def function_c(x):
    if (x == 0):
        return float(1 / math.sqrt(2))
    else:
        return float(1)


def functionDCT(image, size_image, i, j):
    somme = float(0)
    N = float(size_image)
    i1 = float(i)
    j1 = float(j)
    for x in range(size_image):
        for y in range(size_image):
            x1 = float(x)
            y1 = float(y)
            somme = somme + image[x, y] * math.cos(((2 * x1 + 1) * i1 * math.pi) / (2 * N)) * math.cos(
                ((2 * y1 + 1) * j1 * math.pi) / (2 * N))
    dct = float((2 / N) * function_c(i1) * function_c(j1) * somme)
    return dct


def functionDCTinvert(DCT, size_image, x, y):
    somme = float(0)
    N = float(size_image)
    x1 = float(x)
    y1 = float(y)
    for i in range(size_image):
        for j in range(size_image):
            i1 = float(i)
            j1 = float(j)
            somme = somme + function_c(i1) * function_c(j1) * DCT[i, j] * math.cos(
                ((2 * x1 + 1) * i1 * math.pi) / (2 * N)) * math.cos(((2 * y1 + 1) * j1 * math.pi) / (2 * N))
    pixel = float((2 / N) * somme)
    return pixel


def function_CalcF(image, size_image):
    F = numpy.zeros((size_image, size_image))
    for i in range(size_image):
        for j in range(size_image):
            F[i][j] = functionDCT(image, size_image, i, j)
    return F


def function_Calcf(DCT, size_image):
    f = numpy.zeros((size_image, size_image))
    for x in range(size_image):
        for y in range(size_image):
            f[x][y] = functionDCTinvert(DCT, size_image, x, y)
    return f


def makeQuantificationMatrix(level, step):
    res = numpy.zeros((step, step))
    for i in range(0, step):
        for j in range(0, step):
            res[i][j] = (i * j) + level
    return res


def quantify(DCT, Q, size_image):
    Fq = numpy.zeros((size_image, size_image))
    for i in range(size_image):
        for j in range(size_image):
            q = math.trunc(Q[i][j] / 2);
            res = (DCT[i][j] + q) / Q[i][j]
            Fq[i][j] = math.trunc(res)
    return Fq


def deQuantify(DCT, Q, size_image):
    F = numpy.zeros((size_image, size_image))
    for i in range(size_image):
        for j in range(size_image):
            F[i][j] = DCT[i][j] * Q[i][j]
    return F


def doBlock(Image, size_image):
    blocks = []
    block = numpy.zeros((8, 8))
    #dans notre cas particulier le tableau blocks à une dimension de la taille de l'image (64 blocks)
    #chaque blocks faisant 8*8 cases
    for k in range((int(size_image/8)*int(size_image/8))) :
        blocks.append(copy.copy(block))
    indexBlock = 0
    for i in range(size_image) :
        for j in range(size_image) :
            indexBlock = (int(i / 8) * (int(size_image/8))) + int(j / 8) % (int(size_image/8)*int(size_image/8))
            blocks[indexBlock][int(i%8)][int(j%8)] = copy.copy(Image[i][j])
    return blocks


size_image = 512
size_block = 8
# image = makedummyimage()
image = cv2.resize(imarray1, (size_image, size_image))

#transformation en block
blocks = doBlock(image, size_image)

imageBlock = numpy.zeros((size_image, size_image))

# ici on a 8 blocks fois 8 blocks de blocks de 8 par 8
for i in range(size_image):
    for j in range(size_image):
        indexBlock = (int(i / 8) * (int(size_image / 8))) + int(j / 8) % (int(size_image / 8) * int(size_image / 8))
        indexInBlockLine = int(i % 8)
        indexInblockColumn = int(j % 8)
        imageBlock[i][j] = copy.copy(blocks[indexBlock][indexInBlockLine][indexInblockColumn])

cv2.imshow("ImageBlock", numpy.uint8(imageBlock))

print("\n\n\n")

#transformation des blocks par DCT
blocksDCT = []
for i in range(len(blocks)):
    print("block: " + str(i))
    blocksDCT.append(function_CalcF(blocks[i], size_block))

#DCT TO Image
blocksDTCtoImage = []

for i in range(len(blocks)):
    blocksDTCtoImage.append(function_Calcf(blocksDCT[i], size_block))

cv2.imshow("Frame", im1)

cv2.imshow("FrameResized", image)

imageDecompressed = numpy.zeros((size_image, size_image))

# ici on a 8 blocks fois 8 blocks de blocks de 8 par 8
for i in range(size_image):
    for j in range(size_image):
        indexBlock = (int(i / 8) * (int(size_image / 8))) + int(j / 8) % (int(size_image / 8) * int(size_image / 8))
        indexInBlockLine = int(i % 8)
        indexInblockColumn = int(j % 8)
        imageDecompressed[i][j] = copy.copy(blocksDTCtoImage[indexBlock][indexInBlockLine][indexInblockColumn])

# Affichage de l'image decompresse
cv2.imshow("FrameDecompressed", numpy.uint8(imageDecompressed))

cv2.waitKey(0)
cv2.destroyAllWindows()
