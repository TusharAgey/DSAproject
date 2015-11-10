
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

# include<stdio.h>
# include<stdlib.h>
# include "list2.h"
void minit(mlist *l) {							//Initializes the list for money management
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
void showAllentries(mlist *l) {						//Displays all purchase history
	if(l->head == NULL) {
		printf("T> No purchase history in database\n ");	
		return;
	}
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
void minitNode(mnode *n) {						//Initializes the node for money management
	n->next = n->prev = NULL; 
	n->ptr = NULL;
}
void minsert(mlist *l, mnode *n, data2 *data1, int pos) {		//Inserts new purchased item inside list
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
void mstoreTotal(mlist *l) {						//Stores whole data into the file
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
