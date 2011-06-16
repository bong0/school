/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- 
 * findword.c
 * Copyright (C) Julian Kessel 2011 <julian@juliankessel.de>
 * 
 * snake-anj is free software copyrighted by Julian Kessel.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name ``Julian Kessel'' nor the name of any other
 *    contributor may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 * 
 * snake-anj IS PROVIDED BY Julian Kessel ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL Julian Kessel OR ANY OTHER CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <stdio.h>
#include <string.h>
struct Position{int zeile; int spalte;};

struct Position SearchWord(FILE * fptr, char *word, int zeile);

int main(const int argc, const char* argv[]){
	char word[300];
	char fn[128];
	FILE *fp, *found;
	struct Position pos = {1,0};

	printf("Dateiname: ");
	scanf("%s", fn);
	if(!(fp=fopen(fn, "r"))){ printf("[-] Konnte Datei nicht öffnen\n"); return 1; }

	printf("Suchwort: ");
	scanf("%s", word);
	do{
		pos = SearchWord(fp, word, pos.zeile);
		if(pos.spalte){
		  found=fopen("found.txt", "w");
		  fprintf(found, "Position: Zeile:%d | Spalte:%d\n", pos.zeile, pos.spalte);
		  printf("Position: Zeile:%d | Spalte:%d\n", pos.zeile, pos.spalte);
		}
		(pos.zeile)++;
	} while(!feof(fp));

	if(ftell(found)) printf("[+] >= ein Auftreten des Worts wurde gefunden, alle Ergebnisse liegen in found.txt\n");
	else printf("[-] Es wurde nichts gefunden\n");
	fclose(found);
	fclose(fp);
	return 0; 
}

struct Position SearchWord(FILE * fptr, char *word, int zeile){
	struct Position pos;
	pos.zeile=zeile; pos.spalte=0;
	char txtbuf[301];
	char *wptr=NULL;

	if(!fgets(txtbuf, 301, fptr)) return pos; //read chunk

	if((wptr=strstr(txtbuf, word))){
		pos.spalte=(unsigned int)(wptr-txtbuf)+1; //calculate relative position of char start@1
		return pos;
	}

	//we didn't find the word, invalidate data
	pos.spalte=0;
	return pos;
}