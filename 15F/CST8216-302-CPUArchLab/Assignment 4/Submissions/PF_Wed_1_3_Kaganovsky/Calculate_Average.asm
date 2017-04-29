; Calculate_Average.asm
;
; Author:          Mark Kaganovsky
; Student Number:  040-789-903
; Date:            4 December 2015
;

; Purpose:         The purpose of the Calculat_Average_Subroutine is to
;                  calculate the average of ANY number of values, noting that
;                  the average is always out of 50%

; Precondition:    Y points to first value
;                  B contains # values to average
;
;                  Average always out of 50%
;
; Postcondition:   Accumulator A - Destroyed
;                  Accumulator B - Destroyed
;                  Accumulator X - Destroyed
;                  No other accumulators affected.
;
;                  The division that takes place is: (sum of elements) / DIVISOR
;                  Accumulator D - Contains remainder of the division.
;                  Accumulator X - Containts the result of the division.

DIVISOR equ     $05

Calculate_Average
        ldx     #DIVISOR
        
        pshy                 ; Save the value of y
        aby                  ; This loop starts at the end of the array
        dey                  ; and works its way to the beginning.

        clra
        clrb

Next
        cpy     0,sp         ; Have we reached Start of Array minus 1?
        blo     Divide       ; Go and divide if we reached the start.
        
        pshd                 ; Save the value of D

        ldab    1,y-         ; Retrieve the value.
        clra
        
        addd    0,sp
        ins                  ; Clear the stack
        ins
        
        bra     Next         ; Add the next value

Divide
        idiv
        puly                 ; Get back the original value of Y

        rts