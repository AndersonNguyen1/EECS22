/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* Movie.c: source file for basic movie manipulations                */
/*                                                                   */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Movie.h"

/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */
MOVIE *CreateMovie(void)
{
	MOVIE *movie;
	movie = malloc(sizeof(MOVIE));
	if(! movie)
	{
		perror("Out of memory! Aborting...");
		exit(10);
	}
	movie->Frames = CreateImageList();
	return movie;	
}

/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(MOVIE *movie)
{
	assert(movie);
	DeleteImageList(movie->Frames);
	free(movie);
}

static int clip(int i)
{
	if(i < 0)
	{
		return 0;
	}
	else if(i > 255)
	{
		return 255;
	}
	return i;
}

/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(MOVIE *movie)
{
	assert(movie);
	int i, j = 0;
	IENTRY *current = movie->Frames->First;
 
	while(current)
	{
		YUVIMAGE *YUVimage = current->YUVImage;
		IMAGE *RGBimage = CreateImage(YUVimage->W, YUVimage->H);
		for(j = 0; j < YUVimage->H; j++)
		{
			for(i = 0; i < YUVimage->W; i++)
			{
				unsigned char Y = GetPixelY(YUVimage, i, j);
				unsigned char U = GetPixelU(YUVimage, i, j);
				unsigned char V = GetPixelV(YUVimage, i, j);
				
				int C = Y - 16;
			        int D = U - 128;
        			int E = V - 128;
        			int R = clip(( 298 * C + 409 * E + 128) >> 8);
        			int G = clip(( 298 * C - 100 * D - 208 * E + 128) >> 8);
        			int B = clip(( 298 * C + 516 * D + 128) >> 8);

				SetPixelR(RGBimage, i, j, R);
				SetPixelG(RGBimage, i, j, G);
				SetPixelB(RGBimage, i, j, B);		
			}
		}
		current->RGBImage = RGBimage;
		DeleteYUVImage(current->YUVImage);
		current->YUVImage = NULL;
		current = current->Next;
	}		
}

/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(MOVIE *movie)
{
	assert(movie);
        int i, j = 0;
        IENTRY *current = movie->Frames->First;

        while(current)
        {
                IMAGE *RGBimage = current->RGBImage;
                YUVIMAGE *YUVimage = CreateYUVImage(RGBimage->W, RGBimage->H);
                for(j = 0; j < RGBimage->H; j++)
                {
                        for(i = 0; i < RGBimage->W; i++)
                        {
                                unsigned char R = GetPixelR(RGBimage, i, j);
                                unsigned char G = GetPixelG(RGBimage, i, j);
                                unsigned char B = GetPixelB(RGBimage, i, j);

				int Y = clip( ( ( 66 * R + 129 * G + 25 * B + 128) >> 8) + 16 );
       				int U = clip( ( ( -38 * R - 74 * G + 112 * B + 128) >> 8) + 128 );
        			int V = clip( ( ( 112 * R - 94 * G - 18 * B + 128) >> 8) + 128 );

                                SetPixelY(YUVimage, i, j, Y);
                                SetPixelU(YUVimage, i, j, U);
                                SetPixelV(YUVimage, i, j, V);
                        }
                }
                current->YUVImage = YUVimage;
                DeleteImage(current->RGBImage);
                current->RGBImage = NULL;
                current = current->Next;
        }
}

/* EOF */
