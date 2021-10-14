#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //Average pixel value
    for (int row = 0;row<height;row++)
    {
        for (int col = 0;col<width;col++)
        {
            float average = (image[row][col].rgbtRed + image[row][col].rgbtBlue + image[row][col].rgbtGreen)/3.00;
            int avg = round(average);

            image[row][col].rgbtRed = avg;
            image[row][col].rgbtBlue = avg;
            image[row][col].rgbtGreen = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i<height; i++)
    {
        for (int j = 0; j<width; j++)
        {
            //Sepia Algorithms
            RGBTRIPLE pixel = image[i][j];
            int sepiaRed = round(0.393*pixel.rgbtRed + 0.769*pixel.rgbtGreen + 0.189*pixel.rgbtBlue);
            int sepiaBlue = round(0.272*pixel.rgbtRed + 0.534*pixel.rgbtGreen + 0.131*pixel.rgbtBlue);
            int sepiaGreen = round(0.349*pixel.rgbtRed + 0.686*pixel.rgbtGreen + 0.168*pixel.rgbtBlue);

            //Transforming pixels
            image[i][j].rgbtRed = (sepiaRed > 255) ? 255 : sepiaRed;
            image[i][j].rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width/2; j++)
            {
                RGBTRIPLE pixel = image[i][j];
                int red = pixel.rgbtRed;
                int green = pixel.rgbtGreen;
                int blue = pixel.rgbtBlue;

                image[i][j].rgbtRed = image[i][width-j-1].rgbtRed;
                image[i][j].rgbtGreen = image[i][width-j-1].rgbtGreen;
                image[i][j].rgbtBlue = image[i][width-j-1].rgbtBlue;

                image[i][width-j-1].rgbtRed = red;
                image[i][width-j-1].rgbtGreen = green;
                image[i][width-j-1].rgbtBlue = blue;
            }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i<height; i++)
    {
        for (int j = 0; j<width;j++)
        {
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            float counter = 0.00;

            for (int k = -1; k<2; k++)
            {
                for (int h = -1; h<2; h++)
                {
                    if ( i+k < 0 || i+k > height-1 || j+h < 0 || j+h > width-1)
						{
						   continue;
						}

						 sumRed += image[i+k][j+h].rgbtRed;
			           	 sumGreen += image[i+k][j+h].rgbtGreen;
				         sumBlue = image[i+k][j+h].rgbtBlue;
				         counter++;
                    }
                }

                temp[i][j].rgbtRed = round(sumRed/counter);
                temp[i][j].rgbtGreen = round(sumGreen/counter);
                temp[i][j].rgbtBlue = round(sumBlue/counter);
            }
    }

        for (int i = 0;i<height;i++)
            {
                for(int j = 0;j<width;j++)
                    {
                        image[i][j].rgbtRed = temp[i][j].rgbtRed;
                        image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
                        image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
                     }
            }
    return;
}
