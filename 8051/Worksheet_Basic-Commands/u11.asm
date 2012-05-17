;U11: cyclic output of BCD 0..99 on port
POUTPUT EQU P3;

RESET:
mov R0,#00H
CLR C; clear carry, else this would confuse DA after RST

ITER:
mov A,R0; transfer counter to ACC for processing
DA A; to-BCD conversion
mov POUTPUT,A; output
inc R0; count up
JC RESET; reset if num is not representable via BCD (is > 99)
SJMP ITER; else iterate