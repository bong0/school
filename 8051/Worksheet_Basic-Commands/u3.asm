;U3: a cheap chaser light

mov A, #080H; leftmost bit (light) is set
mov A, #01111111b
mov P3, A; output on port3

START:
  RR A; shift set bit one bit right
  mov P3, A; push result on port
SJMP START
