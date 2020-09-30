/* Implements a program that recovers JPEGs from a forensic image per the specifications from 
https://cs50.harvard.edu/x/2020/psets/4/recover/#:~:text=Implement%20a%20program%20that%20recovers%20JPEGs%20from%20a%20forensic%20image */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// define byte data-type
typedef uint8_t BYTE;

// recover jpegs from memory card file
int main(int argc, char *argv[])
{
    // checks for a single command-line argument
    if (argc != 2)
    {
        printf("Enter one filename\n");
        return 1;
    }

    // allocate memory for buffer array
    BYTE *buffer = malloc(sizeof(BYTE) * 512);
    buffer[512] = 0;

    // allocate memory for filename string
    char *filename = malloc(sizeof(int) * 8);
    filename[8] = 0;

    // counts number of jpegs
    int jpegcounter = -1;

    // open memory card
    FILE *memorycard = fopen(argv[1], "r");
    if (memorycard == NULL)
    {
        printf("Couldn't open file\n");
        return 1;
    }

    while (fread(buffer, sizeof(BYTE), 512, memorycard) == 512)
    {
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {
            // increase jpeg counter
            jpegcounter++;

            // create new file using naming convention
            sprintf(filename, "%03i.jpg", jpegcounter);
            FILE *fp = fopen(filename, "w");

            if (fp == NULL)
            {
                printf("Couldn't open file\n");
                return 1;
            }

            // write block of 512 bytes to new image file
            fwrite(buffer, sizeof(BYTE), 512, fp);

            fclose(fp);
        }

        else
        {
            if (jpegcounter > -1)
            {
                // open image file
                FILE *fp = fopen(filename, "a");

                if (fp == NULL)
                {
                    printf("Couldn't open file\n");
                    return 1;
                }

                // write block of 512 bytes to image file
                fwrite(buffer, sizeof(BYTE), 512, fp);

                fclose(fp);
            }
        }
    }

    // close files
    int fcloseall();

    // free memory
    free(buffer);
    free(filename);

    return 0;
}
