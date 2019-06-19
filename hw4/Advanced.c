#include "Advanced.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>

/* Add noise to an image */
IMAGE *AddNoise(IMAGE *image, int n)
{
        assert(image);
	int x, y, i;
	int num; /* number of noise added */
	num = ( n * ImageHeight(image) * ImageWidth(image))/100;
	srand(time(NULL));

	for ( i = 0; i < num; i++ ) 
        {
		x = ( (double)rand()/RAND_MAX )*(ImageWidth(image)-1);
		y = ( (double)rand()/RAND_MAX )*(ImageHeight(image)-1);
                
                SetPixelR(image, x, y, 255);
                SetPixelG(image, x, y, 255);
                SetPixelB(image, x, y, 255);		
	}
        return image;
}


/* sharpen the image */
IMAGE *Sharpen(IMAGE *image)
{
        assert(image);
	int		x, y, m, n, a, b;
	int		tmpR = 0;
	int		tmpG = 0;
	int		tmpB = 0;
        IMAGE *temp = CreateImage(ImageWidth(image), ImageHeight(image));  
	
	for (y = 0; y < ImageHeight(image); y++){
		for (x = 0; x < ImageWidth(image); x++) {
			SetPixelR(temp, x, y, GetPixelR(image, x, y));
                        SetPixelG(temp, x, y, GetPixelG(image, x, y));
                        SetPixelB(temp, x, y, GetPixelB(image, x, y));
		}
	}

	for (y = 0; y < ImageHeight(image); y++){
		for (x = 0; x < ImageWidth(image); x++){
			for (n = -1; n <= 1; n++){
				for (m = -1; m <= 1; m++) {
					a = x + m;
					b = y + n;
					if (a > ImageWidth(image) - 1)
						a = ImageWidth(image) - 1;
					if (a < 0)
						a = 0;
					if (b > ImageHeight(image) - 1)
						b = ImageHeight(image) - 1;
					if (b < 0)
						b = 0;
					
					if ((n==0)&&(m==0))
					{
						tmpR += 9*GetPixelR(temp, a, b); 
						tmpG += 9*GetPixelG(temp, a, b);
                				tmpB += 9*GetPixelB(temp, a, b); 
					}
					else
					{
						tmpR -= GetPixelR(temp, a, b); 
						tmpG -= GetPixelG(temp, a, b);
						tmpB -= GetPixelB(temp, a, b); 
					}
				}
			}
			SetPixelR(image, x, y, (tmpR>255)? 255: (tmpR<0)? 0: tmpR);
			SetPixelG(image, x, y, (tmpG>255)? 255: (tmpG<0)? 0: tmpG);
			SetPixelB(image, x, y, (tmpB>255)? 255: (tmpB<0)? 0: tmpB);
		  	tmpR = tmpG = tmpB = 0; 	
		}
	}
        DeleteImage(temp);
        return image;
}

/* make the image posterized */
IMAGE *Posterize(IMAGE *image, unsigned int rbit, unsigned int gbit, unsigned int bbit)
{
    assert(image);
    int x, y = 0;
    int r, g, b;
    unsigned char rbitTemp, gbitTemp, bbitTemp;
    unsigned char rbitTemp2, gbitTemp2, bbitTemp2;

    for(y = 0; y < ImageHeight(image); y++)
    {
        for(x = 0; x < ImageWidth(image); x++)
        {
            /* We are going to set the bit posterization to zero */
            rbitTemp = GetPixelR(image, x, y);
            rbitTemp &= ~(1 << (rbit - 1));
            SetPixelR(image, x, y, rbitTemp);
            
            gbitTemp = GetPixelG(image, x, y);
            gbitTemp &= ~(1 << (gbit - 1));
            SetPixelG(image, x, y, gbitTemp);

            bbitTemp = GetPixelB(image, x, y);
            bbitTemp &= ~(1 << (bbit - 1));
            SetPixelB(image, x, y, bbitTemp);

            /* Loops through the R and loops through the bits that are less than rbit and sets them to 1 */
            for(r = 0; r < rbit - 1; r++)
            {
                rbitTemp2 = GetPixelR(image, x, y);
                rbitTemp2 |= 1 << r;
                SetPixelR(image, x, y, rbitTemp2); 
            }
            /* Loops through the G and loops through the bits that are less than gbit and sets them to 1 */
            for(g = 0; g < gbit - 1; g++)
            {
                gbitTemp2 = GetPixelG(image, x, y); 
                gbitTemp2 |= 1 << g;
                SetPixelG(image, x, y, gbitTemp2);
            }
            /* Loops through the B and loops through the bits that are less than bbit and sets them to 1 */
            for(b = 0; b < bbit - 1; b++)
            {
                bbitTemp2 = GetPixelB(image, x, y);
                bbitTemp2 |= 1 << g;
                SetPixelB(image, x, y, bbitTemp2);
            }
        }
    }
    return image;
}


/* add motion blur to the image */
IMAGE *MotionBlur(IMAGE *image, unsigned char BlurAmount)
{
	assert(image);
        int x,y,m;
	unsigned int temp_r , temp_g , temp_b;

	for (x = 0; x < ImageWidth(image); x++)
        	for (y = 0; y < ImageHeight(image) ; y++) 
		{
			temp_r = GetPixelR(image, x, y)/2;
			temp_g = GetPixelG(image, x, y)/2;
			temp_b = GetPixelB(image, x, y)/2;
			
			for (m = 1; m<=BlurAmount ; m++)
			{
				if ((x+m) < ImageWidth(image))
				{
					temp_r = temp_r + GetPixelR(image, x+m, y) * 0.5/BlurAmount;
					temp_g = temp_g + GetPixelG(image, x+m, y) * 0.5/BlurAmount;
					temp_b = temp_b + GetPixelB(image, x+m, y) * 0.5/BlurAmount;
				}
			}	
			SetPixelR(image, x, y, temp_r);
                        SetPixelG(image, x, y, temp_g);
                        SetPixelB(image, x, y, temp_b); 
		}	
        return image;
}

IMAGE *Crop(IMAGE *image, int x, int y, int W, int H)
{
    assert(image);
    int croppedX, croppedY;

    if(x + W > ImageWidth(image))
    {
        W = ImageWidth(image) - x;
    } 
    if(y + H > ImageHeight(image))
    {
        H = ImageHeight(image) - y;
    }
    IMAGE *cropped = CreateImage(W, H);

    for(croppedY = 0; croppedY < ImageHeight(cropped); croppedY++)
    {
        for(croppedX = 0; croppedX < ImageWidth(cropped); croppedX++)
        {
            SetPixelR(cropped, croppedX, croppedY, GetPixelR(image, x + croppedX, y + croppedY));
            SetPixelG(cropped, croppedX, croppedY, GetPixelG(image, x + croppedX, y + croppedY));
            SetPixelB(cropped, croppedX, croppedY, GetPixelB(image, x + croppedX, y + croppedY));
        }
    }
    DeleteImage(image);
    return cropped;     
}

IMAGE *BrightnessAndContrast(IMAGE *image, int brightness, int contrast)
{
    assert(image);
    int x, y;
    int pixelContrastR, pixelContrastG, pixelContrastB;
    int newPixelR, newPixelG, newPixelB;
    double factor = (double)(259 * (contrast + 255)) / (double)(255 * (259 - contrast));

    for(y = 0; y < ImageHeight(image); y++)
    {
        for(x = 0; x < ImageWidth(image); x++)
        {
            pixelContrastR = (int)(factor * (GetPixelR(image, x, y) - 128) + 128);
            pixelContrastG = (int)(factor * (GetPixelG(image, x, y) - 128) + 128);
            pixelContrastB = (int)(factor * (GetPixelB(image, x, y) - 128) + 128);

            newPixelR = pixelContrastR + brightness;
            newPixelG = pixelContrastG + brightness;
            newPixelB = pixelContrastB + brightness;

            if (newPixelR > 255)
            {
                newPixelR = 255;   
            }
            else if (newPixelR < 0)
            {
                newPixelR = 0;
            }

            if (newPixelG > 255)
            {
                newPixelG = 255;
            }
            else if (newPixelG < 0)
            {
                newPixelG = 0;
            }

            if (newPixelB > 255)
            {
                newPixelB = 255;
            }
            else if (newPixelB < 0)
            {
                newPixelB = 0;
            }

            SetPixelR(image, x, y, newPixelR);
            SetPixelG(image, x, y, newPixelG);
            SetPixelB(image, x, y, newPixelB);
        } 
    }
    return image;
}

IMAGE *Resize(IMAGE *image, int percentage)
{
    assert(image);
    int x, y;
    int originalX, originalY;
    if (percentage == 100)
    {
        return image;
    }

    int scaledWidth = ImageWidth(image) * (percentage / 100.00);
    int scaledHeight = ImageHeight(image) * (percentage / 100.00);
    
    IMAGE *scaled = CreateImage(scaledWidth, scaledHeight);
    if (percentage > 100)
    {
        for (y = 0; y < ImageHeight(scaled); y++)
        {
            for (x = 0; x < ImageWidth(scaled); x++)
            {
                originalX = (int)x*ImageWidth(image)/scaledWidth; 
                originalY = (int)y*ImageHeight(image)/scaledHeight;
                SetPixelR(scaled, x, y, GetPixelR(image, originalX, originalY));
                SetPixelG(scaled, x, y, GetPixelG(image, originalX, originalY));
                SetPixelB(scaled, x, y, GetPixelB(image, originalX, originalY));
            }
        }         
    }
    else
    {
        for (y = 0; y < ImageHeight(scaled); y++)
        {
            for (x = 0; x < ImageWidth(scaled); x++)
            {
                originalX = (int)x*ImageWidth(image)/scaledWidth;
                originalY = (int)y*ImageHeight(image)/scaledHeight;
                SetPixelR(scaled, x, y, GetPixelR(image, originalX, originalY));
                SetPixelG(scaled, x, y, GetPixelG(image, originalX, originalY));
                SetPixelB(scaled, x, y, GetPixelB(image, originalX, originalY));
            }
        }

    }
    DeleteImage(image);
    return scaled;   
}

IMAGE *Watermark(IMAGE *image, const IMAGE *watermark_image)
{
    assert(image);
    int x, y;
    int watermarkR, watermarkG, watermarkB;
    int tempR, tempG, tempB;

    for (y = 0; y < ImageHeight(image); y++)
    {
        for (x = 0; x < ImageWidth(image); x++)
        {
            watermarkR = GetPixelR(watermark_image, x % ImageWidth(watermark_image), y % ImageHeight(watermark_image));
            watermarkG = GetPixelG(watermark_image, x % ImageWidth(watermark_image), y % ImageHeight(watermark_image));
            watermarkB = GetPixelB(watermark_image, x % ImageWidth(watermark_image), y % ImageHeight(watermark_image));
            if ((watermarkR + watermarkG + watermarkB) == 0)
            {
                tempR = GetPixelR(image, x, y) * 1.45;
                if(tempR > 255)
                {
                    tempR = 255;   
                }    
                SetPixelR(image, x, y, tempR);
                
                tempG = GetPixelG(image, x, y) * 1.45;
                if(tempG > 255)
                {
                    tempG = 255;
                }
                SetPixelG(image, x, y, tempG);

                tempB = GetPixelB(image, x, y) * 1.45; 
                if(tempB > 255)
                {
                    tempB = 255;
                }
                SetPixelB(image, x, y, tempB);
            }
        }
    }
    return image;    
}



















/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
