;U2: calculate crosstotal of 2 BCD-coded nums

;mask input in 2 4bit segments
HB_MASK EQU 0F0H
LB_MASK EQU 00FH

; mask => separate lower 4bit
mov A, P2 
ANL A, #LB_MASK
mov R0, A; Result => R0

; mask => separate upper 4bit
mov A, P2
ANL A, #HB_MASK
SWAP A
mov R1, A; Result => R1

mov A,R0 ; load lower
add A,R1 ; add lower to upper
DA A; correct num to valid BCD

mov P3,A; output result
