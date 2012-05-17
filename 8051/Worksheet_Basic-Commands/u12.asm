;U12 knight-rider on port
POUTPUT EQU P3

mov A, #080H; leftmost bit (light) is set


START:
	mov POUTPUT, A; push result on port
	
	CJNE A, #80H,IFRIGHTMOST; check if we have reached the left border; else check if we're right
	SJMP CLRC; unset auxcarry if true => we need to go right
	
	IFRIGHTMOST:
	CJNE A, #01H,COMP; true if we are not at one of the two borders
	SJMP SETC; set carry if we need to change direction to left

	COMP:; we don't need to set anything => just continue shifting
	JB AC,LSHIFT
	JNB AC,RSHIFT
	
	CLRC:
	  CLR AC; need to use AC because CY is touched by CJNE
	  SJMP RSHIFT
	SETC:
	  SETB AC
	  SJMP LSHIFT; for readability
	
	
	RSHIFT:
	  RR A;
	  SJMP START
	LSHIFT:
	  RL A;
	  SJMP START