#include <stdlib.h>
#include <stdio.h>
#include "gba.h"
#include "lab25.h"

// DO NOT MODIFY THIS FILE!
// See lab25.c for the lab

static char *stringify_short_array(const short *, int);

int main(void) {
    REG_DISPCNT = MODE3 | BG2_ENABLE;

    const short arr[] = {9, 6, 0, 2, 4};
    const int arr_len = sizeof arr / sizeof arr[0];

    const int padding = 5;
    short *arr_reversed = calloc(arr_len + 2 * padding, sizeof(short));
    reverse_short_array(arr, arr_reversed + padding, arr_len);

    drawString(70, 20, "original array:", WHITE);
    drawString(70, 35, stringify_short_array(arr, arr_len), WHITE);
    drawString(70, 55, "reversed array:", WHITE);
    drawString(70, 70, stringify_short_array(arr_reversed + padding, arr_len), WHITE);

    int outOfBounds = 0;
    for (int i = 0; !outOfBounds && i < padding; i++)
        outOfBounds = outOfBounds || arr_reversed[i];

    for (int i = arr_len + padding; !outOfBounds && i < arr_len + 2 * padding; i++)
        outOfBounds = outOfBounds || arr_reversed[i];

    if (outOfBounds) {
        drawCenteredString(0, 100, 240, 20, "WARNING! YOU WROTE OUTSIDE THE ARRAY!", PINK);
        drawCenteredString(0, 120, 240, 20, "Check your DMA address calculations!", PINK);
    }

    // Display both
    while (1);
    return 0;
}

static char *stringify_short_array(const short *arr, int len) {
    //  Assume single-digit characters
    char *buf = malloc(len * 3);
    char *p = buf;

    *(p++) = '[';

    for (int i = 0; i < len; i++)
        p += sprintf(p, "%d, ", arr[i]);

    p[-2] = ']';
    p[-1] = '\0';

    return buf;
}
