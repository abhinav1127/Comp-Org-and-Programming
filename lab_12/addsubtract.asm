;;===============================
;; Name: Abhinav Tirath
;;===============================

.orig x3000

AND R0, R0, 0 ; sum
AND R1, R1, 0 ; array index
AND R2, R2, 0 ; add or subtract
AND R3, R3, 0 ; curr value
AND R4, R4, 0 ; address of array


FOR1 ADD R1, R1, #1
    BRNZ ENDFOR

    LD R4, ARRAY
    ADD R4, R4, 1
    LDR R3, R4, R1

    ADD R2, R2, 0

    BRZ IF0
    BRNP IF1

    IF0
        ADD R0, R0, R3
        BRNZP ENDIF
    IF1
        NOT R3, R3
        ADD R3, R3, 1
        ADD R0, R0, R3
        BRNZP ENDIF
    ENDIF

    NOT R2, R2
    AND R1, R1, 1
    BRNZP FOR1

ENDFOR

ST R1, RESULT

                    ;addsubtract(int arr[], int length) {
                    ;	int currentState = 0; // 0 for add, 1 for subtract
                    ;	int result = 0;
                    ;	for (int i = 0; i < length; i++) {
                    ;		int element = arr[i];
                    ;		if (currentState) {
                    ;			result = result - element;
                    ;			currentState = 0;
                    ;		} else {
                    ;			result = result + element;
                    ;			currentState = 1;
                    ;		}
                    ;	}
                    ;	return result;
                    ;}


HALT


ARRAY .fill x6000
LENGTH .fill 7
RESULT .fill 0
.end




.orig x6000
.fill 3 ; +
.fill 5 ; -
.fill 1 ; +
.fill 4 ; -
.fill 6 ; +
.fill 8 ; -
.fill 12; +
.end
