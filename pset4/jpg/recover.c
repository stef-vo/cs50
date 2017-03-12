/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;

int main(void)
{
    // open input file 
    FILE* inptr = fopen("card.raw", "rb");
    if (inptr == NULL)
    {
        printf("Could not open card.raw\n");
        return 1;
    }
    
    int block_size = 512;
    
    BYTE buffer[block_size];
    
    int jpg = -1; // number of jpg-files
    
    char s[8]; // additional array for sprintf
    
    // while not end of file
    while (!feof(inptr))
    {
        // read 512 bytes
        int n = fread(&buffer, 1, block_size, inptr);
        
        // if we read 512 bytes
        if (n == block_size)
        {
            // checking for the jpg mask
            if (buffer[0] == 0xff &&
                buffer[1] == 0xd8 &&
                buffer[2] == 0xff &&
                (buffer[3] & 0xf0) == 0xe0)
            {
                jpg++;  
                sprintf(s, "%03i.jpg", jpg);
                FILE*outptr = fopen (s, "ab+");
                fwrite(&buffer, 1, block_size, outptr);
                fclose(outptr);
            }
            else
            {
                if (jpg >= 0)
                {
                    sprintf(s, "%03i.jpg", jpg);
                    FILE*outptr = fopen (s, "ab+");
                    fwrite(&buffer, 1, block_size, outptr);
                    fclose(outptr);
                }
            }
        
        } //  end of fread
        
        else
        {
            // appending the last file with n bytes
            sprintf(s, "%03i.jpg", jpg);
            FILE*outptr = fopen (s, "ab+");
            fwrite(&buffer, 1, n, outptr);
            fclose(outptr);
        }
        
    } // end of while
        
     
    // close infile
    fclose(inptr);
    
    // that's all folks
    return 0;
}
