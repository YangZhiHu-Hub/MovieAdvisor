/******************************************************************/
/******************************************************************/
/* Created by Berk Cetinsaya on 2014/12/16                        */
/* Copyright (c) 2019 Berk Cetinsaya. All rights reserved.        */
/* Edited: June 20, 2019                                          */
/******************************************************************/
/******************************************************************/
/******************************************************************/
/******************************************************************/
/******************************************************************/
/******************************************************************/

#include "generalh.h"

Linked *create(void *data)
{
	Linked *list = new Linked;
	list -> data = data;
	list -> next = NULL;
	return list;
}
void add(Linked *list, Linked *node)
{
	Linked *temp = list;
	if(temp != NULL)
		while(temp -> next != NULL)
			temp = temp -> next;
	temp -> next = node;
	node->next = NULL;
}
void *next(Linked **list)
{
	Linked *temp = *list;
	*list = (*list) -> next;
	temp -> next = NULL;
	delete temp;
}
Linked *find (Linked *first, Linked *node)
{
	Linked *temp = first;
	if(temp != NULL)
		while(temp -> next != NULL)
			if(temp -> next == node)
				return temp;
			else
				temp = temp -> next;
	return NULL;
}
void remove (Linked **list , Linked *what)
{
	if(*list == what)
	{
		next(&what);
		return;
	}
	Linked *temp = find(*list, what);
	if(temp == NULL)
		return;
	temp -> next = what -> next;
	what -> next = NULL;
	delete what;
}
void print(Linked *list)
{
	Linked *temp = list;
	while(temp != NULL)
	{
		cout << ((Movie*)(temp -> data)) -> movie_id << endl;
		temp = temp -> next;
	}
	cout << endl;
}
