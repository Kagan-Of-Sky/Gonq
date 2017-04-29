; First.asm
;
; Author:              Mark Kaganovsky
; Student Number:      040-789-903
; Date:                17 Oct 15
;
; Purpose:             Add the following values: $25 + $37 - $1
;

        org        $1000       ; Set the current location to the starts of RAM.
p:      db         $25         ; First addend is at location p.
q:      db         $37         ; Second addend is at location q.
r:      ds         1           ; Sum will be stored at location r.
        org        $2000       ; Set the current location to the start in ROM.
        ldaa       p           ; Load value at p into accumulator a.
        adda       q           ; Add value at q into accumulator a.
        deca                   ; Decrement accumulator a.
        staa       r           ; Store a in memory location r.
        end