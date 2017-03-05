
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
void minit(mlist *l);					//Initializes the list for money management
void minitNode(mnode *n);				//Initializes the node for money management
void mstoreTotal(mlist *l);				//Stores whole data into the file
void minsert(mlist *l, mnode *n, data2 *data1, int pos);//Inserts new purchased item inside list
void showAllentries(mlist *l);				//Displays all purchase history

