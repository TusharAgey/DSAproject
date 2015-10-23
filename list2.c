# include<stdio.h>
# include<stdlib.h>
# include "list2.h"
void minit(mlist *l) {
	l->head = l->tail = NULL;
	l->length = 0;
	FILE *fp;
	l->mdet = (mdetails *)malloc(sizeof(mdetails));
	
	if(!(fp = fopen("DataBase/mdetail.dat", "r"))) {
		creat("DataBase/mdetail.dat", 0666);
		fp = fopen("DataBase/mdetail.dat", "w");
		l->mdet->balance = 0;
		l->mdet->spent = 0;
		fwrite(l->mdet, sizeof(mdetails), 1, fp);
		fclose(fp);
		return;
	}
	fread(l->mdet, sizeof(mdetails), 1, fp);
	fclose(fp);
}
void showAllentries(mlist *l) {
	printf("T> All your expenditures\n ");
	mnode *p = l->head;
	int i = 1;
	while(p) {
		printf("Entry number %d\n", i);
		printf("\nName:\t%s\nPrice:\t%s\nQuantity:%s\nDate:\t%s\n\n", p->ptr->name, p->ptr->price, p->ptr->quantity, p->ptr->date);
		p = p->next;
		i++;
	}
				
}
void minitNode(mnode *n) {
	n->next = n->prev = NULL; 
	n->ptr = NULL;
}
void minsert(mlist *l, mnode *n, data2 *data1, int pos) {
	FILE *fp = fopen("DataBase/mdetail.dat", "w");
	fwrite(l->mdet, sizeof(mdetails), 1, fp);
	fclose(fp);
	if(pos == 0) {
		l->head = l->tail = n;
		n->ptr = data1;
		(l->length)++;
		return;
	}
	n->ptr = data1;
	l->tail->next = n;
	n->prev = l->tail;
	l->tail = n;
	(l->length)++;
}
void mshowAll(mlist *l) {
	/*mnode *p = l->head;
	while(p) {
		printf("\n%s\n%s\n%s\n\n", p->ptr->name, p->ptr->phone, p->ptr->email);
		p = p->next;	
	}*/
}
void mstoreTotal(mlist *l) {
	data2 myData;
	mnode *p = l->head;
	FILE *fp = fopen("DataBase/money.dat", "w");;
	while(p) {
		myData = *(p->ptr);
		fwrite(&myData, sizeof(myData), 1, fp);
		p = p->next;	
	}
	fclose(fp);
}
void mviewContact(char *name, mlist *l) {
/*	mnode *p = l->head;
	int cnt =0;
	while(p) {
		if(strcmp(p->ptr->name, name) == 0) {
			printf("T> Contact found:\n");
			printf("\n%s\n%s\n%s\n\n", p->ptr->name, p->ptr->phone, p->ptr->email);
			cnt++;
		}
		p = p->next;	
	}
	if(cnt == 0) {
		printf("T> Sorry, no contact found\n");	
	}*/
}
void mupdate(mlist *l, char *phone) {
/*	mnode *p = l->head;
	int cnt =0;
	while(p) {
		if(strcmp(p->ptr->phone, phone) == 0) {
			printf("T> Contact found:\n");
			printf("\n%s\n%s\n%s\n\n", p->ptr->name, p->ptr->phone, p->ptr->email);
			cnt++;
			break;
			
		}
		p = p->next;	
	}
	if(cnt == 0) {
		printf("T> Sorry, no contact found\n");	
	}
	else {
		int choic;
		printf("T> what entry do u want to change?\n\n1)Name\n2)Phone Numbe\n3)email\n4)All\nU> ");
		scanf("%d", &choic);
		if(choic == 4) {
			printf("T> Enter the new details please\nT> Enter new Name\nU> ");
			scanf("%s", p->ptr->name);
			printf("T> Enter new Phone Number\nU> ");
			scanf("%s", p->ptr->phone);
			printf("T> Enter new email\nU> ");
			scanf("%s", p->ptr->email);
		}
		else if(choic == 1) {
			printf("T> Enter new Name\nU> ");
			scanf("%s", p->ptr->name);
		}
		else if(choic == 2) {
			printf("T> Enter new Phone Number\nU> ");
			scanf("%s", p->ptr->phone);
		}
		else if(choic == 3) {
			printf("T> Enter new email\nU> ");
			scanf("%s", p->ptr->email);
		}
		
	}*/

}
