typedef struct node {
	struct data *ptr;
	struct node *next, *prev;
}node;
typedef struct list {
	struct node *head, *tail;
	int length;
}list;
typedef struct data {
	char name[100];
	char phone[100];
	char email[100];
}data;
void init(list *l);
void initNode(node *n);
void storeTotal(list *l);
void insert(list *l, node *n, data *data1, int pos);
/*void remov(list *l, int pos);
void append(list *l, char *str);
int length(list *l);
void reverse(list *l);*/
void viewContact(char *name, list *l);
void showAll(list *l);
void update(list *l, char *phone);
<<<<<<< HEAD

=======
>>>>>>> bb0a8c67ac80de4a2eb65228d5c06121d65b01fd
