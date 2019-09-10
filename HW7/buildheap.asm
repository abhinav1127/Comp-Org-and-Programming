;;====================================
;; CS 2110 - Fall 2018
;; Homework 7
;; buildheap.asm
;;====================================
;; Name: Abhinav Tirath
;;====================================

; Little reminder from your pals: don't run this directly by pressing
; ``Run'' in complx, since (look below) there's nothing put at address
; x3000. Instead, load it and use ``Debug'' -> ``Simulate Subroutine
; Call'' and choose the ``strlen'' label.

.orig x3000

halt

heapify

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

    LDR R0, R5, 4    ;store array address in R0
    LDR R1, R5, 6    ;store index root in R1

    LDR R4, R5, 6    ;store index of largest in R4

    LDR R3, R5, 5    ;store length of array in R3
    NOT R3, R3
    ADD R3, R3, 1    ;get negative length of array

    ADD R0, R0, R1
    LDR R2, R0, 0   ;store i in R2
    LDR R0, R5, 4    ;store array address in R0

    NOT R2, R2
    ADD R2, R2, 1    ;store -i in R2

    ADD R1, R1, R1   ;i*2
    ADD R1, R1, 1    ;i*2 + 1

    ADD R3, R1, R3
    BRZP INDEXOOBLEFT ;leftChild < n
        ADD R0, R0, R1
        LDR R3, R0, 0   ;store i*2 + 1 in R3
        LDR R0, R5, 4    ;store array address in R0
        ADD R3, R3, R2   ;arr[leftChild] > arr[largest]
        BRNZ INDEXOOBLEFT
            ADD R4, R1, 0    ;store index of largest in R4
            ADD R0, R0, R1
            LDR R2, R0, 0 ;store i*2 + 1 in R2
            LDR R0, R5, 4    ;store array address in R0
            NOT R2, R2
            ADD R2, R2, 1    ;get -(i*2 + 1)

    INDEXOOBLEFT

    LDR R3, R5, 5    ;store length of array in R3
    NOT R3, R3
    ADD R3, R3, 1    ;get negative length of array

    LDR R1, R5, 6    ;store index root in R1
    ADD R1, R1, R1   ;i*2
    ADD R1, R1, 2    ;i*2 + 2

    ADD R3, R1, R3
    BRZP INDEXOOBRIGHT ;rightchild < n
        ADD R0, R0, R1
        LDR R3, R0, 0   ;store i*2 + 1 in R3
        LDR R0, R5, 4    ;store array address in R0
        ADD R3, R3, R2   ;arr[rightchild] > arr[largest]
        BRNZ INDEXOOBRIGHT
            ADD R4, R1, 0    ;store index of largest in R4
            ADD R0, R0, R1
            LDR R2, R0, 0 ;store i*2 + 1 in R2
            LDR R0, R5, 4    ;store array address in R0
            NOT R2, R2
            ADD R2, R2, 1    ;get -(i*2 + 1)

    INDEXOOBRIGHT

    LDR R1, R5, 6    ;store index root in R1
    ADD R0, R0, R1
    LDR R3, R0, 0   ;store i in R3
    LDR R0, R5, 4    ;store array address in R0
    NOT R3, R3
    ADD R3, R3, 1    ;store -i in R3
    NOT R2, R2
    ADD R2, R2, 1    ;make the max positive again

    ADD R3, R2, R3

    BRZ TEARDOWN ; is the largest index i or not?
        ADD R3, R0, R1   ;store address of i in R3
        LDR R1, R3, 0    ;store i in R1
        STR R2, R3, 0    ;store max in i address

        ADD R0, R0, R4   ;R0 is address of max
        STR R1, R0, 0    ;store i in max address


        LDR R0, R5, 4    ;store array address in R0
        LDR R1, R5, 5    ;store length in R1
        ADD R2, R4, 0    ;store max index in R2

        ADD R6, R6, -1
        STR R2, R6, 0 ; storing parameters
        ADD R6, R6, -1
        STR R1, R6, 0 ; storing parameters
        ADD R6, R6, -1
        STR R0, R6, 0 ; storing parameters
        JSR heapify

        ADD R6, R6, 2 ; makes R6 go back to the top of the previous stack from the return value


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


buildheap

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

    LDR R0, R5, 4    ;store array address in R0
    LDR R1, R5, 5    ;store length of array in R1
    LDR R2, R5, 5    ;counter

    LOOP
        ADD R6, R6, -1
        STR R2, R6, 0 ; storing index counter
        ADD R6, R6, -1
        STR R1, R6, 0 ; storing length of array
        ADD R6, R6, -1
        STR R0, R6, 0 ; storing array address
        JSR heapify

        ADD R6, R6, 2 ; makes R6 go back to the top of the previous stack from the return value

        ADD R2, R2, -1
        BRN TEARDOWN

        BR LOOP




; Needed by Simulate Subroutine Call in complx
STACK .fill xF000
.end

; You should not have to LD from any label, take the
; address off the stack instead :)
