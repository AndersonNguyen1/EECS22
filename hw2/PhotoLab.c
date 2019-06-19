/*********************************************************************/
/* PhotoLab.c: assignment 2 for EECS 22 in Fall 2017                 */
/*                                                                   */
/* modifications: (Saeed Karimi Bidhendi)                            */
/* 09/27/17 RD	adjusted for lecture usage                           */
/*********************************************************************/

/* Author: Amderson Nguyen */

/*** header files ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*** global definitions ***/

const int WIDTH  = 600;	/* image width */
const int HEIGHT = 400;	/* image height */
const int SLEN   =  80;	/* max. string length */

/*** function declarations ***/

void PrintMenu();

/* read image from a file */
int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT],
              unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* save a processed image */
int SaveImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT],
              unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* change color image to black & white */
void BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
                 unsigned char B[WIDTH][HEIGHT]);

/* reverse image color */
void Negative(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
              unsigned char B[WIDTH][HEIGHT]);

/* color filter */
void ColorFilter(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
                 unsigned char B[WIDTH][HEIGHT], int target_r, int target_g,
                 int target_b, int threshold, int replace_r, int replace_g, int replace_b);

/* edge detection */
void Edge(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
          unsigned char B[WIDTH][HEIGHT]);

/* shuffle an image */
void Shuffle(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
             unsigned char B[WIDTH][HEIGHT]);

/* flip image vertically */
void VFlip(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
           unsigned char B[WIDTH][HEIGHT]);

/* mirror image vertically */
void VMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
             unsigned char B[WIDTH][HEIGHT]);

/* add border */
void AddBorder(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
               unsigned char B[WIDTH][HEIGHT], char color[SLEN], int border_width);

void Boundcheck(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], int r_sum, int g_sum, int b_sum, int x, int y);

/* Test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
              unsigned char B[WIDTH][HEIGHT]);

/*** main program ***/

int main(void)
{
    unsigned char R[WIDTH][HEIGHT];
    unsigned char G[WIDTH][HEIGHT];
    unsigned char B[WIDTH][HEIGHT];

    char fname[SLEN];
    int user_input;
    int r_target, g_target, b_target;
    int threshold;
    int r_replace, g_replace, b_replace;
    int user_width = 0;
    char color[79];

    srand(time(NULL)); 

    /* runs program indefinitely until told to stop */
    while(1)
    {
        PrintMenu();
        scanf("%d", &user_input);
        switch (user_input)
        {
            case 1:
                      printf("Please input the file name to load: ");
                      scanf("%s", fname);
                      LoadImage(fname, R, G, B);
                      break;
            case 2:
                      printf("Please input the file name to save: ");
                      scanf("%79s", &fname[0]);
                      SaveImage(fname, R, G, B);
                      break;
            case 3:
                      BlackNWhite(R, G, B);
                      printf("\"Black & White\" operation is done!\n");
                      break;
            case 4:
                      Negative(R, G, B);
                      printf("\"Negative\" operation is done!\n");
                      break;
            case 5:
                      printf("Enter Red   component for the target color: ");
                      scanf("%d", &r_target);
                      printf("Enter Green component for the target color: ");
                      scanf("%d", &g_target);
                      printf("Enter Blue  component for the target color: ");
                      scanf("%d", &b_target);
                      printf("Enter threshold for the color difference: ");
                      scanf("%d", &threshold);
                      printf("Enter value for Red   component in the target color: ");
                      scanf("%d", &r_replace);
                      printf("Enter value for Green component in the target color: ");
                      scanf("%d", &g_replace);
                      printf("Enter value for Blue  component in the target color: ");
                      scanf("%d", &b_replace);
                      ColorFilter(R, G, B, r_target, g_target, b_target, threshold, r_replace, g_replace, b_replace);
                      printf("\"Color Filter\" operation done!\n");
                      break;
            case 6:
                      Edge(R, G, B);
                      printf("\"Edge\" operation done!\n");
                      break;
            case 7:
                      Shuffle(R, G, B);
                      printf("\"Shuffle\" operation done!\n");
                      break;
            case 8:
                      VFlip(R, G, B);
                      printf("\"VFlip\" operation done!\n");
                      break;
            case 9:
                      VMirror(R, G, B);
                      printf("\"VMirror\" operation done!\n");
                      break;
            case 10:
                      printf("Enter border width: ");
                      scanf("%d", &user_width);
                      printf("Available border colors : black, white, red, green, blue, yellow, cyan, pink, orange\n");
                      printf("Select border color from the options: ");
                      scanf("%s", color);
                      AddBorder(R, G, B, color, user_width);
                      printf("\"AddBorder\" operation done!\n");
                      break;
            case 11:
                      AutoTest(R, G, B);
                      break;        
            case 12:
                      exit(0);
        }
    }

    if (LoadImage("HSSOE.ppm", R, G, B) != 0)
        { return 10; }

    return 0;
} /* end of main */
 
/*** function definitions ***/

void PrintMenu()
{
    printf("1: Load a PPM image\n");
    printf("2: Save an image in PPM and JPEG format\n");
    printf("3: Change a color image to Black and White\n");
    printf("4: Make a negative of an image\n");
    printf("5: Color filter an image\n");
    printf("6: Sketch the edge of an image\n");
    printf("7: Shuffle an image\n");
    printf("8: Flip an image vertically\n");
    printf("9: Mirror an image vertically\n");
    printf("10: Add Border to an image\n");
    printf("11: Test all functions\n");
    printf("12: Exit\n");
    printf("please make your choice: ");
}

/* read a photo from the specified file into the specified */
/* RGB data structure; returns 0 for success, >0 for error */


void BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    int x, y, z = 0;
    for(y = 0; y < HEIGHT; y++)
    {
        for(x = 0; x < WIDTH; x++)
        {
            z = (R[x][y] + G[x][y] + B[x][y])/3;
            R[x][y] = z;
            G[x][y] = z;
            B[x][y] = z;
        }
    }
}

void Negative(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    int x, y = 0;
    for(y = 0; y < HEIGHT; y++)
    {
        for(x = 0; x < WIDTH; x++)
        {
            R[x][y] = 255 - R[x][y];
            G[x][y] = 255 - G[x][y];
            B[x][y] = 255 - B[x][y];
        }
    }    
}

void ColorFilter(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], int r_target, int g_target, int b_target, int threshold, int r_replace, int g_replace, int b_replace)
{
    int x, y = 0;
    for(y = 0; y < HEIGHT; y++)
    {
        for(x = 0; x < WIDTH; x++)
        {
            if(((r_target - threshold) < R[x][y] && R[x][y] < (r_target + threshold)) && ((g_target - threshold) < G[x][y] && G[x][y] < (g_target + threshold)) && ((b_target - threshold) < B[x][y] && B[x][y] < (b_target + threshold)))
            {
                R[x][y] = R[x][y] * r_replace;
                G[x][y] = G[x][y] * g_replace;
                B[x][y] = B[x][y] * b_replace;
  
                if(R[x][y] > 255)
                    { R[x][y] = 255; }
                if(R[x][y] < 0)
                    { R[x][y] = 0; }
                if(G[x][y] > 255)
                    { G[x][y] = 255; }
                if(G[x][y] < 0)
                    { G[x][y] = 0; }
                if(B[x][y] > 255)
                    { B[x][y] = 255; }
                if(B[x][y] < 0)
                    { B[x][y] = 0; }
            }
            else
                { continue; }
        }       
    } 
}

void Edge(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    int x, y = 0;
    unsigned char R2[WIDTH][HEIGHT];
    unsigned char G2[WIDTH][HEIGHT];
    unsigned char B2[WIDTH][HEIGHT];
    int r_sum = 0;
    int g_sum = 0;
    int b_sum = 0;

    /* fills in the new array with the original array's values */
    for(y = 0; y < HEIGHT; y++)
    {
        for(x = 0; x < WIDTH; x++)
        {
            R2[x][y] = R[x][y];
            G2[x][y] = G[x][y];
            B2[x][y] = B[x][y];
        }
    }

    for(y = 1; y < HEIGHT - 1; y++)
    {
        for(x = 1; x < WIDTH - 1; x++)
        {
            r_sum = 8 * R2[x][y] - R2[x - 1][y - 1] - R2[x - 1][y] - R2[x - 1][y + 1] - R2[x][y + 1] - R2[x + 1][y + 1] - R2[x + 1][y] - R2[x + 1][y - 1] - R2[x][y - 1];
            g_sum = 8 * G2[x][y] - G2[x - 1][y - 1] - G2[x - 1][y] - G2[x - 1][y + 1] - G2[x][y + 1] - G2[x + 1][y + 1] - G2[x + 1][y] - G2[x + 1][y - 1] - G2[x][y - 1];
            b_sum = 8 * B2[x][y] - B2[x - 1][y - 1] - B2[x - 1][y] - B2[x - 1][y + 1] - B2[x][y + 1] - B2[x + 1][y + 1] - B2[x + 1][y] - B2[x + 1][y - 1] - B2[x][y - 1];
            Boundcheck(R, G, B, r_sum, g_sum, b_sum, x, y);
        }
    }
    for(y = 0; y < HEIGHT; y++)
    {
        for(x = 0; x < WIDTH; x++)
        {
            if(x == 0 && y == 0)
            {
                r_sum = 3*R2[x][y] - R2[x + 1][y] - R2[x][y - 1] - R2[x + 1][y - 1];
                g_sum = 3*G2[x][y] - G2[x + 1][y] - G2[x][y - 1] - G2[x + 1][y - 1];
                b_sum = 3*B2[x][y] - B2[x + 1][y] - B2[x][y - 1] - B2[x + 1][y - 1];
                Boundcheck(R, G, B, r_sum, g_sum, b_sum, x, y);
            }

            if(x == WIDTH - 1 && y == 0)
            {
                r_sum = 3*R2[x][y] - R2[x - 1][y] - R2[x - 1][y - 1] - R2[x][y - 1];
                g_sum = 3*G2[x][y] - G2[x - 1][y] - G2[x - 1][y - 1] - G2[x][y - 1];
                b_sum = 3*B2[x][y] - B2[x - 1][y] - B2[x - 1][y - 1] - B2[x][y - 1];
                Boundcheck(R, G, B, r_sum, g_sum, b_sum, x, y);
            }

            if(x == 0 && y == HEIGHT - 1)
            {
                r_sum = 3*R2[x][y] - R2[x + 1][y] - R2[x][y + 1] - R2[x + 1][y + 1];
                g_sum = 3*G2[x][y] - G2[x + 1][y] - G2[x][y + 1] - G2[x + 1][y + 1];
                b_sum = 3*B2[x][y] - B2[x + 1][y] - B2[x][y + 1] - B2[x + 1][y + 1];
                Boundcheck(R, G, B, r_sum, g_sum, b_sum, x, y);
            }
 
            if(x == WIDTH - 1 && y == HEIGHT - 1)
            {
                r_sum = 3*R2[x][y] - R2[x - 1][y] - R2[x][y + 1] - R2[x - 1][y + 1];
                g_sum = 3*G2[x][y] - G2[x - 1][y] - G2[x][y + 1] - G2[x - 1][y + 1];
                b_sum = 3*B2[x][y] - B2[x - 1][y] - B2[x][y + 1] - B2[x - 1][y + 1];
                Boundcheck(R, G, B, r_sum, g_sum, b_sum, x, y);
            }

            if(x == WIDTH - 1 && y != 0 && y !=  HEIGHT - 1)
            {
                r_sum = 5*R2[x][y] - R2[x - 1][y - 1] - R2[x][y - 1] - R2[x - 1][y] - R2[x - 1][y - 1] - R2[x][y - 1];
                g_sum = 5*G2[x][y] - G2[x - 1][y - 1] - G2[x][y - 1] - G2[x - 1][y] - G2[x - 1][y - 1] - G2[x][y - 1];
                b_sum = 5*B2[x][y] - B2[x - 1][y - 1] - B2[x][y - 1] - B2[x - 1][y] - B2[x - 1][y - 1] - B2[x][y - 1];
                Boundcheck(R, G, B, r_sum, g_sum, b_sum, x, y);
            } 

            if(x == 0 && y != 0 && y !=  HEIGHT - 1)
            {
                r_sum = 5*R2[x][y] - R2[x + 1][y - 1] - R2[x][y - 1] - R2[x + 1][y] - R2[x + 1][y - 1] - R2[x][y - 1];
                g_sum = 5*G2[x][y] - G2[x + 1][y - 1] - G2[x][y - 1] - G2[x + 1][y] - G2[x + 1][y - 1] - G2[x][y - 1];
                b_sum = 5*B2[x][y] - B2[x + 1][y - 1] - B2[x][y - 1] - B2[x + 1][y] - B2[x + 1][y - 1] - B2[x][y - 1];
                Boundcheck(R, G, B, r_sum, g_sum, b_sum, x, y);
            }

            if(x != 0 && x != WIDTH - 1 && y == HEIGHT - 1)
            {
                r_sum = 5*R2[x][y] - R2[x - 1][y - 1] - R2[x][y - 1] - R2[x + 1][y - 1] - R2[x - 1][y] - R2[x + 1][y];
                g_sum = 5*G2[x][y] - G2[x - 1][y - 1] - G2[x][y - 1] - G2[x + 1][y - 1] - G2[x - 1][y] - G2[x + 1][y];
                b_sum = 5*B2[x][y] - B2[x - 1][y - 1] - B2[x][y - 1] - B2[x + 1][y - 1] - B2[x - 1][y] - B2[x + 1][y];
                Boundcheck(R, G, B, r_sum, g_sum, b_sum, x, y);
            }

            if(x != 0 && x != WIDTH - 1 && y == 0)
            {
                r_sum = 5*R2[x][y] - R2[x - 1][y + 1] - R2[x][y + 1] - R2[x - 1][y] - R2[x - 1][y + 1] - R2[x + 1][y];
                g_sum = 5*G2[x][y] - G2[x - 1][y + 1] - G2[x][y + 1] - G2[x - 1][y] - G2[x - 1][y + 1] - G2[x + 1][y];
                b_sum = 5*B2[x][y] - B2[x - 1][y + 1] - B2[x][y + 1] - B2[x - 1][y] - B2[x - 1][y + 1] - B2[x + 1][y];
                Boundcheck(R, G, B, r_sum, g_sum, b_sum, x, y); 
            }
        }
    }
}

int GenerateRandomNumber(int min, int max)
{
    return (rand()%(max - min) + min);    
}

void Shuffle(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    int x = 0;
    int y = 0;
    int i = 0;
    for(i = 0; i < 16; i++)
    {
        int random_i = GenerateRandomNumber(0, 15); 
        for(y = 0; y < HEIGHT/4; y++)
        {
            for(x = 0; x < WIDTH/4; x++)
            {
                int piece_width = WIDTH/4;
                int piece_height = HEIGHT/4;
                int i_xpos = (i%4)*piece_width + x;
                int i_ypos = (i/4)*piece_height + y;
                int random_i_xpos = (random_i%4)*piece_width + x;
                int random_i_ypos = (random_i/4)*piece_height + y;
                int r_temp = R[i_xpos][i_ypos];
                int g_temp = G[i_xpos][i_ypos];
                int b_temp = B[i_xpos][i_ypos];
               
                R[i_xpos][i_ypos] = R[random_i_xpos][random_i_ypos];
                G[i_xpos][i_ypos] = G[random_i_xpos][random_i_ypos];
                B[i_xpos][i_ypos] = B[random_i_xpos][random_i_ypos]; 

                R[random_i_xpos][random_i_ypos] = r_temp;
                G[random_i_xpos][random_i_ypos] = g_temp;
                B[random_i_xpos][random_i_ypos] = b_temp; 
            }
        }
    } 
}

void VFlip(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    int x = 0;
    int y = 0;
    int r_temp = 0;
    int g_temp = 0;
    int b_temp = 0;

    for(y = 0; y < HEIGHT/2; y++)
    {
        for(x = 0; x < WIDTH; x++)
        {
            r_temp = R[x][y];
            g_temp = G[x][y];
            b_temp = B[x][y];
            R[x][y] = R[x][HEIGHT - 1 - y];
            G[x][y] = G[x][HEIGHT - 1 - y];
            B[x][y] = B[x][HEIGHT - 1 - y];
            R[x][HEIGHT - 1 - y] = r_temp;
            G[x][HEIGHT - 1 - y] = g_temp;
            B[x][HEIGHT - 1 - y] = b_temp;
        }
    }
} 

void VMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    int x, y = 0;
    for(y = 0; y < HEIGHT/2; y++)
    {
        for(x = 0; x < WIDTH; x++)
        {
            R[x][HEIGHT - y] = R[x][y];
            G[x][HEIGHT - y] = G[x][y];
            B[x][HEIGHT - y] = B[x][y];     
        }
    }
}

void AddBorder(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
               unsigned char B[WIDTH][HEIGHT], char color[SLEN], int border_width)
{
    int x, y = 0;
    int r, g, b = 0;

    if(strcmp(color, "black") == 0)
    {
        /* already black, no action */
    }
    else if(strcmp(color, "white") == 0)
    {
        r = 255;
        g = 255;
        b = 255;    
    }
    else if(strcmp(color, "red") == 0)
    {
        r = 255;
    }
    else if(strcmp(color, "green") == 0)
    {
        g = 255;
    }
    else if(strcmp(color, "blue") == 0)
    {
        b = 255;
    }
    else if(strcmp(color, "yellow") == 0)
    {
        r = 255;
        g = 255;
    }
    else if(strcmp(color, "cyan") == 0)
    {
        g = 255;
        b = 255;
    }
    else if(strcmp(color, "pink") == 0)
    {
        r = 255;
        g = 192;
        b = 203;
    }
    else if(strcmp(color, "orange") == 0)
    {
        r = 255;
        g = 165;
    }
    else 
    {
        return;
    }

    for(y = 0; y < HEIGHT; y++)
    {
        for(x = 0; x < WIDTH; x++)
        {
            if(x < border_width || x > (WIDTH - border_width) || y < border_width || y > (HEIGHT - border_width))
            {
                R[x][y] = r;
                G[x][y] = g;
                B[x][y] = b;
            } 
        }
    }
}

void Boundcheck(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], int r_sum, int g_sum, int b_sum, int x, int y)
{
    if(r_sum <= 255 && r_sum >=0)
        R[x][y] = r_sum;
    if(r_sum > 255)
        R[x][y] = 255;
    if(r_sum < 0)
        R[x][y] = 0;
    if(g_sum <= 255 && g_sum >=0)
        G[x][y] = g_sum;
    if(g_sum > 255)
	G[x][y] = 255;
    if(g_sum < 0)
        G[x][y] = 0;
    if(b_sum <= 255 && b_sum >=0)
        B[x][y] = b_sum;
    if(b_sum > 255)
        B[x][y] = 255;
    if(b_sum < 0)
        B[x][y] = 0;
}

int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
        FILE           *File;
        char            Type[SLEN];
        int             Width, Height, MaxValue;
        int             x, y;
        char            ftype[] = ".ppm";
        char            fname_tmp[SLEN];      
        strcpy(fname_tmp, fname);
        strcat(fname_tmp, ftype);

        File = fopen(fname_tmp, "r");
        if (!File) {
                printf("Cannot open file \"%s\" for reading!\n", fname);
                return 1;
                    }
        fscanf(File, "%79s", Type);
        if (Type[0] != 'P' || Type[1] != '6' || Type[2] != 0) {
                printf("\nUnsupported file format!\n");
                return 2;
                                                                }
        fscanf(File, "%d", &Width);
        if (Width != WIDTH) {
                printf("\nUnsupported image width %d!\n", Width);
                return 3;
                             }
        fscanf(File, "%d", &Height);
        if (Height != HEIGHT) {
                 printf("\nUnsupported image height %d!\n", Height);
                 return 4;
                              }
        fscanf(File, "%d", &MaxValue);
        if (MaxValue != 255) {
                 printf("\nUnsupported image maximum value %d!\n", MaxValue);
                 return 5;
                            }
        if ('\n' != fgetc(File)) {
                 printf("\nCarriage return expected!\n");
                 return 6;
                                }
        for (y = 0; y < HEIGHT; y++)
             for (x = 0; x < WIDTH; x++) {
                         R[x][y] = fgetc(File);
                         G[x][y] = fgetc(File);
                         B[x][y] = fgetc(File);
                                         }
        if (ferror(File)) {
             printf("\nFile error while reading from file!\n");
             return 7;
                           }
        printf("%s was read.\n", fname_tmp);
        fclose(File);
        return 0;
}

int SaveImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
        FILE    *File;
        int x, y;
        char    SysCmd[SLEN * 5];
        char    ftype[] = ".ppm";
        char    fname_tmp[SLEN];  /*avoid to modify on the original pointer, 11/10/10, X.Han*/
        char    fname_tmp2[SLEN];

        strcpy(fname_tmp, fname);
        strcpy(fname_tmp2, fname);
        strcat(fname_tmp2, ftype);

        File = fopen(fname_tmp2, "w");
        if (!File) {
                printf("Cannot open file \"%s\" for writing!\n", fname);
                return 1;
                   }
        fprintf(File, "P6\n");
        fprintf(File, "%d %d\n", WIDTH, HEIGHT);
        fprintf(File, "255\n");
        for (y = 0; y < HEIGHT; y++)
                 for (x = 0; x < WIDTH; x++) {
                               fputc(R[x][y], File);
                               fputc(G[x][y], File);
                               fputc(B[x][y], File);
                                              }
         if (ferror(File)) {
                  printf("\nFile error while writing to file!\n");
                  return 2;
                            }
         fclose(File);
         printf("%s was saved. \n", fname_tmp2);
   /*
     *      * rename file to image.ppm, convert it to ~/public_html/<fname>.jpg
     *           * and make it world readable
                                   *                */
        sprintf(SysCmd, "/users/grad2/doemer/eecs22/bin/pnmtojpeg_hw2.tcsh %s", fname_tmp2);
        if (system(SysCmd) != 0) {
        printf("\nError while converting to JPG:\nCommand \"%s\" failed!\n", SysCmd);
        return 3;
                                  }
        printf("%s.jpg was stored.\n", fname_tmp);
        return 0;
}

void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    char fname[79] = "HSSOE";
    char sname[79];
    
    LoadImage(fname, R, G, B);
    BlackNWhite(R, G, B);
    strcpy(sname, "bw");/*string copy function to prepare the file name to be saved*/
    SaveImage(sname, R, G, B);
    printf("Black and White tested!\n\n");
    
    LoadImage(fname, R, G, B);
    Negative(R, G, B);
    strcpy(sname, "negative");/*string copy function to prepare the file name to be saved*/
    SaveImage(sname, R, G, B);
    printf("Negative tested!\n\n");
    
    LoadImage(fname, R, G, B);
    ColorFilter(R, G, B, 190, 100, 150, 60, 0, 0, 255);
    strcpy(sname, "colorfilter");
    SaveImage(sname, R, G, B);
    printf("Color Filter tested!\n\n");

    LoadImage(fname, R, G, B);
    Edge(R, G, B);
    strcpy(sname, "edge");
    SaveImage(sname, R, G, B);
    printf("Edge tested!\n\n");

    LoadImage(fname, R, G, B);
    Shuffle(R, G, B);
    strcpy(sname, "shuffle");
    SaveImage(sname, R, G, B);
    printf("Shuffle tested!\n\n");

    LoadImage(fname, R, G, B);
    VFlip(R, G, B);
    strcpy(sname, "vflip");
    SaveImage(sname, R, G, B);
    printf("VFlip tested!\n\n");

    LoadImage(fname, R, G, B);
    VMirror(R, G, B);
    strcpy(sname, "vmirror");
    SaveImage(sname, R, G, B);
    printf("VMirror tested!\n\n");

    LoadImage(fname, R, G, B);
    AddBorder(R, G, B, "yellow", 40);
    strcpy(sname, "border");
    SaveImage(sname, R, G, B);
    printf("AddBorder tested!\n\n");
} 
