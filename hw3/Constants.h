#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SLEN 80                 /* maximum length of file names and string*/
#define SUCCESS 0               /* return code for success */
#define EXIT 16                 /* menu item number for EXIT */
#define MAX_PIXEL 255   /* max pixel value */
#define MIN_PIXEL 0             /* min pixel value */
#define SHUFF_HEIGHT_DIV 4      /* Height division for shuffleing */
#define SHUFF_WIDTH_DIV 4       /* Width division for shuffleing */
#define WIDTH 600               /* image width */
#define HEIGHT 400              /* image height */

// I decided to #define it to keep it consistent and it made the importing the library easier
//const int WIDTH;          /* image width */
//const int HEIGHT;         /* image height */

#endif /* CONSTANTS_H */
