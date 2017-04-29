; Pass_Fail.asm
; Pass_Fail Subroutine
; Is it a Pass or Fail ?

; Author:         Mark Kaganovsky
; Student Number: 040-789-903
; Date:           4 December 2015

; Purpose:        The purpose of the Pass_Fail_Subroutine is to
;                 determine if the supplied integer is a Pass or a Fail, given that
;                 - a Pass is a mark between 50% and 100%
;                 - a Fail is a mark between 0% and 49%

; Precondition:   X register contains value to check for passing or failing.
;
; Postcondition:  A destroyed, now contains either a 0 or a 1.
;                 0 indicates that the mark was a fail.
;                 1 indicates that the mark was a pass.


; Constants
PASS_MIN  equ      5          ; The minimum value in x to pass a course.
                              ; Example: If the student got 42/50, then the value
                              ;          in x would be (42/5) = 8 (a pass).

; Code
Pass_Fail
          cpx      #PASS_MIN
          bhs      Pass
          
Fail                          ; Student failed, set A to 0.
          ldaa     #0
          bra      Return
          
Pass                          ; Student passed, set A to 1.
          ldaa     #1

Return
          rts