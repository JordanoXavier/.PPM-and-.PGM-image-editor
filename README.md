# .PPM and .PGM image editor
 
It is a program for manipulating images in P2/PGM and P3/PPM format using static allocation structures to store the image in main memory (vector/matrix).

The program starts in the main function, identifies the initializationFile, which receives from the user the name or directory of the file to be opened and opens it.
In the same function, the first line of the file is read, which indicates the type of image (P2 or P3).

When identifying the format, the program can go to two functions: lerP2 or lerP3. These two functions read as remaining information from the file (height and width, maximum color, and the color value of each pixel). The first 3 lines of the file will be stored in a structure called dataArquivo which will be used later to pass such information as a parameter to other functions.
In the case of the lerP2 function, the cores will be stored in a matrix with the dimensions read from the file. In the P3 function, they will also be stored in a matrix with the height and width read, but with 3 dimensions for storing the 3 cores of each pixel (R,G,B), since this type of file supports this, unlike P2.

After the complete reading of the file, the structure dataArquivo and the matrix read will be transmitted to the respective function of the menu of each type/format (function menuP2 or menuP3). In functions menuP2 and menuP3, the user has the possibility to choose between 6 options that call functions (individual of each menu) to carry out operations with the read data.
All options have versions P2 and P3 due to the difference in storing pixels for each image format, however, the operation for both types is identical. Furthermore, all of them except the image saving options return to the respective menu, which this time receives the edited image data.

The functions are:

## recorteP2 and recorteP3:
Receive from the user a cut/selection of the initial image for the output image. This cropping is mapped from the X1 and Y1 coordinates (starting at 0) of the upper left X2 and Y2 coordinates of the lower right corner of the area to be cropped.
The first checks occur to find out if it is possible to carry out the clipping. In case of impossibility, it returns to the respective menu with the previous matrix and data. Otherwise, a new matrix is generated with the clipping area in the original.
The new matrix will be printed on the screen and forwarded to the menu along with the updated data for new editions or recording of the file.

## grayscaleP3:
Convert an image read from P3 format to P2. Since P2 images are already grayscale, there is no such functionality for this type.
The conversion basically consists of performing an average of the RGB values of each pixel and placing them in the equivalent positions of a P2 matrix with only two dimensions.
The new matrix will be printed on the screen and followed along with the data updated to menuP2 and not to menuP3, in view of the type conversion.

## greenscreenP2 and greenscreenP3:
Read a new image and pass to the previous image all the pixels of the new one except those of a color chosen by the user (mask). To do so, first a new file of the same type as the background image is opened and read.
Subsequently, it is checked whether the size of the front image is smaller than or equal to that of the background and whether the type is the same, returning to the menu if the effect is impossible and reading the mask color if possible.
If the color is read, the greenscreen effect is applied. The result will be forwarded to the menu.

## rotacaoP2 and rotacaoP3:
Rotate the image clockwise by 90, 180 or 270 degrees recursively according to the user's choice in the menu. They receive from the menu the image (data and matrix) and the number of rotations to be made (degrees/90). Recursion is used to rotate the image more than once by 90º, passing a received image rotated along with the remaining number of rotations -1 in the same function. The recursion stopping point, which returns to the menu, is when the number of rotations is 1.
To perform the rotation, compare the height and width of the received image to know if it is a square matrix or not. If so, a simple 90º rotation is performed using an auxiliary matrix. The result will be printed on the screen and forwarded to the menu or again to the function if there are pending rotations.
If it is a non-square matrix, a square matrix will be created with the largest coordinate (height or width), so that it is possible to perform a 90º rotation. The square matrix is filled with a negative value, receives the original values in the equivalent positions and is rotated with the help of an auxiliary matrix. Next, a new matrix with inverted height and width is created, which will receive the positive values of the rotated square matrix and will be printed on the screen. The result, together with the updated file data, will be forwarded to the menu or again to the function if there are still rotations to be made.

## salvarP2 and salvarP3:
Recebem do usuário o nome ou diretório que o arquivo (.pgm ou .ppm) será salvo e o criam com os dados e a imagem editada. Caso haja um arquivo de mesmo nome, será substituído pelo novo.
