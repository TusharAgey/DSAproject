#include<stdio.h>
#include "Techna.h"
void printmenu() {
	printf("T> How can I serve you sir?\nT> select the service that you want from me:\n");
	printf("T> 1)Manage the contacts\n");
	printf("T> 1)Manage the money\n");
	/*printf("T> 1)Manage the contacts\n");
	printf("T> 1)Manage the contacts\n");
	printf("T> 1)Manage the contacts\n");
	*/
	
}
int main() {
	user u;
	printf("\n \t\tTECHNA\n");
	printf("\n *****************************************\n");
	printf("T> Welcome to the world of TECHNA\n");
	if(isFirstTime(&u)) {
		printf("T> Wow, first time visit, let me introduce myself, I am a chatbot, having name\n\t\t\t TECHNA.\n And I came in exsistance on 13th September 2015\n"); 
		printf("T> Please tell me about you! So that I can understnd you clearly\n");
		writeinfo(&u);
		printf("T> Let me tell you that on next login, you will be asked for login, and its just\n ur name and the passcode will be the value equal to current day + 9;\nConfused? no pooblem, just type help, you will get set of commands with their\n use!\n");
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
	//printmenu();
	startRoutine(u																);//Biggest real time working function.
	closeMe(u);
	return 0;
}
