#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image");
        return 1;
    }
    BYTE buffer[512]; //makes a buffer 
    FILE *card = fopen(argv[1], "r");
    if (card == NULL) //makes sure card exists
    {
        printf("Usage: ./recover image");
        return 1;
    }
    FILE *img = NULL; // makes image empty
    int fopened = 0;
    int jpgnumb = -1;
    int test;
    while ((fread(&buffer, sizeof(BYTE), 512, card)) != 0)
    {
        //test = (fread(&buffer, sizeof(BYTE), 512, card));
        char filename[7];
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) //checks if image is jpg
        {
            jpgnumb ++;
            if (jpgnumb != 0) //if more than one file has been opened
            {
                fclose(img); // it closes the file
            }
            sprintf(filename, "%03i.jpg", jpgnumb);
            img = fopen(filename, "w"); //defins image
            fwrite(&buffer, sizeof(BYTE), 512, img);
            fopened = 1;
        }
        else
        {
            if (fopened == 1) //means file has been opened
            {
                fwrite(&buffer, sizeof(BYTE), 512, img); //if a file has been opened it continues
            }
            else
            {
                continue;
            }
        }
    }



}