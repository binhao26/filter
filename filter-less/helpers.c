#include "helpers.h"
#include <math.h>
#include <stdio.h>



// Convert image to grayscale
/**
 * Takes the average of red, blue, and green values for each pixel 
 * then reassign the new averaged value back to each colour channel.
 * 
 * */
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg_grayscale;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            avg_grayscale = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0); // 3.0 is usd instead 3 for higher accuracy, then round up the new value to nearest integer.
            image[i][j].rgbtBlue = avg_grayscale;
            image[i][j].rgbtGreen = avg_grayscale;
            image[i][j].rgbtRed = avg_grayscale;
        }
    }
    return;
}

// Convert image to sepia
/**
 * The sepia function gives images an old-timey feel 
 * by making the whole image look a bit reddish-brown.
 * 
 * To achieve this effect it takes each pixel, and computes new red, green, and blue value
 * based on the original values of the three.
 * 
 * */
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed, sepiaGreen, sepiaBlue;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            // the sepia algorithm
            sepiaRed = round((0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue));
            sepiaGreen = round((0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue));
            sepiaBlue = round((0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue));

            //ensure the computed value is 0-255 inclusive
            if (sepiaRed > 255) sepiaRed = 255;
            if (sepiaGreen > 255) sepiaGreen = 255;
            if (sepiaBlue > 255) sepiaBlue = 255;

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int head = 0;
    int tail = width - 1;
    int temp_rgbtRed, temp_rgbtGreen, temp_rgbtBlue;

    for (int i = 0; i < height; i++) {
        for (int j = 0; head < tail; j++) {
            temp_rgbtRed = image[i][head].rgbtRed;
            temp_rgbtGreen = image[i][head].rgbtGreen;
            temp_rgbtBlue = image[i][head].rgbtBlue;

            image[i][head].rgbtRed = image[i][tail].rgbtRed;
            image[i][head].rgbtGreen = image[i][tail].rgbtGreen;
            image[i][head].rgbtBlue = image[i][tail].rgbtBlue;

            image[i][tail].rgbtRed = temp_rgbtRed;
            image[i][tail].rgbtGreen = temp_rgbtGreen;
            image[i][tail].rgbtBlue = temp_rgbtBlue;

            head = head + 1;
            tail = tail - 1;
        }
        head = 0;
        tail = width - 1;
    }
    return;
}

// Blur image
/**
 * The box blur method is used to achieve blur effect by
 * taking each pixel and, for each color value, giving it a new value by 
 * averaging the color values of neighboring pixels.
 * **For more explanation, please visit cs50 lecture 4 memory - filter****
 * 
 * */
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // variables to hold each colour channel value of pixels surrounding 
    // the current pixel
    int left_blue = 0;
    int left_red = 0;
    int left_green = 0;
    int right_blue = 0;
    int right_red = 0;
    int right_green = 0;
    int up_left_blue = 0;
    int up_left_red = 0;
    int up_left_green = 0;
    int up_right_blue = 0;
    int up_right_red = 0;
    int up_right_green = 0;
    int down_blue = 0;
    int down_red = 0;
    int down_green = 0;
    int up_blue = 0;
    int up_red = 0;
    int up_green = 0;
    int down_right_blue = 0;
    int down_right_red = 0;
    int down_right_green = 0;
    int down_left_blue = 0 ;
    int down_left_red = 0;
    int down_left_green = 0;

    int counter = 0;

    // new values to be 
    // assigned for each respective colour channel for all
    // surrounding pixels, including the current pixel.
    int new_red_value = 0;
    int new_blue_value = 0;
    int new_green_value = 0;


    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

        /**
         * The if statements below are for ensuring 
         * for the current pixel, each of its surround
         * pixels are within boundary, thus their rgb values
         * will be extracted for calculations.
         * 
         * @counter for tracking how many valid pixels read.
         * */

            // if i >= 0 and i <= height - 1
            // retrieve the rgb values from upper pixel
            // up
            if (i - 1 >= 0) {

 				up_blue = image[i-1][j].rgbtBlue;
                up_red = image[i-1][j].rgbtRed;
                up_green = image[i-1][j].rgbtGreen;
 				counter = counter + 1;
 			}
 			// down
 			if (i + 1 <= height - 1) {

 				down_blue = image[i+1][j].rgbtBlue;
                down_red = image[i+1][j].rgbtRed;
                down_green = image[i+1][j].rgbtGreen;
 				counter = counter + 1;
 			}
 			//left
 			if (j - 1 >= 0) {

 				left_blue = image[i][j-1].rgbtBlue;
                left_red = image[i][j-1].rgbtRed;
                left_green = image[i][j-1].rgbtGreen;
 				counter = counter + 1;
 			}
 			//right
 			if (j + 1 <= width - 1) {

 				right_blue = image[i][j+1].rgbtBlue;
                right_red = image[i][j+1].rgbtRed;
                right_green = image[i][j+1].rgbtGreen;
 				counter = counter + 1;
 			}
 			//up-left
 			if ((i - 1 >= 0) && (j - 1 >= 0)) {

 				up_left_blue = image[i-1][j-1].rgbtBlue;
                up_left_red = image[i-1][j-1].rgbtRed;
                up_left_green = image[i-1][j-1].rgbtGreen;
 				counter = counter + 1;
 			}
 			//up-right
 			if ((i - 1 >= 0) && (j + 1 <= width - 1)) {

 				up_right_blue = image[i-1][j+1].rgbtBlue;
                up_right_red = image[i-1][j+1].rgbtRed;
                up_right_green = image[i-1][j+1].rgbtGreen;
 				counter = counter + 1;
 			}
 			//down-left
 			if ((i + 1 <= height - 1) && (j - 1 >= 0)) {

 				down_left_blue = image[i+1][j-1].rgbtBlue;
                down_left_red = image[i+1][j-1].rgbtRed;
                down_left_green = image[i+1][j-1].rgbtGreen;
 				counter = counter + 1;
 			}
 			//down-right
 			if ((i + 1 <= height - 1) && (j + 1 <= width - 1)) {

 				down_right_blue = image[i+1][j+1].rgbtBlue;
                down_right_red = image[i+1][j+1].rgbtRed;
                down_right_green = image[i+1][j+1].rgbtGreen;
 				counter = counter + 1;
 			}
            counter = counter + 1; // increment counter by 1 to include current pixel

            //take the average of all surrounding rbg channel values including pixel's rbg values.
 			new_blue_value = round((up_blue + down_blue + left_blue + right_blue + up_left_blue + up_right_blue + down_right_blue + down_left_blue + image[i][j].rgbtBlue) / counter);
            new_red_value = round((up_red + down_red + left_red + right_red + up_left_red + up_right_red + down_right_red + down_left_red + image[i][j].rgbtRed) / counter);
            new_green_value = round((up_green + down_green + left_green + right_green + up_left_green + up_right_green + down_right_green + down_left_green + image[i][j].rgbtGreen) / counter);
 			image[i][j].rgbtBlue = new_blue_value;
            image[i][j].rgbtRed = new_red_value;
            image[i][j].rgbtGreen = new_green_value;

            // reset
 			left_blue = 0;
            left_red = 0;
            left_green = 0;
            right_blue = 0;
            right_red = 0;
            right_green = 0;
            up_left_blue = 0;
            up_left_red = 0;
            up_left_green = 0;
            up_right_blue = 0;
            up_right_red = 0;
            up_right_green = 0;
            down_blue = 0;
            down_red = 0;
            down_green = 0;
            up_blue = 0;
            up_red = 0;
            up_green = 0;
            down_right_blue = 0;
            down_right_red = 0;
            down_right_green = 0;
            down_left_blue = 0;
            down_left_red = 0;
            down_left_green = 0;

            counter = 0;
            new_red_value = 0;
            new_blue_value = 0;
            new_green_value = 0;

        }
    }

    return;
}
