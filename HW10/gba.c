#include "gba.h"
#include "geometry.h"
#include "graphics.h"

volatile unsigned short *videoBuffer = (volatile unsigned short *)0x6000000;
u32 vBlankCounter = 0;

void waitForVBlank(void) {

    // a while loop that loops until we're NOT in vBlank anymore:
    
    while(*SCANLINECOUNTER < 160);


    // a while loop that keeps going until we're in vBlank:

    while(*SCANLINECOUNTER > 160);
    
    // Finally, increment the vBlank counter:

    vBlankCounter += 1;

}

static int __qran_seed= 42;
static int qran(void) {
    __qran_seed= 1664525*__qran_seed+1013904223;
    return (__qran_seed>>16) & 0x7FFF;
}

int randint(int min, int max) {
    return (qran()*(max-min)>>15)+min;
}

//sets pixel at position x,y to certain color
void setPixel(int x, int y, volatile u16 color) {
    DMA[3].src = &color;
    DMA[3].dst = videoBuffer + (y * WIDTH) + x;
    DMA[3].cnt = 1 | DMA_SOURCE_FIXED | DMA_DESTINATION_FIXED | DMA_ON;
}

//Draws a rectangle of a certain color
void drawRectDMA(int x, int y, int width, int height, volatile u16 color) {
    for (int i = 0; i < height; i++) {
        DMA[3].src = &color;
        DMA[3].dst = videoBuffer + ((x + i) * WIDTH) + y;
        DMA[3].cnt = width | DMA_SOURCE_FIXED | DMA_DESTINATION_INCREMENT | DMA_ON;
    }
}

//Draws a full screen image with only one call to DMA
void drawFullScreenImageDMA(const u16 *image) {
    DMA[3].src = image;
    DMA[3].dst = videoBuffer;
    DMA[3].cnt = 240 * 160 | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT | DMA_ON;
}

//Draws an image with DMA
void drawImageDMA(int x, int y, int width, int height, const u16 *image) {
    for (int i = 0; i < height; i++) {
        DMA[3].src = image + (i * width);
        DMA[3].dst = videoBuffer + ((x + i) * WIDTH) + y;
        DMA[3].cnt = width | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT | DMA_ON;
    }
}

//Draw the background where the player used to be
//This is done to prevent tearing
void drawPartialBackground(int x, int y, int width, int height, const u16 *image) {
    for (int i = 0; i < height; i++) {
        DMA[3].src = image + (i * WIDTH) + (x * WIDTH) + y;
        DMA[3].dst = videoBuffer + (i * WIDTH) + (x * WIDTH) + y;
        DMA[3].cnt = width | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT | DMA_ON;
    }
}

void fillScreenDMA(volatile u16 color) {
    DMA[3].src = &color;
    DMA[3].dst = videoBuffer;
    DMA[3].cnt = 240 * 160 | DMA_SOURCE_FIXED | DMA_DESTINATION_INCREMENT | DMA_ON;
}

void drawChar(int col, int row, char ch, u16 color) {
    for(int r = 0; r<8; r++) {
        for(int c=0; c<6; c++) {
            if(fontdata_6x8[OFFSET(r, c, 6) + ch*48]) {
                setPixel(col+c, row+r, color);
            }
        }
    }
}

void drawString(int col, int row, char *str, u16 color) {
    while(*str) {
        drawChar(col, row, *str++, color);
        col += 6;
    }
}

void drawCenteredString(int x, int y, int width, int height, char *str, u16 color) {
    u32 len = 0;
    char *strCpy = str;
    while (*strCpy) {
        len++;
        strCpy++;
    }

    u32 strWidth = 6 * len;
    u32 strHeight = 8;

    int col = x + ((width - strWidth) >> 1);
    int row = y + ((height - strHeight) >> 1);
    drawString(col, row, str, color);
}
