
/*****************************************************************************
 * Copyright (C) Tushar Sandeep Agey agey.tushar3@gmail.com
 *
 * This program(TECHNA) is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
 *****************************************************************************/

#include<stdio.h>
#include "Techna.h"
int main() {				//Entry point of TECHNA routine
	user u;
	printf("\n \t\tTECHNA\n");
	printf("\n **********************************************************\n");
	printf("T> Welcome to the world of TECHNA\n");
	if(isFirstTime(&u)) {
		printf("T> Wow, first time visit, let me introduce myself, I am a personal assistant\n   program, with name\n\t\t\t TECHNA\n   I came in exsistance on 13th September 2015.\n"); 
		printf("T> Please tell me about you! So that I can understnd you clearly\n");
		writeinfo(&u);
		printf("T> Let me tell you that on next login, you will be asked for login, and its just\n   ur name and the secrete code will be the value equal to current day + 9;\n   Confused? no problem, just type help, you will get set of commands with their   use!\n");
		printf("T> Hint: Type help\n");
	goto jmp;
	}
	else {
		grabData(&u);
	}
	if(!(login(u))) {
		printf("T> I am going for shopping, I'll be unavailable for say,, hmm,, forever!!!\n");
		return(0);
	}
jmp:	greet(u, 1);
	startRoutine(u);		//Biggest real time working function.
	closeMe(u);
	return 0;
}
