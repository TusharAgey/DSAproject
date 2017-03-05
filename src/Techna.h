
/*****************************************************************************
 *   This file is part of TECHNA.
 *
 *  TECHNA is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Foobar is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with TECHNA.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define NAMESIZE 1024
#define MORNING 123
#define AFTERNOON 456
#define EVENING 789
typedef struct user {
	char name[NAMESIZE];
	char gender[10];
	char DOB[11];
	char occupation[NAMESIZE];
	
}user;
int isFirstTime(user *u);	//returns 1 if the user has not visited the interface yet, else returns 0.
int greet(user u, int need);	//greets the user with morning, afternoon or evening if need = 1, else just returns the time slice.
void writeinfo(user *u);	//writes the user info onto the file
void grabData(user *u);		//gets the user info from already saved file to the program for manipulation
int login();			//makes the login logic.returns 1 for successfull login.
void closeME(user u);		//ends the program & greets accordingly
void startRoutine(user u);	//most imp function
char *cmdLowerCase(char *s);	//converts the string s to lower case
void contactManaging(user u);	//manages contact
int chkBirthday(user u,int day,int month); //returns 1 is its birthday, else 0
void moneyManaging(user u);	//Manages your money
void writeDiary(user u);	//routine for diary management
char *trim(char *cmd);		//removes the excess spaces from start and end of the string

