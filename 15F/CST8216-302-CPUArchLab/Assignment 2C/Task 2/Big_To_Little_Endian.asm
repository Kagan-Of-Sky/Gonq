; Big_To_Little_Endian.asm

; Author:       Mark Kaganovsky
; Course:       CST8216 Fall 2015
; S/N:          040-789-903
; Date:         3 Nov 2015

; Purpose       To convert a big endian array of three 2 byte words into an
;               array of little endian words.

; Data
                   org      $1000
Source_Array       dw       $10fe, $2888, $aa55
                   org      $1020
Destination_Array  ds.w     3
            
; Program Code
            org      $2000
            lds      $2000
            
            ldd      Source_Array          ; Read in a two byte word
            stab     Destination_Array     ; Write low order byte first
            staa     Destination_Array+1   ; Write the high order byte next
            
            ldd      Source_Array+2
            stab     Destination_Array+2
            staa     Destination_Array+3
            
            ldd      Source_Array+4
            stab     Destination_Array+4
            staa     Destination_Array+5
            
            swi
            end