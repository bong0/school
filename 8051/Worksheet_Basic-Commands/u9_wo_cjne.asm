;U9: determine size of num on port 2 and react
; without using CJNE

PINPUT EQU P2
POUTPUT EQU P3

mov A,#42 ; our counter
mov R0,PINPUT
mov POUTPUT, #00H ; default: num is not greater than 42

ITER:
mov R1,A; save ACC
SUBB A,R0; subtract ACC from input 
JNZ DECR; jump if subtr does not equal 0; INPUT != counter => continue testing
SJMP END; else contents of A and R0 are equal => number is <= 42
DECR:
mov A,R1; restore ACC
DJNZ ACC,ITER; the counter has not reached zero, increment 
SJMP ISG; reached zero => we didn't find the num => it's > 42!

ISG:; being here indicates R0 <= start val of A
SETB POUTPUT.1; flag R0 <= 42

END: