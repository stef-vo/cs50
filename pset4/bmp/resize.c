/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    int n = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];
    
    // checking if n less than 100
    if (n < 1 || n >= 100)
    {
        printf("n must be from 1 to 99 inclusive\n");
        return 2;
    }
    

    // open input file 
    FILE* inptr = fopen(infile, "rb");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, new_bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    
    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, new_bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    
    // checking if n times size(infile) < 2^32 - 1
    if (n * bi.biSizeImage >= exp(32 * log(2)) - 1 )
    {
        printf ("Infile is too large\n");
        fclose(inptr);
        return 4;
    }
    
    
    
     // open output file
    FILE* outptr = fopen(outfile, "wb");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 5;
    }

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 6;
    }

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    new_bi = bi;
    new_bi.biWidth = bi.biWidth * n;
    new_bi.biHeight = bi.biHeight * n;
    
    // determine padding for outlines
    int new_padding = (4 - (new_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    new_bi.biSizeImage = ((bi.biSizeImage - abs(bi.biHeight) * padding)
    * n * n + n * abs(bi.biHeight) * new_padding);
    
    new_bf = bf;
    new_bf.bfSize = new_bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&new_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&new_bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        int rows;
        for (rows = 1; rows <= n; rows++)
            {
                
                if (rows > 1)
                {
                    // go back to the beginning of the line
                    fseek(inptr, -(long int)(bi.biWidth * sizeof(RGBTRIPLE)), SEEK_CUR);
                }
                
                
                // iterate over pixels in scanline
                for (int j = 0; j < bi.biWidth; j++)
                {
                    
                    // temporary storage
                    RGBTRIPLE triple;
                    
                    // read RGB triple from infile
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
                    // write RGB triple to outfile
                    for (int l = 1; l <= n; l++)
                    {
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }
                }
                 
                // then add new_padding
                for (int k = 0; k < new_padding; k++)
                {
                    fputc(0x00, outptr);
                }
            }
            
            // skip padding in inptr, if any
            fseek(inptr, padding, SEEK_CUR);
            
    }
        
        
     
    
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
