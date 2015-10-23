# include<stdio.h>
# include<stdlib.h>
# include "list.h"
void init(list *l) {
	l->head = l->tail = NULL;
	l->length = 0;
}
void initNode(node *n) {
	n->next = n->prev = NULL;
	n->ptr = NULL;
}
void insert(list *l, node *n, data *data1, int pos) {
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
void showAll(list *l) {
	node *p = l->head;
	while(p) {
		printf("\n%s\n%s\n%s\n\n", p->ptr->name, p->ptr->phone, p->ptr->email);
		p = p->next;	
	}
}
void storeTotal(list *l) {
	data myData;
	node *p = l->head;
	FILE *fp = fopen("DataBase/contact.dat", "w");;
	while(p) {
		myData = *(p->ptr);
		fwrite(&myData, sizeof(myData), 1, fp);
		p = p->next;	
	}
	fclose(fp);
}
void viewContact(char *name, list *l) {
	node *p = l->head;
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
	}
}
void update(list *l, char *phone) {
	node *p = l->head;
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
		
	}

}
