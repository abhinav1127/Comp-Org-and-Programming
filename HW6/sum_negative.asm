;;====================================
;; CS 2110 - Fall 2018
;; Homework 6
;;====================================
;; Name: Abhinav Tirath
;;====================================

.orig x3000

AND R0, R0, 0 ;; Array Address
AND R1, R1, 0 ;; counter
AND R2, R2, 0 ;; sum
AND R3, R3, 0 ;; -ARRAY_LEN
AND R4, R4, 0 ;; curr
AND R5, R5, 0 ;; checker

LD R0, ARRAY_ADDR

LD R3, ARRAY_LEN
NOT R3, R3
ADD R3, R3, 1

LOOP LD R0, ARRAY_ADDR
    ADD R0, R0, R1
    LDR R4, R0, 0
    BRZP END
        ADD R2, R2, R4

    END ADD R1, R1, 1
    ADD R5, R3, R1
    BRN LOOP

ST R2, ANSWER

HALT

ARRAY_ADDR .fill x4000
ARRAY_LEN  .fill 10

ANSWER     .blkw 1

.end

.orig x4000
  .fill 7
  .fill -18
  .fill 0
  .fill 5
  .fill -9
  .fill 25
  .fill 1
  .fill -2
  .fill 10
  .fill -6
.end
