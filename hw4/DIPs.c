#include "DIPs.h"
#include "Image.h"

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>

/* make the picture color black & white */
IMAGE *BlackNWhite(IMAGE *image)
{
    assert(image);
    int x, y, tmp;

    for (y = 0; y < ImageHeight(image); y++)
    {   
        for (x = 0; x < ImageWidth(image); x++) 
        {
            tmp = (GetPixelR(image, x, y) + GetPixelG(image, x, y) + GetPixelB(image, x, y)) / 3;
            SetPixelR(image, x, y, tmp);
            SetPixelG(image, x, y, tmp);
            SetPixelB(image, x, y, tmp);
        }
    }
    return image;
}

/* reverse image color */
IMAGE *Negative(IMAGE *image)
{
    assert(image);
    int x, y;
    for (y = 0; y < ImageHeight(image); y++) {
        for (x = 0; x < ImageWidth(image); x++) 
        {
            SetPixelR(image, x, y, MAX_PIXEL - GetPixelR(image, x, y));
            SetPixelG(image, x, y, MAX_PIXEL - GetPixelG(image, x, y));
            SetPixelB(image, x, y, MAX_PIXEL - GetPixelB(image, x, y));
        }
    }
    return image;
}

/*colorfiler */
IMAGE *ColorFilter (IMAGE *image, int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b)
{
    assert(image);
    replace_r = (replace_r > MAX_PIXEL)? MAX_PIXEL : (replace_r < 0) ? 0 : replace_r;
    replace_r = (replace_r > MAX_PIXEL)? MAX_PIXEL : (replace_r < 0) ? 0 : replace_r;
    replace_r = (replace_r > MAX_PIXEL)? MAX_PIXEL : (replace_r < 0) ? 0 : replace_r;
    int x, y;
    for (y = 0; y < ImageHeight(image); y++)
    {
        for (x = 0; x < ImageWidth(image); x++)
        {
            if (abs(GetPixelR(image, x, y) - target_r) <= threshold && abs(GetPixelG(image, x, y) - target_g) <= threshold && abs(GetPixelB(image, x, y) - target_b) <= threshold)
            {
                SetPixelR(image, x, y, replace_r);
                SetPixelG(image, x, y, replace_g);
                SetPixelB(image, x, y, replace_b);
            }
        }
    }
    return image;
}

/* Add edge to the image*/
IMAGE *Edge(IMAGE *image) 
{
    assert(image);
    int x, y, m, n, a, b;

    IMAGE *temp = CreateImage(ImageWidth(image), ImageHeight(image));
    
    for (y = 0; y < ImageHeight(image); y++){
        for (x = 0; x < ImageWidth(image); x++)
        {
             SetPixelR(temp, x, y, GetPixelR(image, x, y));
             SetPixelG(temp, x, y, GetPixelG(image, x, y));
             SetPixelB(temp, x, y, GetPixelB(image, x, y));
        }
    }

    int sumR = 0;    /*sum of the intensity differences with neighbors */
    int sumG = 0;
    int sumB = 0;
    for (y = 1; y < ImageHeight(image) - 1; y++){
        for (x = 1; x < ImageWidth(image) - 1; x++){
            for (n = -1; n <= 1; n++){
                for (m = -1; m <= 1; m++) {
                    a = (x + m >= ImageWidth(image)) ? ImageWidth(image) - 1 : (x + m < 0) ? 0 : x + m;
                    b = (y + n >= ImageHeight(image)) ? ImageHeight(image) - 1 : (y + n < 0) ? 0 : y + n;
                    sumR += GetPixelR(temp, x, y) - GetPixelR(temp, a, b);
                    sumG += GetPixelG(temp, x, y) - GetPixelG(temp, a, b);
                    sumB += GetPixelB(temp, x, y) - GetPixelB(temp, a, b);
                }
            }
            SetPixelR(image, x, y, (sumR > MAX_PIXEL) ? MAX_PIXEL: (sumR < 0) ? 0: sumR);
            SetPixelG(image, x, y, (sumG > MAX_PIXEL) ? MAX_PIXEL: (sumG < 0) ? 0: sumG);
            SetPixelB(image, x, y, (sumB > MAX_PIXEL) ? MAX_PIXEL: (sumB < 0) ? 0: sumB);
            sumR = sumG = sumB = 0;
        }
    }
    /* set all four borders to 0 */
    for (y = 0; y < ImageHeight(image); y++)
    {
        SetPixelR(image, 0, y, 0);
        SetPixelG(image, 0, y, 0);
        SetPixelB(image, 0, y, 0);
        
        SetPixelR(image, ImageWidth(image) - 1, y, 0);
        SetPixelG(image, ImageWidth(image) - 1, y, 0);
        SetPixelB(image, ImageWidth(image) - 1, y, 0);        
    }
    for (x = 0; x < ImageWidth(image); x++) 
    {
        SetPixelR(image, x, 0, 0);
        SetPixelG(image, x, 0, 0);
        SetPixelB(image, x, 0, 0);

        SetPixelR(image, x, ImageHeight(image) - 1, 0);
        SetPixelG(image, x, ImageHeight(image) - 1, 0);
        SetPixelB(image, x, ImageHeight(image) - 1, 0);
    }
    DeleteImage(temp);
    return image;
}

/* flip image vertically */
IMAGE *VFlip(IMAGE *image)
{
    assert(image);   
    int             x, y;
    unsigned char   r, g, b;
    
    for (y = 0; y < (ImageHeight(image))/2; y ++) 
    {
        for (x = 0; x < ImageWidth(image); x ++) 
        {
            r = GetPixelR(image, x, ImageHeight(image) - 1 - y);
            g = GetPixelG(image, x, ImageHeight(image) - 1 - y);
            b = GetPixelG(image, x, ImageHeight(image) - 1 - y);
            
            SetPixelR(image, x, ImageHeight(image) - 1 - y, GetPixelR(image, x, y));
            SetPixelG(image, x, ImageHeight(image) - 1 - y, GetPixelG(image, x, y));
            SetPixelB(image, x, ImageHeight(image) - 1 - y, GetPixelB(image, x, y));
            
            SetPixelR(image, x, y, r);
            SetPixelG(image, x, y, g);
            SetPixelB(image, x, y, b);
        }
    }
    return image;
}

/* mirror image vertically */
IMAGE *VMirror(IMAGE *image) 
{
    assert(image);
    int x, y;
    for (y = 0; y < ImageHeight(image) / 2; y++) 
    {
        for (x = 0; x < ImageWidth(image); x++) 
        {
            SetPixelR(image, x, ImageHeight(image) - 1 - y, GetPixelR(image, x, y));
            SetPixelG(image, x, ImageHeight(image) - 1 - y, GetPixelG(image, x, y));
            SetPixelB(image, x, ImageHeight(image) - 1 - y, GetPixelB(image, x, y));
        }
    }
    return image;
}

int GenerateRandomNumber(int min, int max)
{
    return (rand()%(max - min) + min);
}

/* Shuffle the image */
IMAGE *Shuffle(IMAGE *image)
{
    assert(image);
    int x = 0;
    int y = 0;
    int i = 0;
    for(i = 0; i < 16; i++)
    {
        int random_i = GenerateRandomNumber(0, 15);
        for(y = 0; y < ImageHeight(image)/4; y++)
        {
            for(x = 0; x < ImageWidth(image)/4; x++)
            {
                int piece_width = ImageWidth(image)/4;
                int piece_height = ImageHeight(image)/4;
                int i_xpos = (i%4)*piece_width + x;
                int i_ypos = (i/4)*piece_height + y;
                int random_i_xpos = (random_i%4)*piece_width + x;
                int random_i_ypos = (random_i/4)*piece_height + y;
                int r_temp = GetPixelR(image, i_xpos, i_ypos);
                int g_temp = GetPixelG(image, i_xpos, i_ypos);
                int b_temp = GetPixelB(image, i_xpos, i_ypos);

                SetPixelR(image, i_xpos, i_ypos, GetPixelR(image, random_i_xpos, random_i_ypos));
                SetPixelG(image, i_xpos, i_ypos, GetPixelG(image, random_i_xpos, random_i_ypos));
                SetPixelB(image, i_xpos, i_ypos, GetPixelB(image, random_i_xpos, random_i_ypos));

                SetPixelR(image, random_i_xpos, random_i_ypos, r_temp);
                SetPixelG(image, random_i_xpos, random_i_ypos, g_temp);
                SetPixelB(image, random_i_xpos, random_i_ypos, b_temp);
            }
        }
    }
    return image;
}

/* add border to the image */
IMAGE *AddBorder(IMAGE *image, char color[SLEN], int border_width)
{
    assert(image); 
    int x, y;
    int border_r = 255;
    int border_g = 255;
    int border_b = 255;
    if (!strcmp(color, "black")) {
        border_r = 0;
        border_g = 0;
        border_b = 0;
    } else if (!strcmp(color, "white")) {
        border_r = 255;
        border_g = 255;
        border_b = 255;
    } else if (!strcmp(color, "red")) {
        border_r = 255;
        border_g = 0;
        border_b = 0;
    } else if (!strcmp(color, "green")) {
        border_r = 0;
        border_g = 255;
        border_b = 0;
    } else if (!strcmp(color, "blue")) {
        border_r = 0;
        border_g = 0;
        border_b = 255;
    } else if (!strcmp(color, "yellow")) {
        border_r = 255;
        border_g = 255;
        border_b = 0;
    } else if (!strcmp(color, "cyan")) {
        border_r = 0;
        border_g = 255;
        border_b = 255;
    } else if (!strcmp(color, "pink")) {
        border_r = 255;
        border_g = 192;
        border_b = 203;
    } else if (!strcmp(color, "orange")) {
        border_r = 255;
        border_g = 165;
        border_b = 0;
    } else {
        printf("Unsurported color.\n");
        return image;
    }
    const int X_BORDER_WIDTH = border_width * 9 / 16;
    for (y = 0; y < ImageHeight(image); y++) {
        for (x = 0; x < ImageWidth(image); x++) {
            if ((y < border_width) || (y > ImageHeight(image) - 1 - border_width) ||
                    (x < X_BORDER_WIDTH) || (x > ImageWidth(image) - 1 - X_BORDER_WIDTH)) 
            {
                SetPixelR(image, x, y, border_r);
                SetPixelG(image, x, y, border_g);
                SetPixelB(image, x, y, border_b);
            }
        }
    }
    return image;
}

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
