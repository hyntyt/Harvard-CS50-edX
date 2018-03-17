/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 * 
 * James Dreher
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define PAGESIZE 512
typedef uint8_t byte;
byte buffer[PAGESIZE]; //data buffer for each block (page)
char title[7] = "000.jpg";
int imgno = 1;

int main(int argc, char* argv[])
{
    
    // STEP 1: Open file blob
    FILE* blob = fopen("card.raw", "r");
    FILE *jpeg = NULL;
    
    // validate file
    if(blob == NULL){
        printf("Could not open %s.\n", "card.raw");
        fclose(blob);
        return 1;
    }
    

    // STEP 2: Read data blob into buffer
    while(fread(buffer, PAGESIZE, 1, blob) > 0){    
    
        // STEP 3: Iterate through buffer to find the start of a JPEG file
        if((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && (buffer[3] >= 0xe0) && (buffer[3] <= 0xef)){

            // Close old jpeg
            if (jpeg != NULL){
               fclose(jpeg);
            }
            
            // STEP 5: Create another jpeg since we're at the beginning of one
            jpeg = fopen(title, "w");
            sprintf(title, "%03d.jpg", imgno);
            imgno = imgno + 1;
           
            // write buffer data to mew jpeg file created
            fwrite(buffer, PAGESIZE, 1, jpeg);
        
        }else if(jpeg){
            // STEP 6: Write the remainder of the image
            fwrite(buffer, PAGESIZE, 1, jpeg);
        }
    
        
    }
    
    // FINAL STEP: tidy up
    fclose(blob);
    if(jpeg != NULL){
        fclose(jpeg);    
    }
    
    return 0;
    
}
