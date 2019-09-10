#include "gba.h"

// TODO: Using DMA, reverse the array elements in arr_in and place them
//       in arr_out.
//       You MUST use a single DMA call.
//       Memory is already allocated for arr_out --- all you need to do
//       is copy elements, except in reverse, with DMA.
// HINT: Think about the control signals for DMA
void reverse_short_array(const short *arr_in, short *arr_out, int len) {
    DMA[3].src = arr_in;
    DMA[3].dst = arr_out + len - 1;
    DMA[3].cnt = len | DMA_SOURCE_INCREMENT | DMA_DESTINATION_DECREMENT | DMA_ON;
}
