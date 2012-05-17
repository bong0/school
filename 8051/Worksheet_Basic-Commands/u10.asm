;U10: cyclic write 0xFF..0x11 to port
POUTPUT EQU P3

RESET:
mov A, #0FFH

BEGIN:
mov POUTPUT,A
DEC A
CJNE A,#10H,BEGIN ;jump if counter is above 0x11
SJMP RESET; else reset to 0xFF

