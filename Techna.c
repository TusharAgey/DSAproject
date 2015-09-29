#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<fcntl.h>
#include<time.h>
#include "Techna.h"
#include "list.h"
static int hellcnt = 0;
int isFirstTime(user *u) {
	FILE *fp;
	if(!(fp = fopen("DataBase/uinfo.dat", "r"))) {
		creat("DataBase/uinfo.dat", 0666);
		fp = fopen("DataBase/uinfo.dat", "r");
	}
	if(fread(u, sizeof(*u), 1, fp)) {
		fclose(fp);
		return 0;
	}
	else
		return 1;
}
int chkBirthday(user u,int day,int month) {
	char cday[3];
	char cmonth[3];
	char tmp;
	int chk = 0;
	sprintf(cday, "%d", day);
	sprintf(cmonth, "%d", month);
	if(strlen(cday) == 1) {
		tmp = cday[0];
		cday[0] = '0';
		cday[1] = tmp;
	}
	if(strlen(cmonth) == 1) {
		tmp = cmonth[0];
		cmonth[0] = '0';
		cmonth[1] = tmp;
	}

	if((cday[0] == u.DOB[0]) && (cday[1] == u.DOB[1]) && (cmonth[0] == u.DOB[3]) && (cmonth[1] == u.DOB[4]) ) {
		chk = 1;	
	}
	return chk;
}
int greet(user u, int need) {
	int tmval;
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
//	printf("%d", timeinfo->tm_hour);
	if(timeinfo->tm_hour >= 00 && timeinfo->tm_hour < 12)
		tmval = MORNING;
	else if(timeinfo->tm_hour >= 12 && timeinfo->tm_hour < 17)
		tmval = AFTERNOON;
	else
		tmval = EVENING;
	int day = timeinfo->tm_mday;
	int month = timeinfo->tm_mon + 1;
	int x = chkBirthday(u, day, month);
	if(x == 1)
		printf("T> Happy Birthday, enjoy the day to its full length!\n");
	if(need != 1)
		goto retvals;
	switch(tmval) {
		case MORNING:
			if(strcmp(u.gender, "male") == 0)
				printf("T> Good morning Mr. %s\n", u.name);
			else
				printf("T> Good morning Miss %s\n", u.name);

		break;
		case AFTERNOON:
			if(strcmp(u.gender, "male") == 0)
				printf("T> Good afternoon Mr. %s\n", u.name);
			else
				printf("T> Good afternoon Miss %s\n", u.name);
		break;
		case EVENING:
			if(strcmp(u.gender, "male") == 0)
				printf("T> Good evening Mr. %s\n", u.name);
			else
				printf("T> Good evening Miss %s\n", u.name);
		break;
	}
retvals:
	return(tmval);

}
void writeinfo(user *u) {
	char tmp1[11], tmp2[11];
	printf("T> What is ur name?\nU> ");
	scanf("%s", u->name);
	printf("T> Nice Name, and Gender?\nU> ");
	scanf("%s", u->gender);
	if(strcmp(u->gender, "male") == 0) {
		printf("T> Ohh hello Mr. %s and Date of Birth please?in format DD:MM:YYYY\nU> ", u->name);	
	}
	else {
		printf("T> Ohh hello Miss %s and Date of Birth please?in format DD:MM:YYYY\nU> ", u->name);
	}
	scanf("%s", tmp1);
	tmp2[0] = tmp1[0];
	tmp2[1] = tmp1[1];
	tmp2[2] = '/';
	tmp2[3] = tmp1[3];
	tmp2[4] = tmp1[4];
	tmp2[5] = '/';
	tmp2[6] = tmp1[6];
	tmp2[7] = tmp1[7];
	tmp2[8] = tmp1[8];
	tmp2[9] = tmp1[9];
	tmp2[10] = '\0';
	strcpy(u->DOB, tmp2);
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	int day = timeinfo->tm_mday;
	int month = timeinfo->tm_mon + 1;
	int x = chkBirthday(*u, day, month);
	
	if(x == 1)
		printf("T> Wowee, its your birthday today!! Happy Birthday!!\nT> And What is your occupation? \nU> ");	
	else
 		printf("T> Hmm, I'll wish u!!, and occupation?\nU> ");
	scanf("%s", u->occupation);
	FILE *fp = fopen("DataBase/uinfo.dat", "w");
	fwrite(u, sizeof(*u), 1, fp);	
	printf("T> Ohh %s ha, okay. \n", u->occupation);

}
void grabData(user *u) {
	FILE *fp = fopen("DataBase/uinfo.dat", "r");
	fread(u, sizeof(*u), 1, fp);
}
int login(user u) {
	char *name;
	int secret, code;
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	secret = timeinfo->tm_mday + 9;


	name=(char *)malloc(sizeof(char)*30);
	printf("T> Who are you?\nU> ");
	scanf("%s", name);
	if(strcmp(u.name, name) == 0) {
		printf("T> Enter the secrete code:\nU> ");
		scanf("%d", &code);
		if(code == secret) {
			return 1;
		}
		else
			return 0;
	}
	return 0;
}
void closeMe(user u) {
	int tm = greet(u, 0);
	switch(tm) {
		case MORNING:
			if(strcmp(u.gender, "male") == 0)
				printf("T> Have a beautiful day Mr. %s\n", u.name);
			else
				printf("T> Have a beautiful day Miss %s\n", u.name);

		break;
		case AFTERNOON:
			if(strcmp(u.gender, "male") == 0)
				printf("T> Glad to help you Mr. %s\n", u.name);
			else
				printf("T> Glad to help you Miss %s\n", u.name);
		break;
		case EVENING:
			if(strcmp(u.gender, "male") == 0)
				printf("T> Good night Mr. %s\n", u.name);
			else
				printf("T> Good night Miss %s\n", u.name);
		break;
	}
}
void toomuchwait() {
}
char *analyse(char *cmd, user u) {
	if(strcmp(cmd, "exit") == 0)
		return cmd;
	else if(strcmp(cmd, "manage my contacts") == 0) {
		printf("T> I am opening a portal for contact management...\n");
		contactManaging(u); 
	}
	else if(strcmp(cmd, "help") == 0) {
		FILE *helpfp = fopen("DataBase/help.txt", "r");
		char readfp;
		printf("Here's the help:-\n\n");
		while(fread(&readfp, sizeof(readfp), 1, helpfp)) {
				printf("%c", readfp);
		}
		printf("\n\n");
	}
	return cmd;
}
void contactManaging(user u) {
	list l;
	node *n;
	FILE *fp;
	if(!(fp = fopen("DataBase/contact.dat", "r"))) {
		creat("DataBase/contact.dat", 0666);
		fp = fopen("DataBase/contact.dat", "r");
	}
	init(&l);
	
	data *data1 = (data *)malloc(sizeof(data));
	static int pos = 0;
	while(fread(data1, sizeof(*data1), 1, fp)) {
		n = NULL;
		n = (node *)malloc(sizeof(node));
		initNode(n);
		insert(&l, n, data1, pos);
		pos++;
		data1 = NULL;
		data1 = (data *)malloc(sizeof(data));
	}
	fclose(fp);
	char name[100], phone[100], email[100];
	int choise = 0;
	printf("T> Hey there, I am here to manage ur contacts\n");
	
	while(choise != 5) {
		printf("T> choose one of the following:\n  1)Add contact\n  2)view contact\n  3)remove contact\n  4)Update existing contact\n  5)exit\nU> ");
		scanf("%d", &choise);
		switch(choise) {
			case 1:
				//printf("T> Enter the name, phone number and email\nU> ");
				//scanf("%s%s%s", data1->name, data1->phone, data1->email);
				printf("T> Enter name:\nU> ");
				scanf("%s", data1->name);
				printf("T> Enter Phone Number:\nU> ");
				scanf("%s", data1->phone);
				printf("T> Enter Email:\nU> ");
				scanf("%s", data1->email);
				
				n = NULL;
				n = (node *)malloc(sizeof(node));
				initNode(n);
				insert(&l, n, data1, pos);
				pos++;
				data1 = NULL;
				data1 = (data *)malloc(sizeof(data));
				printf("T> Record inserted successfully\nU> ");
				break;
			case 2:
				printf("T> Enter the name of person to be searched\nU> ");
				scanf("%s", name);
				//showAll(&l);
				viewContact(name, &l);
				break;
			case 3:
				printf("T> Please dont remove a contact, I know you will need it some time in future, i insist you to keep this contact, please!\nU> ");
				break;	
			case 4:
				printf("T> Enter the phone number of the person whose details are to be updated:\nU> ");
				scanf("%s", phone);
				update(&l, phone);
				break;
			case 5:
				printf("T> Thank you for using my service, glad to help you!\n");		
				storeTotal(&l);
				hellcnt = 0;
				return;
				break;	
			default:
				printf("T> I couldn't understand your request, please recheck\n");
				break;
		}
	}
	hellcnt = 0;
	
}
char *cmdLowerCase(char *s) {
	int i = 0;
	while(s[i] != '\0') {
		switch(s[i]) {
			case 'A':
				s[i] = 'a';
				break;
			case 'B':
				s[i] = 'b';
				break;
			case 'C':
				s[i] = 'c';
				break;
			case 'D':
				s[i] = 'd';
				break;
			case 'E':
				s[i] = 'e';
				break;
			case 'F':
				s[i] = 'f';
				break;
			case 'G':
				s[i] = 'g';
				break;
			case 'H':
				s[i] = 'h';
				break;
			case 'I':
				s[i] = 'i';
				break;
			case 'J':
				s[i] = 'j';
				break;
			case 'K':
				s[i] = 'k';
				break;
			case 'L':
				s[i] = 'l';
				break;
			case 'M':
				s[i] = 'm';
				break;
			case 'N':
				s[i] = 'n';
				break;
			case 'O':
				s[i] = 'o';
				break;
			case 'P':
				s[i] = 'p';
				break;
			case 'Q':
				s[i] = 'q';
				break;
			case 'R':
				s[i] = 'r';
				break;
			case 'S':
				s[i] = 's';
				break;
			case 'T':
				s[i] = 't';
				break;
			case 'U':
				s[i] = 'u';
				break;
			case 'V':
				s[i] = 'v';
				break;
			case 'W':
				s[i] = 'w';
				break;
			case 'X':
				s[i] = 'x';
				break;
			case 'Y':
				s[i] = 'y';
				break;
			case 'Z':
				s[i] = 'z';
				break;
			default:
				break;		
		}
		++i;
	}
	return s;
	
}
void startRoutine(user u) {
	char gender[8], *cmd;
	cmd = (char *) malloc(sizeof(char) * 30);
	int gen;
	strcpy(gender, u.gender);
	if(strcmp(gender, "male") == 0)
		gen = 1;	
	else
		gen = 0;
	
	strcpy(cmd, "start");
	char chval;
	int i;
	
	while(strcmp(cmd, "exit") != 0) {
		i = 0;
		toomuchwait();
		if(strcmp(u.gender, "male") == 0)
			printf("T> Hello Mr. %s, can I help you ?\nU> ", u.name);
		else
			printf("T> Hello miss %s, can I help you ?\nU> ", u.name);
		if(hellcnt == 0) { 	
			chval = getchar();
			++hellcnt;
		}
		while((chval = getchar()) != '\n') {
			cmd[i] = chval;
			i++;
		}
		cmd[i] = '\0';
		cmd = cmdLowerCase(cmd);
		cmd = analyse(cmd, u);
	}
	
}

