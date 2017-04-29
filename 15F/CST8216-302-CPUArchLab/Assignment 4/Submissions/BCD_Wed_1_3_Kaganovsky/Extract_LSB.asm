; Extract_LSB.asm

; Author:            Mark Kaganovsky
; Student Number:    040-789-903
; Date:              4 December 2015
;
; Purpose:           To extract the least significant nibble of accumulator A.
;
; Example:           If A contained %1011 1001 before calling this subrouting,
;                    then it will contain %0000 1001 after calling.
;
; Preconditions:     Accumulator A contains the value which you want to extract
;                    the least significant nibble for.
;
; Postcondition:     A destroyed, the most significant nibble (the left 4 bits)
;                    are set to 0, the least significant nibble (the right 4 bits)
;                    preserve their value.
;

MASK     equ     %00001111

Extract_LSB
         anda    #MASK         ; Mask off the most significant nibble.
         rts

;- ------------------------------------
;     End Extract_LSB.asm             -
;--------------------------------------