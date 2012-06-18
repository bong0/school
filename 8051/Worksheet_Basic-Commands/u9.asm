;U9: determine size of num on port 2 and react
PINPUT EQU P2
POUTPUT EQU P3
R0_MAN EQU 00H; workaround: we may not use R0, only dadr in CJNE

mov A,PINPUT
mov POUTPUT, #00H ; default: num is not greater than 42

CJNE A,#42,COMPARE; A equals 42 => compare CY

COMPARE:
JNC SETFLAG; A > 42
JC END; else number is < 42

SETFLAG:
SETB POUTPUT.1; flag R0 <= 42

END: