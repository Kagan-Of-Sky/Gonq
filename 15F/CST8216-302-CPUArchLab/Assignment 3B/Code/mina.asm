; Program data
                   org     $1000
Array              db      $FF, $FE

; Code starts
                   org     $2000
                   ldx     #Array
                   ldaa    1,x+
                   mina    1,x+
                   
                   blt     A_LESS
                   beq     A_EQUAL
                   bgt     A_GREATER

A_GREATER          ldaa    #1
                   bra     END_
                   
A_EQUAL            ldaa    #0
                   bra     END_
                   
A_LESS             ldaa    #2
                   bra     END_
                   
END_
                   swi
                   end