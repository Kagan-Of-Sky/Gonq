; The_Stack.asm

Stack           equ         $2000
                
                org         $1000
Data            db          $93, $53, $21, $11, $10

                org         $2000
                lds         #Stack
                
                ldx         #Data
                ldaa        0,x
                ldab        1,x+
                psha
                pshb
                pshx
                jsr         Here
                pulx
                puld
                bra         Finish
Here            ldaa        Data+2
                dex
                rts
Finish          swi
                end