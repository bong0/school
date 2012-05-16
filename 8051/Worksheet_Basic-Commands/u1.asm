;U1: 16Bit-Addition
; SRC1
mov R3, #00H  ;0 in l. Byte
mov R4, #0FFH ;255 in r. Byte

; SRC2
mov R5, #00H ; 0 in l. Byte
mov R6, #0FH ; 1 in r. Byte

mov A,R4; load LSByte of SRC1 into ACC
ADD A,R6; add w/ LSByte of SRC2
mov R4,A; save

mov A,R5; load MSByte of SRC2
ADDC A,R3; add considering Carry
mov R3,A; write result to reg3

END