;U4: determine if input is even
mov P2, #42 ; even test value
mov P3, #00H; default: uneven

mov C, P2.0 ; LSB of p2 IN C
JNC EVEN; if LSB is 0 => input is even
SJMP END; else => leave the output untouched

EVEN:
mov P3, #0FFH; set output

END:

