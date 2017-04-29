; Flash_Even_Odd.asm
#include C:\68HCS12\registers.inc

; Author:       Mark Kaganovsky
; Course:       CST8216 Fall 2015
; S/N:          040-789-903
; Date:         6 Nov 2015
; Purpose       To flash the LEDs on the Dragon board in an even, odd, off pattern.

; Program Constants
STACK       equ     $2000
PB_EVEN     equ     %01010101           ; b6, b4, b2, b0 on - Remainder of the bits off.
PB_ODD      equ     %10101010           ; b7, b5, b3, b1 on - Remainder of the bits off.
PB_OFF      equ     %00000000           ; All LEDs off.
DTIME       equ     250                 ; 250 milliseconds delay time.




; Code starts
            org     $2000               ; program code
Start       lds     #STACK              ; stack location

; Configure the Ports
            jsr     Config_SWs_and_LEDs

; Continually flash the LEDs in an even, odd, off pattern.
LoopStart   ldaa    #PB_EVEN
            staa    portb               ; Flash even leds only.
            ldaa    #DTIME              ; Delay 250ms
            jsr     Delay_ms            ; Call delay routine
            
            ldaa    #PB_ODD
            staa    portb               ; Flash odd leds only.
            ldaa    #DTIME
            jsr     Delay_ms
            
            ldaa    #PB_OFF
            staa    portb               ; Turn all LEDs off.
            ldaa    #DTIME
            jsr     Delay_ms
            
            bra     LoopStart           ; endless loop

; Library Files
#include C:\68HCS12\Lib\Config_SWs_and_LEDs.asm
#include C:\68HCS12\Lib\Delay_ms.asm

            end