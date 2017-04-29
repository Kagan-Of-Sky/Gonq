; Counter_00_99_BCD_HEX_Display.asm

#include C:\68hcs12\registers.inc

; Author:      Mark Kaganovsky
; Course:      CST8216 Fall 2015
; S/N:         040-789-903
; Date:        4 December 2015
;
; Purpose      To continually count from 0 to 99 in BCD, displaying the number
;              on the LED hex display on the Dragon-12-Plus HCS12 Trainer Board.




; Program Constants
STACK         equ     $2000

; Port P (PPT) Display Selection Values
DIGIT3_PP0    equ  %1110      ; MSB of the displayed BCD digits (left-most dislay)
DIGIT2_PP1    equ  %1101      ; LSB of the displayed BCD digits (2nd display from left)

; Delay Subroutine Values
DELAY_VALUE   equ     250     ; Delay value (base 10) 0 - 255 ms
                              ; 125 = 1/8 second, 250 = 1/4 second



; Code starts.
        org     $2000               ; program code
Start   lds     #STACK              ; stack location

; Configure the Ports
        jsr     Config_HEX_Displays

Reset   ldaa    #0                  ; Start up the counter at 0

Again
        psha

        jsr     Extract_MSB         ; Flash the lower nibble (tens digit)
        ldab    #DIGIT3_PP0
        jsr     Hex_Display
        ldaa    #DELAY_VALUE
        jsr     Delay_ms

        ldaa    0,sp                ; Flash the upper nibble (ones digit)
        jsr     Extract_LSB
        ldab    #DIGIT2_PP1
        jsr     Hex_Display
        ldaa    #DELAY_VALUE
        jsr     Delay_ms


        pula                        ; Check if counter needs resetting
        cmpa    #%10011001          ; If A is equal to 99 in BCD, reset counter.
        beq     Reset
        
        adda    #1                  ; Otherwise add 1 to A and loop again.
        daa
        bra     Again

; Subroutines used by program (DO NOT CHANGE ANY OF THE FOLLOWING LINES OF CODE)
#include C:\68HCS12\Lib\Config_HEX_Displays.asm
#include C:\68HCS12\Lib\Delay_ms.asm
#include Extract_MSB.asm
#include Extract_LSB.asm
#include Hex_Display.asm

        end