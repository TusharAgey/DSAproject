typedef struct mnode {
	struct data2 *ptr;
	struct mnode *next, *prev;
}mnode;
typedef struct mlist {
	struct mnode *head, *tail;
	struct mdetails *mdet;
	int length;
}mlist;
typedef struct data2 {
	char name[100];
	char price[100];
	char quantity[100];
	char date[100];
	
}data2;
typedef struct mdetails {
	long long balance;
	long long spent;
}mdetails;
void minit(mlist *l);
void minitNode(mnode *n);
void mstoreTotal(mlist *l);
void minsert(mlist *l, mnode *n, data2 *data1, int pos);
/*void remov(mlist *l, int pos);
void append(mlist *l, char *str);
int length(mlist *l);
void reverse(mlist *l);*/
void mviewContact(char *name, mlist *l);
void mshowAll(mlist *l);
void mupdate(mlist *l, char *phone);
void showAllentries(mlist *l);

