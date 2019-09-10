
;;====================================================
;; CS 2110 - Fall 2018
;; Timed Lab 3
;; timedlab3.asm
;;====================================================
;; Name: Abhinav Tirath
;;====================================================

.orig x3000

AND R0, R0, 0 ;; Array Address
AND R1, R1, 0 ;; -ASCII0
AND R2, R2, 0 ;; -ASCII9
AND R3, R3, 0 ;; ASCIISPACE
AND R4, R4, 0 ;; current
AND R5, R5, 0 ;; evaluation

LD R0, STR_ADDR

LD R1, ASCII0
NOT R1, R1
ADD R1, R1, 1 ;-ASCII0

LD R2, ASCII9
NOT R2, R2
ADD R2, R2, 1 ;-ASCII9

LD R3, ASCIISPACE

LDR R4, R0, 0 ;load current at R4
BRZ END

LOOP ADD R5, R1, R4 ;current - ASCII0, if positive or zero, could be number
    BRN MAKESPACE

    ADD R5, R2, R4 ;current - ASCII9, if negative or zero, is number
    BRP MAKESPACE

    BR NOSPACE

    MAKESPACE STR R3, R0, 0
    NOSPACE
    ADD R0, R0, 1 ; increment address
    LDR R4, R0, 0 ;load current at R4
    BRP LOOP
END

HALT

STR_ADDR .fill x5000

ASCII0  .fill 48
ASCII9 .fill 57
ASCIISPACE .fill 32

.end

.orig x5000
  .stringz "asdfasdfasdf"

.end
