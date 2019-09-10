;;====================================
;; CS 2110 - Fall 2018
;; Homework 6
;;====================================
;; Name: Abhinav Tirath
;;====================================

.orig x3000

AND R0, R0, 0 ;; current node address (next)
AND R1, R1, 0 ;; current node address (value)
AND R2, R2, 0 ;; curr max
AND R3, R3, 0 ;; curr min
AND R4, R4, 0 ;; evaluation
AND R5, R5, 0 ;; curr/ -curr
AND R6, R6, 0 ;; idk

LD R2, MIN_INT ; fill max with min int
LD R3, MAX_INT ; fill min with max int

LD R0, HEAD_ADDR
BRNZ END

LDR R2, R0, 1 ; getting first value
LDR R3, R0, 1 ; getting first value

LDR R0, R0, 0
BRNZ END

LOOP
    ADD R1, R0, 1
    LDR R5, R1, 0 ; getting curr in R5
    NOT R6, R5
    ADD R6, R6, 1 ; getting -curr in R6

    ADD R4, R6, R2 ; is curr new max?
    BRZP NEWMAX ; if negative,
        AND R2, R2, 0 ; making R2 0
        ADD R2, R5, 0 ; putting curr into R2
    NEWMAX

    ADD R4, R6, R3 ; is curr new min?
    BRNZ NEWMIN ; if negative,
    AND R3, R3, 0 ; making R3 0
    ADD R3, R5, 0 ; putting curr into R3

    NEWMIN

    LDR R0, R0, 0
    BRNZ END
    BR LOOP

END
ST R2, ANSWER_MAX
ST R3, ANSWER_MIN

HALT

HEAD_ADDR  .fill x4000

MAX_INT    .fill x7FFF
MIN_INT    .fill x8000

ANSWER_MAX .blkw 1
ANSWER_MIN .blkw 1

.end

.orig x4000
  .fill x4002         ;; Node 1
  .fill 4
  .fill x4004         ;; Node 2
  .fill 5
  .fill x4006         ;; Node 3
  .fill 25
  .fill x4008         ;; Node 4
  .fill 1
  .fill x0000         ;; Node 5
  .fill 10
.end
