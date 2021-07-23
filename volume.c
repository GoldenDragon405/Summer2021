// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;
int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);
    //typedef uint8_t BYTE;
    uint8_t headers[HEADER_SIZE];
    fread(&headers, sizeof(uint8_t), HEADER_SIZE, input);
    fwrite(&headers, sizeof(uint8_t), HEADER_SIZE, output);
    int i = 0;
    int16_t buffer;
    while (fread(&buffer, 2, 1, input))
    {
        //fread(&buffer, 2, 1, input);
        buffer = buffer * factor;
        fwrite(&buffer, 2, 1, output);
    }

    // TODO: Read samples from input file and write updated data to output file
    fclose(input);
    fclose(output);
}
