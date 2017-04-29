; Walk_A_Bit.asm
#include C:\68HCS12\registers.inc

; Author:       Mark Kaganovsky
; Course:       CST8216 Fall 2015
; S/N:          040-789-903
; Date:         6 Nov 2015
; Purpose       To flash the leds in the following order:
;               . . . . . . . .
;               1 . . . 1 . . .
;               . 1 . . . 1 . .
;               . . 1 . . . 1 .
;               . . . 1 . . . 1
;               . . . . . . . .
;               . . . 1 . . . 1
;               . . 1 . . . 1 .
;               . 1 . . . 1 . .
;               1 . . . 1 . . .
;               Where a dot(.) means the LED is off and a '1' means it is on.

; Program Constants
STACK           equ     $2000
DTIME           equ     180                 ; 180 milliseconds delay time.

; Program data
                org     $1000
Flash_Array     db      %00000000           ; Array containing the data needed to
                db      %10001000           ; produce the pattern.
                db      %01000100
                db      %00100010
                db      %00010001
                db      %00000000
                db      %00010001
                db      %00100010
                db      %01000100
                db      %10001000
End_Array

; Code starts
                org     $2000
                lds     #STACK

; Configure the Ports
                jsr     Config_SWs_and_LEDs

; Main program loop
Reset_IRX       ldx     #Flash_Array
Flash_Start     ldaa    1,X+
                staa    portb               ; Flash the LEDs
                ldaa    #DTIME              ; Delay.
                jsr     Delay_ms            ; Call delay routine
                cpx     #End_Array
                blo     Flash_Start         ; Flash the next entry in the array.
                bra     Reset_IRX           ; Otherwise resest index register X to the start of Flash_Array

; Library Files
#include C:\68HCS12\Lib\Config_SWs_and_LEDs.asm
#include C:\68HCS12\Lib\Delay_ms.asm

                end