/**
 * resize.c   //copied from copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, resizing it based on command-line input.
 * 
 * James Dreher
 * james.d.dreher@gmail.com
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4) //needed to be increased by 1 bc we're also accpeting an int for the scale of resize
    {
        printf("Usage: ./resize scale(1-100) small.bmp large.bmp\n");
        return 1;
    }

    // determine the scale to resize the image to based on command-line input
    int scale = atoi(argv[1]); //second input is now the scale
    
    //error checking for scale input, low end
    if(scale < 1){
        printf("Usage: ./resize scale(1-100) small.bmp large.bmp\n");
        return 1;    
    }
    
    //error checking for scale input, high end
    if(scale > 100){
        printf("Usage: ./resize scale(1-100) small.bmp large.bmp\n");
        return 1;    
    }
    
    
    // saving filenames based on last 2 command-line inputs
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

    // read infile's BITMAPFILEHEADER, set instance of struct as 'bf'
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER, set instance of struct as 'bi'
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
    
    // determine padding for scanlines
    int bipadding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
        
    //PART 1: Make new bmp headers based on scale input jd (verified through cs50 commands)
         
    // Edit values for outfile's BITMAPINFOHEADER, keeping track of initial values per Zamayla
    BITMAPINFOHEADER outBI = bi;
        outBI.biWidth = bi.biWidth * scale; //simple multiplication for w
        outBI.biHeight = bi.biHeight * scale; //simple multiplication for h
        int outBIpadding = (4 - (outBI.biWidth * sizeof(RGBTRIPLE)) % 4) % 4; //new padding value since image is diferent size
        outBI.biSizeImage = ((outBI.biWidth * sizeof(RGBTRIPLE)) + outBIpadding) * abs(outBI.biHeight); //new image size to account for scale and new padding
   
    // Edit values for outfile's BITMAPFILEHEADER, keeping track of initial values per Zamayla
     BITMAPFILEHEADER outBF = bf; 
        outBF.bfSize = 54 + outBI.biSizeImage; //header plus image itself for total size
            
    // write outfile's BITMAPFILEHEADER and BITMAPINFOHEADER with updated values
    fwrite(&outBF, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&outBI, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    
    //PART 2: Copy pixels from inptr to outptr accordingly jd, using re-copy method
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for(int s = 0; s<scale;s++){
            
            //move ptr to beginning of scaleline again, using header offset and row offset from beginning of file
            fseek(inptr, (((bi.biWidth * 3 + bipadding) * i) + 54), SEEK_SET);
            
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                for(int t=0; t<scale;t++){
                    // write RGB triple to outfile, repeatedly to scale
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            
            // write padding required for new bitmap size after pixels are written
            for(int p=0;p<outBIpadding;p++){
                fputc(0x00, outptr);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success if reached
    return 0;
}
