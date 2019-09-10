;;====================================
;; CS 2110 - Fall 2018
;; Homework 6
;;====================================
;; Name: Abhinav Tirath
;;====================================

.orig x3000

AND R0, R0, 0
AND R1, R1, 0
AND R2, R2, 0

LD R0, A
LD R1, B

NOT R0, R0
NOT R1, R1

AND R2, R1, R0
NOT R2, R2

ST R2, ANSWER

HALT

A      .fill x1010
B      .fill x0404

ANSWER .blkw 1

.end
