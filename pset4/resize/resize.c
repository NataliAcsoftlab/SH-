      
#include <stdio.h>
#include <stdlib.h>
 
#include "bmp.h"
 
int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }
 
    // retrieve the scaling factor as a float
    int mashtab = atof(argv[1]);
    
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
 
    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }
 
    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }
 
    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
 
    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
 
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
 
    // determine padding for scanlines (for the image we are reading from)
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // zhituu image
    RGBTRIPLE image[bi.biWidth][abs(bi.biHeight)];
    
  
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for (int j = 0; j < bi.biWidth; j++)
        {
            RGBTRIPLE triple;
            // zchituu color
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            // brocau v masiv
            image[j][i] = triple;
        }
        // poisk v file
        fseek(inptr, padding, SEEK_CUR);
    }
    
    // zmenhut v k raz vusotu i hirinu
    bi.biWidth = bi.biWidth * mashtab;
    bi.biHeight =bi.biHeight* mashtab;
    
    // recalculate the padding (for the sclaed image we are writing)
    padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // poschet nomera bayt 
    bi.biSizeImage = abs(bi.biHeight) * (bi.biWidth * sizeof(RGBTRIPLE) + padding);
    
    // calculate the total number of bytes in the image (with the headers)
    bf.bfSize = bi.biSizeImage + 54;
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
 
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // writing to the scaled image's out file
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;
            
            // zapisuvaem cvet
            triple = image[(int) (j / mashtab)][(int) (i / mashtab)];

            // write the pixel to the file
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr); 
        }
        
        // write the buffer
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }
    
    // close infile
    fclose(inptr);
 
    // close outfile
    fclose(outptr);
 
    // that's all folks
    return 0;
}