; Pass_Fail_Calc.asm

#include c:\68hcs12\registers.inc

; Author(s) and Student Number(s):
; Date:
; Purpose:      Calculate if a student has passed both the Practical and Theory
;               portions of the course. Display a 'P' if both portions passed;
;               otherwise, display an 'F' Display the values for 1 second each
;               (e.g. 4 delay cycles of 250 ms each) Then, blank the display for
;               the same amount of time and continue on with the values. At the
;               end, blank the display
;
;               Note that there is only ONE 'P' or 'F' displayed per student
;
;
; Program Constants
DELAY_VALUE     equ     250

; data section
                org     $1000
; Read in Data File
Start_Course_Data
; remove the comment symbol (;) to unmask your lab section's include statement
; #include "Tue_10-12_Marks.txt"
; #include "Wed_1-3_Mark.txt"
; #include "Wed_3-5_Marks.txt"
; #include "Fri_2-4_Marks.txt"
End_Course_Data

; code section
        org     $2000           ; RAM address for Code
        lds     #$2000          ; Stack



Done    bra     Done                ; infinite loop keeps last value on 7-seg display

; ***** DO NOT CHANGE ANY CODE BELOW HERE *****;
#include Calculate_Average.asm
#include Pass_Fail.asm
#include C:\68HCS12\Lib\Config_Hex_Displays.asm
#include PF_HEX_Display.asm
#include C:\68HCS12\Lib\Delay_ms.asm
        end