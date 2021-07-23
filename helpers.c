#include "helpers.h"
#include <math.h>
#define NULL ((char *)0)

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int average;
            int blue = image[h][w].rgbtBlue;
            int red = image[h][w].rgbtRed;
            int green = image[h][w].rgbtGreen;
            average = round(((float) blue + (float) green + (float) red) / 3); // averages the colors of each pixel

            if (average >= 255)
            {
                average = 255;
            }
            image[h][w].rgbtGreen = average; // assigns the average to each pixel
            image[h][w].rgbtBlue = average;
            image[h][w].rgbtRed = average;
        }


    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int blue = image[h][w].rgbtBlue;
            int red = image[h][w].rgbtRed;
            int green = image[h][w].rgbtGreen;
            int sepiaRed = round(.393 * red + .769 * green + .189 * blue); //implements the sepia formula
            if (sepiaRed >= 255)
            {
                sepiaRed = 255;
            }
            int sepiaGreen = round(.349 * red + .686 * green + .168 * blue);
            if (sepiaGreen >= 255)
            {
                sepiaGreen = 255;
            }
            int sepiaBlue = round(.272 * red + .534 * green + .131 * blue);
            if (sepiaBlue >= 255)
            {
                sepiaBlue = 255; // makes sure no color is more than 255
            }
            image[h][w].rgbtGreen = sepiaGreen;
            image[h][w].rgbtBlue = sepiaBlue;
            image[h][w].rgbtRed = sepiaRed; // assigns to each pixel 
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    int width2 = width;
    if (width2 % 2 != 0)
    {
        width2 = (width2 + 1) / 2; //formula to find the number of steps needed
    }
    else
    {
        width2 = width2 / 2;
    }

    //int width2 = ceil(((float) width + 1) / 2);
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width2; w++)
        {
            RGBTRIPLE garbage;
            garbage.rgbtGreen = image[h][w].rgbtGreen;
            garbage.rgbtRed = image[h][w].rgbtRed;
            garbage.rgbtBlue = image[h][w].rgbtBlue;
            image[h][w] = image[h][width - w - 1]; //uses switch, makes a garbage array
            image[h][width - w - 1].rgbtBlue = garbage.rgbtBlue;
            image[h][width - w - 1].rgbtGreen = garbage.rgbtGreen;
            image[h][width - w - 1].rgbtRed = garbage.rgbtRed;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int MasterC = -1;
    RGBTRIPLE finalproduct[(height + 1) * (width + 1)];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            MasterC++;
            RGBTRIPLE average[9];
            for (int z = 0; z < 9; z++)
            {
                average[z].rgbtRed = 0; //makes sure all values are blank
                average[z].rgbtGreen = 0;
                average[z].rgbtBlue = 0;
            }
            int counter = 0;
            for (int i = 0; i < 3; i++)
            {
                if (h + 1 > height - 1 || (w - (i - 1)) > width - 1 || (w - (i - 1)) < 0)
                {
                    continue; //condition to make sure pixels exist
                }
                else
                {
                    average[counter].rgbtRed = image[h + 1][w - (i - 1)].rgbtRed;//assigns final value to the array
                    average[counter].rgbtBlue = image[h + 1][w - (i - 1)].rgbtBlue;
                    average[counter].rgbtGreen = image[h + 1][w - (i - 1)].rgbtGreen;
                    counter++;
                }
            }
            for (int i = 0; i < 3; i++)
            {
                if ((w - (i - 1)) > width - 1 || (w - (i - 1)) < 0)
                {
                    continue;
                }
                else
                {
                    average[counter].rgbtRed = image[h][w - (i - 1)].rgbtRed;//assigns final value to the array
                    average[counter].rgbtBlue = image[h][w - (i - 1)].rgbtBlue;
                    average[counter].rgbtGreen = image[h][w - (i - 1)].rgbtGreen;
                    counter++;
                }
            }
            for (int i = 0; i < 3; i++)
            {
                if (h - 1 > height - 1 || (w - (i - 1)) > width - 1 || h - 1 < 0 || (w - (i - 1)) < 0)
                {
                    continue;
                }
                else
                {
                    average[counter].rgbtRed = image[h - 1][w - (i - 1)].rgbtRed; //assigns final value to the array
                    average[counter].rgbtBlue = image[h - 1][w - (i - 1)].rgbtBlue;
                    average[counter].rgbtGreen = image[h - 1][w - (i - 1)].rgbtGreen;
                    counter++;
                }
            }
            float AverageR = 0;
            float AverageB = 0;
            float AverageG = 0;
            for (int p = 0; p < 9; p++)
            {
                AverageR = AverageR + (float)average[p].rgbtRed; //adds the values of the arrays
                AverageB = AverageB + (float)average[p].rgbtBlue;
                AverageG = AverageG + (float)average[p].rgbtGreen;
            }

            int AverageR1 = round(AverageR / (counter)); //makes sure average is int
            int AverageB1 = round(AverageB / (counter));
            int AverageG1 = round(AverageG / (counter));
            if (AverageR1 >= 255)
            {
                AverageR1 = 255;
            }
            if (AverageB1 >= 255)
            {
                AverageB1 = 255;
            }
            if (AverageG1 >= 255)
            {
                AverageG1 = 255;
            }
            finalproduct[MasterC].rgbtRed = AverageR1; //assigns final value to the final array
            finalproduct[MasterC].rgbtBlue = AverageB1;
            finalproduct[MasterC].rgbtGreen = AverageG1;
        }
    }
    int counter3 = 0;
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w] = finalproduct[counter3];
            counter3++; //assigns each value to an array
        }
    }
    return;
}
