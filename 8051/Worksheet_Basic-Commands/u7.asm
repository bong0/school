;U7: jumping jack (useless, indeed)
PINPUT EQU P2;
POUTPUT EQU P3;

START:
mov C,PINPUT.1
mov POUTPUT.2,C
SJMP START
