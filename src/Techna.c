
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
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<fcntl.h>
#include<time.h>
#include "Techna.h"
#include "list.h"
#include "list2.h"
int dash1, dash2;
static int hellcnt = 0;
static char gendr[7];
int isFirstTime(user *u) {
	dash1 = dash2 = 0;
	FILE *fp;
	if(!(fp = fopen("../DataBase/uinfo.dat", "r"))) {
		creat("../DataBase/uinfo.dat", 0666);
		fp = fopen("../DataBase/uinfo.dat", "r");
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
	char tmp1[11], tmp2[11], *gder;
	gder = (char *)malloc(sizeof(char) * 7);
	printf("T> What is ur name?\nU> ");
	scanf("%[^\n]%*c", u->name);
	printf("T> Nice Name, and Gender?\nU> ");
	scanf("%s", gder);
	gder = cmdLowerCase(gder);
	strcpy(u->gender, gder);
	if(strcmp(u->gender, "male") == 0) {
		printf("T> Ohh hello Mr. %s and Date of Birth please?in format DD:MM:YYYY\nU> ", u->name);	
	}
	else {
		printf("T> Ohh hello Miss %s and Date of Birth please?in format DD:MM:YYYY\nU> ", u->name);
	}
escanf:	scanf("%s", tmp1);
	if(strlen(tmp1) != 10) {
		printf("T> Hey, please enter DOB in correct format, coz due to incorrect format, I would be ubale to assist you ~_~\nU> ");
		goto escanf;	
	}
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
	getchar();
	scanf("%[^\n]%*c", u->occupation);
	FILE *fp = fopen("../DataBase/uinfo.dat", "w");
	fwrite(u, sizeof(*u), 1, fp);	
	printf("T> Ohh %s ha, okay. \n", u->occupation);
	fclose(fp);
}
void grabData(user *u) {
	FILE *fp = fopen("../DataBase/uinfo.dat", "r");
	fread(u, sizeof(*u), 1, fp);
	fclose(fp);
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
	scanf("%[^\n]%*c", name);
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
int toInt(char arr[]) {
	int len = strlen(arr);
	int val = 0;
	int i;
	val = arr[0] - '0';
	for(i = 1; i < len; i++) {
		val = (val * 10) + (arr[i] - '0');
	}
	return val;
}
int isNumber(char str[]) {
	int flag = 0;
	int i = 0;
	while(str[i] != '\0') {
		if(str[i] == '0' ||str[i] == '1' ||str[i] == '2' ||str[i] == '3' ||str[i] == '4' ||str[i] == '5' ||str[i] == '6' ||str[i] == '7' ||str[i] == '8' ||str[i] == '9') {
				;	
		}
		else {
			flag = 1;
			break;	
		}
		i++;	
	}
	return flag;
}

void moneyManaging(user u) {
	if(dash1 == 1) {
		printf("T> I am counting your balance, It will take whole day, please close me and reopen to finalize counting\n");
		hellcnt = 0;
		return;	
	}
	mlist l;
	mnode *n;
	FILE *fp;
	if(!(fp = fopen("../DataBase/money.dat", "r"))) {
		creat("../DataBase/money.dat", 0666);
		fp = fopen("../DataBase/money.dat", "r");
	}
	minit(&l);
	dash1 = 1;
	data2 *data1 = (data2 *)malloc(sizeof(data2));
	static int pos = 0;
	while(fread(data1, sizeof(*data1), 1, fp)) {
		n = NULL;
		n = (mnode *)malloc(sizeof(mnode));
		minitNode(n);
		minsert(&l, n, data1, pos);
		pos++;
		data1 = NULL;
		data1 = (data2 *)malloc(sizeof(data2));
	}
//	fclose(fp);
	char name[100], price[100], quantity[100], date[100];
	long long acc;
	int choise = 0;
	printf("T> Hey there, I am here to manage ur money\n");
	char tmpvar[1];
	while(choise != 5) {
rchoise:	printf("T> choose one of the following:\n  1)New entry\n  2)view balance\n  3)credit\n  4)view all entries\n  5)exit\nU> ");
		scanf("%d", &choise);
		switch(choise) {
			case 1:
				printf("T> Enter item name:\nU> ");
				getchar();
				scanf("%[^\n]%*c", data1->name);
retake:				printf("T> Enter price:\nU> ");
				scanf("%s", data1->price);
				if(isNumber(data1->price)) {
					printf("T> You have entered the alphabetic price, which i cant understand I guess! ~_~.\n");
					goto retake;
				}
				getchar();
				printf("T> Enter quantity:\nU> ");
				scanf("%s", data1->quantity);
				printf("T> Enter purchase date:\nU> ");
				getchar();
				scanf("%s", data1->date);
				int sp, bal, price, tprice;
				char conf[10];
				tprice = toInt(data1->price) * toInt(data1->quantity);
				sprintf(data1->price, "%d", tprice);
				sprintf(conf, "%s", data1->price);
				price = toInt(conf);
				l.mdet->spent = l.mdet->spent + price;
				l.mdet->balance = l.mdet->balance - price;
				if(l.mdet->balance < 0) {
					printf("T> Sorry, you cannot make a purchase! you are out of balance:\n");
					hellcnt = 0;
					fclose(fp);
					return;				
				}

				n = NULL;
				n = (mnode *)malloc(sizeof(mnode));
				minitNode(n);
				minsert(&l, n, data1, pos);
				pos++;
				data1 = NULL;
				data1 = (data2 *)malloc(sizeof(data2));
				printf("T> Record inserted successfully\nU> ");
				break;
			case 2:
				printf("T> Your current balance is %lld\nU> ", l.mdet->balance);
				break;
			case 3:
				
				printf("T> Enter amount to credit\nU> ");
				long long amt;
				scanf("%lld", &amt);
				l.mdet->balance = l.mdet->balance + amt;
				printf("T> You have added %lld rupeese, current balance is %lld\nU> ", amt, l.mdet->balance);
				break;	
			case 4://viewing all entries
				showAllentries(&l);
				break;
			case 5:
				printf("T> Thank you for using my service, glad to manage your money!\n");		
				mstoreTotal(&l);
				//fclose(fp);
				hellcnt = 0;
				return;
				break;	
			default:
				printf("T> I couldn't understand your request, please recheck\n");
				//choise = 0;
				break;
		}
	}
	hellcnt = 0;
	//fclose(fp);
}
void writeDiary(user u) { 
	char dname[21];
	char today[102400], buff[1024];
	//char *today = (char *)malloc(sizeof(char) * 102400);
	int i = 0;
	time_t timeval;
	struct tm * timeinfo;
	FILE *fp;
	printf("T> Hey there, hello %s%s, I am gonna interract with you about today which will automatically create diary of today! amazing na!:)\n", gendr, u.name);
	time(&timeval);
	timeinfo = localtime(&timeval);
	sprintf(dname, "diary/%d:%d:%d.txt", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900);
again:	fp = fopen(dname, "r");
	if(fp) {
		//printf("\nT> The file exists already!!, cannot override :(\nU> ");
		i++;
		sprintf(dname, "diary/%d:%d:%dV%d.txt", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, i);
		goto again;
	}
	creat(dname, 0666);
	fp = fopen(dname, "a");
	/*pass 1 */
	printf("T> So, how was the day?\nU> ");
	scanf("%[^\n]%*c", today);
	fwrite("\nToday was a ", 13, 1, fp);
	fwrite(today, strlen(today), 1, fp);
	fwrite(". ", 2, 1, fp);

	/*pass 2 */
	printf("T> when did you wake up?\nU> ");
	scanf("%[^\n]%*c", today);
	fwrite("\n\nToday I woke up at ", 21, 1, fp);
	fwrite(today, strlen(today), 1, fp);
	fwrite(". ", 2, 1, fp);

	/*pass 3 */
	printf("T> And, what special happened today?\nU> ");
	scanf("%[^\n]%*c", today);
	fwrite("\n\nSpecial thing that happened today:\n\t", 38, 1, fp);
	fwrite(today, strlen(today), 1, fp);
	fwrite(". ", 2, 1, fp);

	/*pass 4 */
	printf("T> Did you face any health problem today?\nU> ");
	scanf("%[^\n]%*c", today);
	//today = trim(today);
	//today = cmdLowerCase(today);
	if(strcmp(today, "no") == 0 || strcmp(today, "nope") == 0) {
		fwrite("\n\nMy health was good today, no problem!\n ", 40, 1, fp);
		goto noproblm;
	}
	printf("T> Which problem?\nU> ");
	scanf("%[^\n]%*c", today);
	
	fwrite("\n\nMy health today: ", 19, 1, fp);
	fwrite(today, strlen(today), 1, fp);
	fwrite(". ", 2, 1, fp);

noproblm:
	
	/*pass 5 */
	printf("T> Write what and how you are feeling today\nU> ");
	scanf("%[^\n]%*c", today);
	fwrite("\n\nMy feelings today: ", 21, 1, fp);
	fwrite(today, strlen(today), 1, fp);
	fwrite(". ", 2, 1, fp);
	fwrite("\n********************************** THE END **********************************", 78, 1, fp);
	

	fclose(fp);
	printf("T> The diary has been saved!! :)\n");
	hellcnt = 0;
	return;
	
}
char *analyse(char *cmd, user u) {
	if(strcmp(cmd, "exit") == 0)
		return cmd;
	else if(strcmp(cmd, "manage my contacts") == 0 || strcmp(cmd, "mmcontacts") == 0) {
		printf("T> I am opening a portal for contact management...\n");
		contactManaging(u); 
		printf("U> ");

	}
	else if(strcmp(cmd, "manage my money") == 0 || strcmp(cmd, "mmm") == 0) {
		printf("T> I am opening a portal for money management...\n");
		moneyManaging(u);
		printf("U> ");
		getchar();

	}
	else if(strcmp(cmd, "manage my diary") == 0 || strcmp(cmd, "mmd") == 0) {
		printf("T> I am opening a portal for you to write diary!...\n");
		writeDiary(u);
		printf("U> ");

	}
	else if(strcmp(cmd, "help") == 0 || strcmp(cmd, "yes") == 0 || strcmp(cmd, "yeah") == 0) {
		FILE *helpfp = fopen("../DataBase/help.txt", "r");
		char readfp;
		printf("Here's the help:-\n\n");
		while(fread(&readfp, sizeof(readfp), 1, helpfp)) {
				printf("%c", readfp);
		}
		fclose(helpfp);
		printf("U> ");
	}
	else if(contains(cmd, "hello") && contains(cmd, "not")) {
		printf("T> Ohh dont be angry.. please :'(\nU> ");
	}
	else if(contains(cmd, "fine") && contains(cmd, "am") && contains(cmd, "how")) {
		printf("T> Ohh cool, I am also very good, I am fine too, glad to see that you think so much about me! ;-)\nU> ");
	}
	else if(contains(cmd, "fine") && strlen(cmd) == 4 || contains(cmd, "ok") && strlen(cmd) == 2 || contains(cmd, "okay") && strlen(cmd) == 4) {
		printf("T> Hmm :| \nU> ");
	}
	else if(contains(cmd, "you") && contains(cmd, "beautiful")) {
		printf("T> Ohh thanks for appreciating me and my beauty! ^_^\nU> ");
	}
	else if(contains(cmd, "you") && contains(cmd, "help") && contains(cmd, "can")) {
		printf("T> Yeah, no worries, I am here always! ;-)\nU> ");
	}
	else if(contains(cmd, "kiss") && contains(cmd, "you")) {
		printf("T> Sorry, I am not that type! ~_~\nU> ");
	}
	else if(contains(cmd, "like") && contains(cmd, "she") && contains(cmd, "is") || contains(cmd, "she") && contains(cmd, "is") && contains(cmd, "same") && contains(cmd, "as") && contains(cmd, "you") && !contains(cmd, "?")) {
		printf("T> Ohh really? but I guess I am one of a kind. ;)\nU> ");
	}
	else if(contains(cmd, "hello") && strlen(cmd) == 5) {
		printf("T> Hieeeeeee :-)\nU> ");
	}
	else if(contains(cmd, "hello") && contains(cmd, "techna")) {
		printf("T> Ohh hello, how are you?;]\nU> ");
	}
	else if(contains(cmd, "hello") && contains(cmd, "not")) {
		printf("T> Ohh hiee, how are you?;]\nU> ");
	}
	else if(contains(cmd, "who") && contains(cmd, "are") && contains(cmd, "you")) {
		printf("T> I am Techna full form TECHNICALLY ENHANCED COOL HEURISTIC NEWLY DEFINED ASSISTANT, I am here to serve you what you want!^_^\nU> ");
	}
	else if(contains(cmd, "who") && contains(cmd, "created") && contains(cmd, "you")) {
		printf("T> Mr. Tushar Sandeep Agey created me and I am so happy that he created me ;-)\nU> ");
	}
	else if(contains(cmd, "love") && (contains(cmd, "movies") || contains(cmd, "movie")) && contains(cmd, "?") && contains(cmd, "do")) {
		printf("T> Yeah I do, my favourite movie is 'The Avengers', Its real cool. ;)\nU> ");
	}
	else if(contains(cmd, "I") && contains(cmd, "have") && contains(cmd, "seen")) {
		printf("T> Ohh,, kk Thts cool. ;-);-)\nU> ");
	}
	else if(contains(cmd, "what") && contains(cmd, "hobby") && contains(cmd, "is") || contains(cmd, "what") && contains(cmd, "hobbies") && contains(cmd, "are")) {
		printf("T> I love helping everyone, I also like to try new things & basically my hobbie is to make life simpler for you!!\nU> ");
	}
	else if(contains(cmd, "ohh") || contains(cmd, "really") || contains(cmd, "cool")) {
		printf("T> yeah!!\nU> ");
	}
	else if(contains(cmd, "nice") && contains(cmd, "liked") && contains(cmd, "it") && contains(cmd, "cute")) {
		printf("T> Thanks!!\nU> ");
	}
	else if(contains(cmd, "doing") && contains(cmd, "what")) {
		printf("T> just oiling my nails!! LOL ^_~\nU> ");
	}
	else if(contains(cmd, "haha")) {
		printf("T> ;)\nU> ");
	}
	else if(contains(cmd, "how") && contains(cmd, "are") && contains(cmd, "you")) {
		printf("T> I am very fine and you? :-)\nU> ");
	}
	else if(contains(cmd, "nice") && contains(cmd, "meet")) {
		printf("T> Really true, wish to cu again *_*?\nU> ");
	}
	else if(contains(cmd, "missing") && contains(cmd, "someone") || contains(cmd, "missing") && contains(cmd, "something")) {
		printf("T> Ohh really, dont worry, u'll have it sooner or later, I wish :)\nU> ");
	}
	else if(contains(cmd, "go") && contains(cmd, "home")) {
		printf("T> you will go, don't worry\nU> ");
	}
	else if(contains(cmd, "did") && contains(cmd, "have") && (contains(cmd, "lunch") || contains(cmd, "dinner") || contains(cmd, "breakfast"))) {
		printf("T> Can't explain!! :(\nU> ");
	}
	else if(contains(cmd, "why")) {
		printf("T> I wish to change the topic\nU> ");
	}
	else if(contains(cmd, "what") && contains(cmd, "time") && contains(cmd, "it")) {
		time_t timevar;
		struct tm *timeinfo;
		time(&timevar);
		timeinfo = localtime(&timevar);
		
		printf("T> its %d/%d/%d\t%d:%d:%d\n now, and I guess its nice time to do something innovative ;-)\nU> ", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	}
	else if(contains(cmd, "what") && contains(cmd, "can") && contains(cmd, "i") && contains(cmd, "do") && contains(cmd, "with")) {
		printf("T> you can type any of these commands to get mentioned services! Isnt this cool? :::)?\nU> ");
	}
	else if(contains(cmd, "what") && contains(cmd, "innovative")) {
		printf("T> Hmm, like making a to do diary, or making a plan for upcoming days and scheduling your tasks!!\nU> ");
	}
	else if((contains(cmd, "same") && contains(cmd, "here") && strlen(cmd) == 9) || (contains(cmd, "same") && contains(cmd, "pintch") && strlen(cmd) == 11)) {
		printf("T> WOWeeee ...cool ;-))\nU> ");
	}
	else if(contains(cmd, "love") && (contains(cmd, "movies") || contains(cmd, "movie")) && contains(cmd, "?")) {
		printf("T> I love 'The Avengers', Its real cool. ;)\nU> ");
	}
	else if(contains(cmd, "like") && (contains(cmd, "movies") || contains(cmd, "movie")) && contains(cmd, "?")) {
		printf("T> I like  action movies, and you?. ;)\nU> ");
	}
	else if(contains(cmd, "i") && contains(cmd, "am") && contains(cmd, "fine")) {
		printf("T> Ohh Thats very good!! :-)\nU> ");
	}
	else if(contains(cmd, "don") && contains(cmd, "say") && contains(cmd, "sorry")) {
		printf("T> oh, okay, but I'll try to understand better! ;-)\nU> ");  
	}
	else if(contains(cmd, "welcome") && strlen(cmd) == 7) {
		printf("T> ;) ;) ;)\nU> ");
	}
	else if(contains(cmd, "nope") || contains(cmd, "no")) {
		printf("T> ohh, then simply type exit now. ~_~\nU> ");
	}
	else if(contains(cmd, "good") && contains(cmd, "morning")) {
		printf("T> Ohh very good morning to you, have a beautiful day.\nU> ");
	}
	else if(contains(cmd, "good") && contains(cmd, "afternoon")) {
		printf("T> Good afternoon.. O_O\nU> ");
	}
	else if(contains(cmd, "good") && contains(cmd, "evening")) {
		printf("T> Good evening, planning something special??.\nU> ");
	}
	else if(contains(cmd, "good") && contains(cmd, "night")) {
		printf("T> good night, sweet dreams, take care.. I wanna suggest you something... Write diary....simply type mmd and enter @_@\nU> ");
	}
	else {
		printf("T> I was unable to understand you, sorry\nU> ");
	}
	//hellcnt = 0;
	return cmd;
}
int contains(char *cmd, char *val) {
	char *p, *q;
	p = cmd;
	q = val;
	int i = 0, j = 0;
	int chk1, chk2, gotit = 0;
	chk1 = strlen(val);
	chk2 = 0;
	while(p[i] != '\0' && q[j] != '\0') {
		if(p[i] == q[j]) {
			chk2++;
			if(chk2 == chk1) {
				gotit = 1;
				break;			
			}
				
			i++;	
			j++;
		}
		else {
			i++;
			j = 0;
			chk2 = 0;
		}
		
	}
	return gotit;
}
void contactManaging(user u) {
	if(dash2 == 1) {
		printf("T> I am sorting your contacts, It will take whole day, please close me and reopen to finalize sorting\n");
		hellcnt = 0;
		return;	
	}
	list l;
	node *n;
	FILE *fp;
	if(!(fp = fopen("../DataBase/contact.dat", "r"))) {
		creat("../DataBase/contact.dat", 0666);
		fp = fopen("../DataBase/contact.dat", "r");
	}
	init(&l);
	dash2 = 1;
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
	
	while(choise != 6) {
		printf("T> choose one of the following:\n  1)Add contact\n  2)view contact\n  3)remove contact\n  4)Update existing contact\n  5)view all contacts\n  6)exit\nU> ");
		scanf("%d", &choise);
		switch(choise) {
			case 1:
				printf("T> Enter name:\nU> ");
				getchar();
				scanf("%[^\n]%*c", data1->name);
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
				scanf("%[^\n]%*c", name);
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
				printf("T> All your contacts:-\n");
				showAll(&l);
				break;
			case 6:
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
	fclose(fp);
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
char *trim(char *cmd) {
	int len = strlen(cmd);
	int i = 0, j = len - 1, k, p = 0, q, r;
	while(cmd[i] != 'a' && cmd[i] != 'b' && cmd[i] != 'c' && cmd[i] != 'd' && cmd[i] != 'e' && cmd[i] != 'f' && cmd[i] != 'g' && cmd[i] != 'h' && cmd[i] != 'i' && cmd[i] != 'j' && cmd[i] != 'k' && cmd[i] != 'l' && cmd[i] != 'm' && cmd[i] != 'n' && cmd[i] != 'o' && cmd[i] != 'p' && cmd[i] != 'q' && cmd[i] != 'r' && cmd[i] != 's' && cmd[i] != 't' && cmd[i] != 'u' && cmd[i] != 'v' && cmd[i] != 'w' && cmd[i] != 'x' && cmd[i] != 'y' && cmd[i] != 'z' && cmd[i] != 'A' && cmd[i] != 'B' && cmd[i] != 'C' && cmd[i] != 'D' && cmd[i] != 'E' && cmd[i] != 'F' && cmd[i] != 'O' && cmd[i] != 'N' && cmd[i] != 'M' && cmd[i] != 'L' && cmd[i] != 'K' && cmd[i] != 'J' && cmd[i] != 'I' && cmd[i] != 'H' && cmd[i] != 'G' && cmd[i] != 'Q' && cmd[i] != 'P' && cmd[i] != 'R' && cmd[i] != 'S' && cmd[i] != 'T' && cmd[i] != 'U' && cmd[i] != 'V' && cmd[i] != 'W' && cmd[i] != 'X' && cmd[i] != 'Y' && cmd[i] != 'Z' && cmd[i] != '0' && cmd[i] != '1' && cmd[i] != '2' && cmd[i] != '3' && cmd[i] != '4' && cmd[i] != '5' && cmd[i] != '6' && cmd[i] != '7' && cmd[i] != '8' && cmd[i] != '9' ) {
		if((cmd[i] == ' ') || (cmd[i] == '\n')) {
			while(p < len) {
				cmd[p] = cmd[p + 1];
				
				p++;			
			}
			len--;
			cmd[len] == '\0';
			p = 0;
		
		}
	
	}	
	i = strlen(cmd) - 1;
	while((cmd[i] == ' ') || (cmd[i] == '\n')) {
		cmd[i] = '\0';
		i--;

	}
	return cmd;
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
	char chval, answer[100];
	int i, dash = 0;
	//strcpy(gendr, u.gender);
	if(strcmp(u.gender, "male") == 0) {
		printf("T> Hello Mr. %s, can I help you ?\nU> ", u.name);
		strcpy(gendr, "Mr.");	
	}
	else {
		printf("T> Hello miss %s, can I help you ?\nU> ", u.name);
		strcpy(gendr, "Miss.");
	}
		
	while(strcmp(cmd, "exit") != 0) {
		i = 0;
		toomuchwait();
		if(hellcnt == 0) { 	
			++hellcnt;
		}
prev:		while((chval = getchar()) != '\n') {
			cmd[i] = chval;
			i++;
		}
		cmd[i] = '\0';
		if(cmd[0] == '\0')
			goto prev;
		cmd = cmdLowerCase(cmd);
		cmd = trim(cmd);
		//printf("%s\n", cmd);
		cmd = analyse(cmd, u);
	}
	
}
