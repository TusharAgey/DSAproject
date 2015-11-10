
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
void init(list *l);					//Initializes the list type for contact management module.
void initNode(node *n);					//Initializes node
void storeTotal(list *l);				//Storing whole data inti the file
void insert(list *l, node *n, data *data1, int pos);	//Inserts new node to list (node means new contact here).
void viewContact(char *name, list *l);			//Showing particular contact according to the name given by user
void showAll(list *l);					//Displays all contacts that are previously stored or added
void update(list *l, char *phone);			//Updates the contact entry

