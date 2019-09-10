.orig x8000
nice
; setup
add r6, r6, -1 ; allocate space for RV
add r6, r6, -1 ; allocate space for RA
str r7, r6, 0  ; backup R7 onto stack as RA
add r6, r6, -1 ; allocate space for OFP
str r5, r6, 0  ; backup R5 onto stack as OFP
add r5, r6, -1 ; set frame pointer

add r6, r6, -5 ; allocate space for saved registers
str r0, r5, 0  ; backup r0 to stack
str r1, r5, -1 ; backup r1 to stack
str r2, r5, -2 ; backup r2 to stack
str r3, r5, -3 ; backup r3 to stack
str r4, r5, -4 ; backup r4 to stack

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;








; YOUR CODE HERE. Put the result in R0!
;                 (Don't touch R5, R6, or R7, though, since this is
;                  inside a subroutine.)
;
; Reminder: here is the pseudocode:
;
;     sum = 0
;
;     for i = 0 to 69 inclusive:
;         sum += i
;
;     return sum


AND R0, R0, 0 ; counter
AND R2, R2, 0 ; sum

LD R1, HOLDER69 ; stores 69
NOT R1, R1
ADD R1, R1, 1 ; -69

LOOP ADD R2, R2, R0
    ADD R0, R0, 1
    ADD R3, R1, R0 ; checks if counter > 69
    BRNZ LOOP

ADD R0, R2, 0








;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


return
str r0, r5, 3 ; make r0 the return value

; reload registers
ldr r0, r5, 0  ; reload r0 from stack
ldr r1, r5, -1 ; reload r1 from stack
ldr r2, r5, -2 ; reload r2 from stack
ldr r3, r5, -3 ; reload r3 from stack
ldr r4, r5, -4 ; reload r4 from stack

; teardown
add r6, r5, 1 ; pop all locals off the stack
ldr r5, r6, 0 ; reload ofp
add r6, r6, 1 ; pop ofp
ldr r7, r6, 0 ; reload return address
add r6, r6, 1 ; pop ra
; r6 now points to return value
ret

HALT

HOLDER69 .fill #69

.end
