; START: Wait loop, time: 1 s
; Clock: 12000.0 kHz (12 / MC)
; Used registers: R0, R1, R2, R3
	MOV	R3, #003h ; 3
	MOV	R2, #0D2h ; 210
	MOV	R1, #024h ; 36
	MOV	R0, #014h ; 20
	NOP ; 1cycle
	DJNZ	R0, $ 	; 3 cycle * 20 loops => 60µs		;1
	DJNZ	R1, $-5	; 5 cycles * 36 loops => 180µs		;2
	DJNZ	R2, $-9	; 7 cycles * 210 *  loops => 1470µs	;3
	DJNZ	R3, $-13 ; 9 cycles * 3 * loops => 27µs		;4
	MOV	R0, #059h ; 89D 
	DJNZ	R0, $; 2 cycles * 89 loops => 178µs
	NOP
; Rest: 0
; END: Wait loop

; Z: 9 60µs 
; Z:10 180µs
; Z: 8 1µs
; Z: 9 2µs (keine Aktion)
; Z: 10 2µs (keine Aktion)
; Z: 11 1470µs
; Z: 8 1µs
; Z: 9 2µs (keine Aktion)
; Z: 10 2µs (keine Aktion)
; Z: 11 2µs (keine Aktion)
; Z: 12	6µs
; Z: 8 1µs
; Z: 9 2µs (keine Aktion)
; Z: 10 2µs (keine Aktion)
; Z: 11 2µs (keine Aktion)
; Z: 12 2µs (keine Aktion)
;