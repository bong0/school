;U9: determine size of num and react
PINPUT EQU P2
POUTPUT EQU P3
R0_MAN EQU 00H

mov A,#42 ; our counter
mov R0,PINPUT

ITER:
CJNE A,R0_MAN,DECR; if A!=PINPUT => decrement
SJMP ISNG; else contents of A and R0 are equal
DECR:
DJNZ ACC,ITER; the counter has not reached zero, increment 
SJMP END; reached zero => bail out

ISNG:; being here indicates R0 <= start val of A
SETB POUTPUT.1; flag R0 <= 42

END:
