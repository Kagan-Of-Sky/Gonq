; Bubble_Sort.asm

; Author:       Mark Kaganovsky
; Course:       CST8216 Fall 2015
; S/N:          040-789-903
; Date:         25 Nov 2015

; Purpose       To sort a copy of an array in memory using the bubble sort algorithm.
;               Creates a copy of the source array right after the destination array.
;               Sorts the copy array using the bubble sort algorithm.

; Program Constants
STACK              equ     $2000

; Program data
                   org     $1000
Source_Array
#include "Bubble_Sort_Array.txt"                          ; Load the array

Destination_Array
                   ds      Destination_Array-Source_Array ; Storage for copy array
End_Dest_Array

; Code starts
                   org     $2000
                   lds     #STACK
                   
                   ldx     #Source_Array
                   ldy     #Destination_Array

; Make a copy of the source array into the destination array.
Copy_Source_Array  ldaa    1,x+
                   staa    1,y+
                   cpx     #Destination_Array
                   bne     Copy_Source_Array

; Bubble sort the destination array.
                   ldx     #End_Dest_Array

Outer_Loop                                         ; for(x=arrayLength; x>0; x--)
                   dex
                   cpx     #Destination_Array
                   bls     End_Loop
                   pshx
                   
                   ldy     #Destination_Array
Inner_Loop                                         ; for(y=0; y<x-1; y++)
                   ldaa    0,y
                   iny
                   cmpa    0,y
                   bhi     Swap                    ; if array[y-1] > array[y]
                   bra     After_Swap              ; else
                   
Swap                                               ; swap array[y-1] and array[y]
                   ldab    0,y
                   staa    0,y
                   dey
                   stab    0,y
                   iny
                   
After_Swap
                   cpy     0,sp
                   blo     Inner_Loop              ; y < x, continue inner loop
                   ins
                   ins                             ; Clear the stack
                   bra     Outer_Loop              ; y >= x, break out of inner loop
End_Loop

                   end