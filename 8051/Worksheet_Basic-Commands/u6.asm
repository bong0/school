;U6 determine subnet start Adr's last octet
IPADR_OCT4 EQU 4403H; mem adr of last octet of IPAdr 
SUB_MASK EQU 224; 4th octet of 255.255.255.242

ORG 4400H
IPADR: DB 192,168,20,34
NMASK: DB 255,255,255,224

ORG 00H
START:
mov DPTR, #IPADR
MOV A,#3
movc A,@A+DPTR
cpl A
mov B,A

mov DPTR,#IP; load to-mask part of IPAdr
mov A,#3
movc A,@A+DPTR; fetch byte from extram
anl A,B; mask IPAdr w/ subnet mask

mov P3, A; output last byte of IP on port 3

END