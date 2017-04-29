; A3B_Array.asm

; Author:       Mark Kaganovsky
; Course:       CST8216 Fall 2015
; S/N:          040-789-903
; Date:         25 Nov 2015

; Purpose       To copy an array backwards into memory, summing up every value
;               as it iterates through the array, and storing it after the copy
;               array.

; Program Constants
STACK              equ     $2000

; Program data
                   org     $1000
Source_Array
                   db      $06, $55, $2C, $7A, $07
Destination_Array  ds      Destination_Array-Source_Array ; auto calculate
                                                          ; Array Size
Additions          ds.w    1                              ; store 16 bit
                                                          ; additions here
; Code starts
                   org    $2000
                   lds    #STACK
                   
                   ldx    #Destination_Array-1 ; x -> last entry in source array
                   ldy    #Destination_Array   ; y -> first entry in dest. array
                   
                   ldd    #0
                   std    Additions            ; Zero out Additions memory
                   
Start
                   ldab   1,x-                 ; Load byte from source array
                   stab   1,y+                 ; Store byte in destinaion array
                   clra                        ; Clear A so msb of d is zero
                   pshd
                   ldd    Additions            ; Get the previous sum
                   addd   0,sp                 ; Add previous sum to current byte
                   std    Additions
                   ins
                   ins                         ; 'pop' the stack
                   cpx    #Source_Array-1
                   bne    Start

                   swi
                   end
                   