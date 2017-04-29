; Extract_MSB.asm

; Author:            Mark Kaganovsky
; Student Number:    040-789-903
; Date:              4 December 2015
;
; Purpose:           To extract the least significant nibble of accumulator A.
;
; Example:           If A contained %1011 1001 before calling this subrouting,
;                    then it will contain %0000 1011 after calling.
;
; Preconditions:     Accumulator A contains the value which you want to extract
;                    the most significat nibble for.
;
; Postcondition:     A destroyed, now contains the most significant nibble
;                    (first 4 bits) shifted over into the least significat bits
;                    position.
;

Extract_MSB
         lsra
         lsra
         lsra
         lsra
         
         rts

;- ------------------------------------
;     End Extract_MSB.asm             -
;--------------------------------------