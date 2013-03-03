; Landesabitur 2011 Vorschlag A
; Heizungssteuerung Heißgetränkeautomat
; Autor: Julian Kessel 2013

PA EQU P1 ; Ausgabeport
PE EQU P0 ; Eingabeport

ORG 0H
LJMP 40H
ORG 40H
MOV PA,#00h
mov PE,#00h

START:
	mov A,PE
	CJNE A, #092d, NE_92
	SJMP START
	NE_92:
		JC LT_92
		CJNE a,#095d, NE_95
		SJMP START; eqal > do nothing
		NE_95:
			JC START; A<95
			CLR PA.0; A> 95 -> hz aus
			sjmp SLEEP
	LT_92:
		setb PA.0
		SJMP SLEEP

SLEEP: ; approx. 5s
mov R0,#0ffh
LO:
	mov R1,#0ffh
	LI1:
		mov R2,#02h
		LI2:
		DJNZ R2,LI2
	DJNZ R1,LI1
DJNZ R0,LO
LJMP START
