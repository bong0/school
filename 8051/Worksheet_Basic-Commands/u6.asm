;U6 determine subnet start Adr's last octet
IPADR_OCT4 EQU 4404H; mem adr of last octet of IPAdr 
SUB_MASK EQU 224; 4th octet of 255.255.255.242

mov DPTR,#IPADR_OCT4; load to-mask part of IPAdr
movx A,@DPTR; fetch byte from extram
anl A,#SUB_MASK; mask IPAdr w/ subnet mask

mov P3, A; output last byte of IP on port 3

END