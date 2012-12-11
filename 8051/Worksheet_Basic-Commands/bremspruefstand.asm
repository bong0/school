;Bremspruefstand
;

INP EQU 50H
mov A,#50D

LOOP:

CJNE A, INP, NE_50
SJMP BTW_50_70; is between 50 and 70 inclusive

NE_50:
JNC SM_50

CMP_EQU_70:
mov A,#70D
CJNE A,INP,CMP_70
SJMP BTW_50_70; is between 50 and 70 inclusive
CMP_70: ; is bigger or smaller than 50?
JNC BTW_50_70; 70 >= INP

SJMP GT_70

BTW_50_70:	; 50<=Input<=70
  mov P3,#40H; set yellow LED
  SJMP LOOP
GT_70:		; Input>70
  ANL P3,#80H; set green LED
  SJMP LOOP
SM_50:		; Input<50
  ANL P3,#20H; set red LED
SJMP LOOP