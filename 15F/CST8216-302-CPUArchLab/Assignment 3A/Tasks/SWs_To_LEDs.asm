; SWs_To_LEDs.asm

#include C:\68HCS12\registers.inc

; Author:         Mark Kaganovsky
; Course:         CST8216 Processor Architecture
; S/N:            040-789-903
; Date:           6 Nov 2015

; Purpose:        To display the values of the switches on Port H on the LEDs
;                 on Port B on Dragon 12+ Trainer.

          org     $2000
          lds     #$2000
          clrb
          jsr     Config_SWs_and_LEDs
Get_SW    ldaa    PTH                  ; Get data from switches
          staa    PORTB                ; And send it to LEDs
          bra     Get_SW
          
#include C:\68HCS12\Lib\Config_SWs_and_LEDs.asm

          end