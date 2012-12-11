;P5 EQU P3
;P4 EQU P2

;bei low-pegel aktiv - prellen
S1 EQU P2.0 ; Aufzug an UNTEN
S2 EQU P2.1 ; select SW UNTEN -> via 100nF C entprellt
S3 EQU P2.2 ; Aufzug an MITTE
S4 EQU P2.3 ; select SW MITTE -> via 100nF C entprellt
S5 EQU P2.4 ; Aufzug an OBEN
S6 EQU P2.5 ; select SW OBEN -> via 100nF C entprellt

;Statusindikatorlampen
H1 EQU P3.0
H2 EQU P3.1
H3 EQU P3.2

ACALL UNTEN
LOOP:

JNB S2, PREPARE_UNTEN
JNB S4, PREPARE_MITTE
JNB S6, PREPARE_OBEN
SJMP LOOP; wait for job

PREPARE_OBEN:
SETB H3
ACALL OBEN
SJMP LOOP

PREPARE_MITTE:
SETB H2
ACALL MITTE
SJMP LOOP

PREPARE_UNTEN:
SETB H1
ACALL UNTEN
SJMP LOOP

;request processing
UNTEN:
  JNB S1, UN_DESTRUCT; we're at our dest
  ACALL DOWN; else drive down
  SJMP UNTEN
  UN_DESTRUCT:; turn off status indicator
    CLR H1
    RET

OBEN:
  JNB S3, OB_DESTRUCT; we're at our dest
  ACALL UP; else drive up
  SJMP OBEN
  OB_DESTRUCT:; turn off status indicator
    CLR H3
    RET

MITTE:
  JNB S1, CALL_UP
  JNB S3, CALL_DOWN
  CHK_IN_MIDDLE:
  JNB S2,UN_DESTRUCT; we're at our dest
  SJMP CHK_IN_MIDDLE
  
  MI_DESTRUCT:; turn off status indicator
    CLR H2
    RET
    
CALL_UP:
  ACALL UP
  SJMP CHK_IN_MIDDLE
CALL_DOWN:
  ACALL DOWN
  SJMP CHK_IN_MIDDLE
  
;Motor control
UP:
  CLR P3.6
  SETB P3.7
  RET
DOWN:
  CLR P3.7
  SETB P3.6
  RET
HALT:
  ANL P3,#03FH ; clear up and down bits
  RET