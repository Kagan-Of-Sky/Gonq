; Math_Operations.asm
;
; Author:           D. Haley, Mark Kaganovsky
; Student Number:   040-789-903
; Date:             20 Oct 2015
;
; Purpose:          To Gain Experience with Assembly Language instructions.




; Program Constants.
STACK     equ     $2000




; Program data.
          org     $1000       ; Data starts at $1000.
MyArray   db      $0C, $81    ; Define 2 bytes
Result    ds      2           ; Two bytes of storage.




; Program instructions.
          org     $2000       ; Program Code starts at $2000.
Start     lds     #STACK      ; Setup the stack.

          ldaa    #$25        ; Load accumulator a with the value 0x25 (37).
          ldab    #25         ; Load accumulator b with the value 25.
          adda    MyArray     ; Add accumulator a with   ?
          staa    Result      ; Store accumulator a into
          stab    Result+1    ; Store accumulator b into
          ldaa    Result+1    ; Load accumulator a with
          ldab    Result      ; Load accumulator b with
          incb                ; Increment accumulator b.
          ldaa    #%10101010  ; Load accumulator a with the decimal value 170.
          std     Result      ; Store the contents of accumulator d into memory.
          swi                 ; (S)oft(W)are (I)nterrupt.
          end