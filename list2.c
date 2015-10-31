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
