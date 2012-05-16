;U8: cyclic output of 00H..FFH on P3
POUTPUT EQU P3;

mov A,#00H

BEGIN:
inc A
mov POUTPUT,A
SJMP BEGIN