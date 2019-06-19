#ifndef TEST_H
#define TEST_H

/* Test all DIPs */
int AutoTest(void);

/* test parameters used in AutoTest() */
/* parameters for color filter */
#define CF_TARGET_R 190
#define CF_TARGET_G 100
#define CF_TARGET_B 150
#define CF_THRESHOLD 60
#define CF_REPLACED_R 0
#define CF_REPLACED_G 0
#define CF_REPLACED_B 255

/* border */
#define BORDER_WIDTH 32

/* noise */
#define NOISE_PERCENTAGE 9

/* posterize */
#define R_BITS 6
#define G_BITS 7
#define B_BITS 8

/* motion blur */
#define BLUR_AMOUNT 50

/* crop */
#define CROP_X 100
#define CROP_Y 200
#define CROP_WIDTH 400
#define CROP_HEIGHT 200

/* resize */
#define BIG_RESIZE_PERCENTAGE 170
#define SMALL_RESIZE_PERCENTAGE 60

/* brightness and contrast */
#define BRIGHTNESS 20
#define CONTRAST 200

#endif /* TEST_H */
