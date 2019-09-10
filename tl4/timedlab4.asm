
;;====================================================
;; CS 2110 - Fall 2018
;; Timed Lab 4
;; converge.asm
;;====================================================
;; Name: Abhinav Tirath
;;====================================================

.orig x3000

;; Don't try to run this code directly, since it only contains
;; subroutines that need to be invoked using the LC-3 calling
;; convention. Use Debug > Setup Test or Simulate Subroutine
;; Call in complx instead.
;;
;; Do not remove this line or you will break...
;; 'Simulate Subroutine Call'

halt

converge

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

LDR R0, R5, 4 ; stores the parameter, n
AND R3, R3, 0;
ADD R3, R3, 2 ;stores 2 in R3
LD R4, DIV_ADDR ; stores address of divide subroutine

ADD R1, R0, -1; n - 1 to check if

BRZ RETURN0

    ADD R6, R6, -2
    STR R0, R6, 0 ; storing n as first parameter for divide
    STR R3, R6, 1 ; storing 2 as second parameter
    JSRR R4 ; jump to divide subroutine

    LDR R1, R6, 0 ; R1 has return of divide
    ADD R6, R6, 2 ; makes R6 go back to the top of the previous stack from the return value

    AND R2, R0, 1 ; n % 2

    BRZ RETURN1

    BR RETURN2


RETURN0
    AND R2, R2, 0
    STR R2, R5, 3
    BR TEARDOWN

RETURN1
    ADD R6, R6, -1
    STR R1, R6, 0 ; storing return of divide as first parameter for recursive
    JSR converge ; jump to divide subroutine

    LDR R2, R6, 0 ; R1 has return of converge
    ADD R6, R6, 2 ; makes R6 go back to the top of the previous stack from the return value

    ADD R2, R2, 1
    STR R2, R5, 3
    BR TEARDOWN

RETURN2
    ADD R6, R6, -1
    ADD R3, R0, R0 ; R3 = R0 * 2
    ADD R0, R3, R0 ; R0 = 3 * R0
    ADD R0, R0, 1 ; R1 = 3 * R0 + 1
    STR R0, R6, 0 ; storing return of divide as first parameter for recursive
    JSR converge ; jump to divide subroutine

    LDR R2, R6, 0 ; R1 has return of converge
    ADD R6, R6, 2 ; makes R6 go back to the top of the previous stack from the return value

    ADD R2, R2, 1
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

STACK    .fill xF000
DIV_ADDR .fill x6000 ;; Call the divide subroutine at
                     ;; this address!

.end

;;====================================================
;;   divide(n, d): Takes a numerator (n) and
;;                 denominator (d), returning n / d.
;;====================================================
.orig x6000
divide  ;; DO NOT call JSR with this label! Use DIV_ADDR instead!
  .fill x1DBD
  .fill x7F81
  .fill x7B80
  .fill x1BBF
  .fill x1DBB
  .fill x7140
  .fill x737F
  .fill x757E
  .fill x777D
  .fill x797C
  .fill x6144
  .fill x6345
  .fill x54A0
  .fill x1620
  .fill x987F
  .fill x1921
  .fill x1903
  .fill x0805
  .fill x14A1
  .fill x987F
  .fill x1921
  .fill x16C4
  .fill x0FF7
  .fill x7543
  .fill x6140
  .fill x637F
  .fill x657E
  .fill x677D
  .fill x697C
  .fill x1D61
  .fill x6B80
  .fill x1DA1
  .fill x6F80
  .fill x1DA1
  .fill xC1C0
.end
