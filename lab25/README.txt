 _ _ _       _    _ _   ____  ____
( | ) | __ _| |__( | ) |___ \| ___|
 V V| |/ _` | '_ \V V    __) |___ \
    | | (_| | |_) |     / __/ ___) |
    |_|\__,_|_.__/     |_____|____/

    LAB 25 - Practice Lab for TL6
=======================================

NOTE: This is practice for TL6, you do not need to turn it in.

Instructions
------------

1. Go into lab25.c and fill out the function reverse_short_array(). This
   function takes an array of shorts (arr_in) and copies its elements to
   arr_out *in reverse* via DMA.

   You MUST use a single DMA call.

2. To test your code, run:

       make emu

   Output should look like:

       Original Array:
       [9, 6, 0, 2, 4]

       Reversed Array:
       [4, 2, 0, 6, 9]

HINT #1: Recall that by default, DMA copies 1 short at a time, so the N
         (number of transfers) in the cnt register is in units of shorts.

HINT #2: Think about the DMA control signals. We've put all of the DMA
         control signals we use in this class below to help out:

         DMA_DESTINATION_INCREMENT
         DMA_DESTINATION_DECREMENT
         DMA_DESTINATION_FIXED

         DMA_SOURCE_INCREMENT
         DMA_SOURCE_DECREMENT
         DMA_SOURCE_FIXED

         DMA_NOW

         DMA_ON
