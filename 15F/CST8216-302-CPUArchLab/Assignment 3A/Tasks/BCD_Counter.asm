; BCD_Counter.asm
#include C:\68HCS12\registers.inc

; Author:       Mark Kaganovsky
; Course:       CST8216 Fall 2015
; S/N:          040-789-903
; Date:         7 Nov 2015
; Purpose       To display the values 00 to 99 in BCD (Binary Coded Decimal).




; Program Constants
STACK           equ     $2000
DTIME           equ     250                 ; 250 milliseconds delay time.

; Program data
                org     $1000
SaveA           ds      1                   ; Space to store accumulator a (destroyed by the delay subroutine)




; Code starts
                org     STACK
                lds     #STACK

; Configure the Ports
                jsr     Config_SWs_and_LEDs

RestartCounter  ldaa    #0                  ; Start the counter off at 0

Count           staa    portb               ; Flash the LEDs
                staa    SaveA               ; Store a (it is destroyed by the delay subroutine)

		ldaa    #DTIME
                jsr     Delay_ms
                ldaa    #DTIME
                jsr     Delay_ms
                ldaa    #DTIME
                jsr     Delay_ms
                ldaa    #DTIME
                jsr     Delay_ms
                
		ldaa    SaveA
                cmpa    #%10011001          ; Is a 99 in BCD?
                beq     RestartCounter      ; Restart the counter if a is 99
                adda    #01                 ; Otherwise increment the counter.
                daa                         ; Adjust it to BCD
                bra     Count               ; Display the value

; Library Files
#include C:\68HCS12\Lib\Config_SWs_and_LEDs.asm
#include C:\68HCS12\Lib\Delay_ms.asm

                end