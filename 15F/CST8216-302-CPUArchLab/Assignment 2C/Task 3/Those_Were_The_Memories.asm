; Those_Were_The_Memories.asm

Value3   equ     128

         org     $1000
Value1   db      $AA
Value2   dw      9876

         org     $1020
Result1  ds      1
Result2  ds      2
Result3  ds      1

         org     $2000
         lds     $2000
         ldaa    Value1
         staa    Result3
         ldab    #Value3
         stab    Result1
         ldab    $1002
         ldaa    $1001
         std     Result2
         
         swi
         end