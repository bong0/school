;U5 set, reset and invert bits 1,5,7 of ACC
MASK_BITS EQU 0A2H

PINPUT EQU P2
POUTPUT EQU P3

JMP INVBITS
;part a) - set bits
SETBITS:
mov A,PINPUT
ORL A,#MASK_BITS
mov POUTPUT,A
SJMP END

;part b) - reset bits
RSTBITS:
mov A,#MASK_BITS
CPL A
anl A,PINPUT
mov POUTPUT,A
SJMP END

;part c) - invert bits
INVBITS:
mov A,PINPUT
xrl A,#MASK_BITS
mov POUTPUT,A
SJMP END

END:
