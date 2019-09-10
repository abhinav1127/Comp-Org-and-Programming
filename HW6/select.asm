;;====================================
;; CS 2110 - Fall 2018
;; Homework 6
;;====================================
;; Name: Abhinav Tirath
;;====================================

.orig x3000

AND R0, R0, 0 ;; Array Address
AND R1, R1, 0 ;; counteri
AND R2, R2, 0 ;; counterj
AND R3, R3, 0 ;; -ARRAY_LEN
AND R4, R4, 0 ;; -minvalue
AND R5, R5, 0 ;; checker
AND R6, R6, 0 ;; currj
AND R7, R7, 0 ;; min_idx

LD R0, ARRAY_ADDR ; load array address

LD R3, ARRAY_LEN
NOT R3, R3
ADD R3, R3, 1 ; get the negative of the array length

LOOPI LD R0, ARRAY_ADDR ; for i = 0 to ARRAY_LEN - 1:
    ADD R0, R0, R1
    LDR R4, R0, 0
    NOT R4, R4
    ADD R4, R4, 1 ; get negative min value, negative current i value

    AND R7, R7, 0
    ADD R7, R1, 0 ; get index of minvalue

    ADD R2, R1, 1 ; j = i + 1
    LOOPJ LD R0, ARRAY_ADDR ; for j = i+1 to ARRAY_LEN - 1:
        ADD R0, R0, R2
        LDR R6, R0, 0 ; get current value into R6

        ADD R5, R6, R4 ; add positive curr value and negative min value
        BRZP ENDJ ; if it's negative,
            AND R4, R4, 0
            ADD R4, R6, 0 ; get curr value in to R4
            NOT R4, R4
            ADD R4, R4, 1 ; put negative curr value into R4

            AND R7, R7, 0
            ADD R7, R2, 0 ; get index of minvalue

        ENDJ ADD R2, R2, 1 ; increment j
        ADD R5, R3, R2 ; add negative loop length and positive index
        BRN LOOPJ ; if negative, jump back to LOOPJ

    ENDI

    NOT R4, R4
    ADD R4, R4, 1 ; make negative value min positive again!

    LD R0, ARRAY_ADDR ; getting the value of the current i, so we can swap
    ADD R0, R0, R1
    LDR R5, R0, 0 ; get current i value into R5

    STR R4, R0, 0 ; store current min value into i index

    LD R0, ARRAY_ADDR
    ADD R0, R0, R7 ; getting the position of the min value

    STR R5, R0, 0 ; store current min value into i index

    ADD R1, R1, 1 ; increment i
    ADD R5, R3, R1 ; add negative loop length and positive index
    BRN LOOPI ; if negative, jump back to LOOPI

                                ;for i = 0 to ARRAY_LEN - 1:
                                ;  min_idx = i
                                ;# Iterate through every position in the array
                                ;# Find the element that will move to position i
                                ;# Everything before index i is sorted, so we are
                                ;# looking for the minimum value after index i
                                ; for j = i + 1 to ARRAY_LEN:
                                ;    if ARRAY_ADDR[j] < ARRAY_ADDR[min_idx]:
                                ;min_idx = j
                                ;                                     # Swap the value that belongs here with the current
                                ;                                     # value; these might be the same value!
                                ;                                     # (and index i might be equal to index min_idx)
                                ;swap(ARRAY_ADDR[i], ARRAY_ADDR[min_idx])

HALT

ARRAY_ADDR .fill x4000
ARRAY_LEN  .fill 10

.end

.orig x4000
  .fill 7
  .fill 18
  .fill 0
  .fill 5
  .fill 9
  .fill 25
  .fill 1
  .fill 2
  .fill 10
  .fill 6
.end
