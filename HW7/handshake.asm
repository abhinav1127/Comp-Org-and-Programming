;;====================================
;; CS 2110 - Fall 2018
;; Homework 7
;; handshake.asm
;;====================================
;; Name: Abhinav Tirath
;;====================================

; Little reminder from your pals: don't run this directly by pressing
; ``Run'' in complx, since (look below) there's nothing put at address
; x3000. Instead, load it and use ``Debug'' -> ``Simulate Subroutine
; Call'' and choose the ``strlen'' label.

.orig x3000

halt

handshake

    ADD R6, R6, -4 ;place stack pointer to build up first portion of the stack (a)
    STR R7, R6, 2 ;save old return address
    STR R5, R6, 1 ;save old frame pointer
    ADD R5, R6, 0 ;set current frame pointer
    ADD R6, R6, -5 ;place stack pointer to save all of the registers on the stack (b)
    STR R0, R6, 4 ;save R0
    STR R1, R6, 3 ;save R1
    STR R2, R6, 2 ;save R2
    STR R3, R6, 1 ;save R3
    STR R4, R6, 0 ;save R4

    AND R2, R2, 0 ; R2 will hold the answer
    LDR R0, R5, 4 ; stores the parameter, n

    BRNZ BASE
        ADD R3, R0, -1 ; decrements parameter and stores it in R3

        ADD R6, R6, -1
        STR R3, R6, 0 ; storing decremented parameter in R6
        JSR handshake

        LDR R1, R6, 0 ; R1 has string length now
        ADD R6, R6, 2 ; makes R6 go back to the top of the previous stack from the return value

        ADD R2, R1, R3 ; sum the values

        STR R2, R5, 3 ;store the return value!
        BR TEARDOWN

    BASE
        STR R2, R5, 3
        BR TEARDOWN


TEARDOWN
    LDR R4, R5, -5 ;restore R4
    LDR R3, R5, -4 ;restore R3
    LDR R2, R5, -3 ;restore R2
    LDR R1, R5, -2 ;restore R1
    LDR R0, R5, -1 ;restore R0
    ADD R6, R5, 0 ;bring R6 back down to R5
    LDR R5, R6, 1 ;restore old frame pointer
    LDR R7, R6, 2 ;restore return address
    ADD R6, R6, 3 ;have R6 point to the return value
    RET

; Needed by Simulate Subroutine Call in complx
STACK .fill xF000
.end

; You should not have to LD from any label, take the
; address off the stack instead :)
