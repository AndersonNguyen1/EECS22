#include "Constants.h"
#include "Advanced.h"

void Noise(int n, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	int x, y = 0;
	int noise_pixels_number = 0;
	srand(0);			/* this makes a random number by using time */

	noise_pixels_number = (n * WIDTH * HEIGHT)/100;

	for(int i = 0; i < noise_pixels_number; i++)
	{
		x = rand() % WIDTH;
		y = rand() % HEIGHT;
		R[x][y] = G[x][y] = B[x][y] = 255;
	}
}

/* Traces the image */
void Sharpen(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
    int             x, y, m, n, a, b;
    unsigned char   tmpR[WIDTH][HEIGHT];
    unsigned char   tmpG[WIDTH][HEIGHT];
    unsigned char   tmpB[WIDTH][HEIGHT];
    for (y = 0; y < HEIGHT; y++){
        for (x = 0; x < WIDTH; x++) {
            tmpR[x][y] = R[x][y];
            tmpG[x][y] = G[x][y];
            tmpB[x][y] = B[x][y];
        }
    }
    int sumR = 0;   /* sum of the intensity differences with neighbors */
    int sumG = 0;
    int sumB = 0;
    for (y = 1; y < HEIGHT - 1; y++){
        for (x = 1; x < WIDTH - 1; x++){
            for (n = -1; n <= 1; n++){
                for (m = -1; m <= 1; m++) {
                    a = (x + m >= WIDTH) ? WIDTH - 1 : (x + m < 0) ? 0 : x + m;
                    b = (y + n >= HEIGHT) ? HEIGHT - 1 : (y + n < 0) ? 0 : y + n;
                    sumR += (tmpR[x][y] - tmpR[a][b]);
                    sumG += (tmpG[x][y] - tmpG[a][b]);
                    sumB += (tmpB[x][y] - tmpB[a][b]);
                }
            }
            sumR += (tmpR[x][y]);
            sumG += (tmpG[x][y]);
            sumB += (tmpB[x][y]);

            R[x][y] = (sumR > MAX_PIXEL) ? MAX_PIXEL: (sumR < 0) ? 0: sumR;
            G[x][y] = (sumG > MAX_PIXEL) ? MAX_PIXEL: (sumG < 0) ? 0: sumG;
            B[x][y] = (sumB > MAX_PIXEL) ? MAX_PIXEL: (sumB < 0) ? 0: sumB;
            sumR = sumG = sumB = 0;
        }
    }
    /* set all four borders to 0 */
    for (y = 0; y < HEIGHT; y++) {
        R[0][y] = 0;
        G[0][y] = 0;
        B[0][y] = 0;
        R[WIDTH - 1][y] = 0;
        G[WIDTH - 1][y] = 0;
        B[WIDTH - 1][y] = 0;
    }
    for (x = 0; x < WIDTH; x++) {
        R[x][0] = 0;
        G[x][0] = 0;
        B[x][0] = 0;
        R[x][HEIGHT - 1] = 0;
        G[x][HEIGHT - 1] = 0;
        B[x][HEIGHT - 1] = 0;
    }
}

/* Posterizes the image */

void Posterize(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], unsigned int rbit, unsigned int gbit, unsigned int bbit)
{
    int x, y = 0;
    int r, g, b;
    for(y = 0; y < HEIGHT; y++)
    {
        for(x = 0; x < WIDTH; x++)
        {
            /* We are going to set the bit posterization to zero */ 
            R[x][y] &= ~(1 << (rbit - 1));
            G[x][y] &= ~(1 << (gbit - 1));
            B[x][y] &= ~(1 << (bbit - 1));

            /* Loops through the R and loops through the bits that are less than rbit and sets them to 1 */
            for(r = 0; r < rbit - 1; r++)
            {
                R[x][y] |= 1 << r;     
            }
            /* Loops through the G and loops through the bits that are less than gbit and sets them to 1 */
            for(g = 0; g < gbit - 1; g++)
            {
                G[x][y] |= 1 << g;
            }
            /* Loops through the B and loops through the bits that are less than bbit and sets them to 1 */
            for(b = 0; b < bbit - 1; b++)
            {
                B[x][y] |= 1 << b;
            }
        }   
    } 	
}

/* Blue the image */

void MotionBlur(int bluramount, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    int             x, y;
    int             offset;
    int             sumR = 0;
    int             sumG = 0;
    int             sumB = 0;
    int             count = 0;
    unsigned char   tmpR[WIDTH][HEIGHT];
    unsigned char   tmpG[WIDTH][HEIGHT];
    unsigned char   tmpB[WIDTH][HEIGHT];
    for (y = 0; y < HEIGHT; y++){
        for (x = 0; x < WIDTH; x++) {
            tmpR[x][y] = R[x][y];
            tmpG[x][y] = G[x][y];
            tmpB[x][y] = B[x][y];
        }
    }
    for(y = 0; y < HEIGHT; y++)
    {
        for(x = 0; x < WIDTH; x++)
        {
            for(offset = 1; offset <= bluramount; offset++)
            {
                if((x + offset) <= WIDTH)
                {
                    sumR += R[x + offset][y];
                    sumG += G[x + offset][y];
                    sumB += B[x + offset][y];
                    count++;
                }                    
            } 
            R[x][y] = (R[x][y] + (sumR/count))/2; 
            G[x][y] = (G[x][y] + (sumG/count))/2;
            B[x][y] = (B[x][y] + (sumB/count))/2;
            sumR = 0;
            sumG = 0;
            sumB = 0;
            count = 0;
        }
    }
} 
 























