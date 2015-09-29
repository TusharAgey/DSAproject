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
	char DOB[10];
	char occupation[NAMESIZE];
	
}user;
int isFirstTime(user *u);//returns 1 if the user has not visited the interface yet, else returns 0.
int greet(user u, int need);//greets the user with morning, afternoon or evening if need = 1, else just returns the time slice.
void writeinfo(user *u);//writes the user info onto the file
void grabData(user *u);//gets the user info from already saved file to the program for manipulation
int login();//makes the login logic.returns 1 for successfull login.
void closeME(user u);//ends the program & greets accordingly
void startRoutine(user u);//most imp function
char *cmdLowerCase(char *s);
void contactManaging(user u);
int chkBirthday(user u,int day,int month); //returns 1 is its birthday, else 0
