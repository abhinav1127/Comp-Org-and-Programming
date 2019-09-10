;;====================================
;; CS 2110 - Fall 2018
;; Homework 7
;; string_ops.asm
;;====================================
;; Name: Abhinav Tirath
;;====================================

; Little reminder from your pals: don't run this directly by pressing
; ``Run'' in complx, since (look below) there's nothing put at address
; x3000. Instead, load it and use ``Debug'' -> ``Simulate Subroutine
; Call'' and choose the ``strlen'' label.

.orig x3000

halt


strlen
    ADD R6, R6, -3   ;initialize space for everything
    STR R7, R6, 1    ;store RA
    STR R5, R6, 0    ;store old FP
    ADD R6, R6, -4   ;initialize space for registers
    ADD R5, R6, 3    ;place new FP
    STR R0, R6, 3    ;store R0 on the stack
    STR R1, R6, 2    ;store R1 on the stack
    STR R2, R6, 1    ;store R2 on the stack
    STR R3, R6, 0    ;store R3 on the stack

    LDR R0, R5, 4    ;load the address of string into R0
    AND R1, R1, 0    ;reset R1 to 0, it'll be the length

LOOPSTRING
    ADD R2, R0, R1   ;R2 -> address of current character
    LDR R2, R2, 0    ;R2 -> value of current character

    BRZ ENDSTRING    ;if value of character is 0, reached the end

    ADD R1, R1, 1    ;increment string length
    BR LOOPSTRING

ENDSTRING
    STR R1, R5, 3    ;store strlen at the return value spot


TEARDOWN
    LDR R3, R6, 0   ;reload R3
    LDR R2, R6, 1   ;reload R2
    LDR R1, R6, 2   ;reload R1
    LDR R0, R6, 3   ;reload R0
    ADD R6, R6, 4   ;add the stack pointer
    LDR R5, R6, 0   ;reload old FP
    LDR R7, R6, 1   ;reload return address
    ADD R6, R6, 2   ;put the stack pointer at the rv
    RET



count_occurrence

    ADD R6, R6, -3   ;initialize space for everything
    STR R7, R6, 1    ;store RA
    STR R5, R6, 0    ;store old FP
    ADD R6, R6, -4   ;initialize space for registers
    ADD R5, R6, 3    ;place new FP
    STR R0, R6, 3    ;store R0 on the stack
    STR R1, R6, 2    ;store R1 on the stack
    STR R2, R6, 1    ;store R2 on the stack
    STR R3, R6, 0    ;store R3 on the stack

    LDR R0, R5, 4    ;load the address of string into R0
    AND R1, R1, 0    ;reset R1 to 0, it'll be the length
    AND R2, R2, 0    ;R2 holds the count
    LDR R3, R5, 5    ;load the character we are checking against

    NOT R3, R3
    ADD R3, R3, 1 ;get negative value of character we are checking against

    ADD R6, R6, -1 ; decrement R6 to store string here for strlen
    STR R0, R6, 0 ; storing string
    JSR strlen ; strlen(s)

    LDR R1, R6, 0 ; R1 has string length now
    ADD R6, R6, 2 ; makes R6 go back to the top of the previous stack from the return value

    ADD R1, R1, 0 ; check if 0 or negative
    BRNZ END

    LOOP LDR R0, R5, 4  ;load the address of string into R0
        ADD R0, R0, R1
        LDR R0, R0, -1  ;R0 now holds the current character

        ADD R0, R0, R3 ;compare the characters
        BRNP INCREMENT
            ADD R2, R2, 1
        INCREMENT
        ADD R1, R1, -1
        BRNZ END
        BR LOOP
    END
    STR R2, R5, 3    ;store count_occurrence at the return value spot

;TEARDOWN
    LDR R3, R6, 0   ;reload R3
    LDR R2, R6, 1   ;reload R2
    LDR R1, R6, 2   ;reload R1
    LDR R0, R6, 3   ;reload R0
    ADD R6, R6, 4   ;add the stack pointer
    LDR R5, R6, 0   ;reload old FP
    LDR R7, R6, 1   ;reload return address
    ADD R6, R6, 2   ;put the stack pointer at the rv
    RET

                            ;int count_occurrence(String s, char c) {
                            ;    int count = 0;
                            ;    for (int i = 0; i < strlen(s); i++) {
                            ;        if (s.charAt(i) == c) {
                            ;            count++;
                            ;        }
                            ;
                            ;    }
                            ;    return count;
                            ;}



; Needed by Simulate Subroutine Call in complx
STACK .fill xF000
.end

; You should not have to LD from any label, take the
; address off the stack instead :)
