;;====================================
;; CS 2110 - Fall 2018
;; Homework 6
;;====================================
;; Name: Abhinav Tirath
;;====================================

.orig x3000

AND R0, R0, 0 ;; String 1 Address
AND R1, R1, 0 ;; String 2 Address
AND R2, R2, 0 ;; curr ASCII value of Str 1
AND R3, R3, 0 ;; curr ASCII value of Str 2
AND R4, R4, 0 ;; index
AND R5, R5, 0 ;; answer
AND R6, R6, 0 ;; evaluation

LD R0, STR_ADDR_1 ; Load Address 1
LD R1, STR_ADDR_2 ; Load Address 2

LOOP
    LD R0, STR_ADDR_1 ; Load Address 1
    ADD R0, R0, R4
    LDR R2, R0, 0 ; load value of Str 1
    BRP NOTZ1
        LD R1, STR_ADDR_2 ; Load Address 2
        ADD R1, R1, R4
        LDR R3, R1, 0 ; load value of Str 2
        BRNZ Z12
            ADD R5, R5, -1
            BR END
        Z12
            AND R5, R5, 0
            BR END
    NOTZ1

    LD R1, STR_ADDR_2 ; Load Address 2
    ADD R1, R1, R4
    LDR R3, R1, 0 ; load value of Str 2

    BRP NOTZ2
        ADD R5, R5, 1
        BR END

    NOTZ2

    NOT R3, R3
    ADD R3, R3, 1 ; get negative of Str 2

    ADD R4, R4, 1 ; increment counter
    ADD R6, R2, R3 ; check if positive or negative
    BRZ LOOP

    BRP Positive
        ADD R5, R5, -1
        BR END

    Positive ADD R5, R5, 1
        BR END

END ST R5, ANSWER

HALT

STR_ADDR_1 .fill x4000
STR_ADDR_2 .fill x4050

ANSWER     .blkw 1

.end

.orig x4000
  .stringz "Message from Mars"
.end

.orig x4050
  .stringz ""
.end
