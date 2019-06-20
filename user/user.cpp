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

#include "../libs/generalh.h"
#define K 100.0

User *create_user(unsigned int user_id = 0)
{
	User *new_user = new User;
	new_user -> user_id = user_id;
	new_user -> watched = NULL;
	return new_user;
}

void add_user(Linked *list, User *user)
{
	if(user == NULL)
		return;
	Linked *node = create((void*)user);
	node -> next = NULL;
	add(list, node);
}
User *find_user(Linked *list, unsigned int user_id)
{
	Linked *temp = list;
	while (temp != NULL)
	{
		if(temp -> data != NULL)
			if( ((User*)temp -> data) -> user_id == user_id )
				return (User*)temp -> data;
		 temp = temp -> next;
	}
	return NULL;
}
unsigned kes(User *user1, User *user2)
{
	unsigned int counter = 0;
	Linked *w1 = user1 -> watched;
	while(w1 != NULL)
	{
		if(w1 -> data == NULL)
		{
			w1 = w1 -> next;
			continue;
		}
		Linked *w2 = user2 -> watched;
		while(w2 != NULL)
		{
			if(w2 -> data == NULL)
			{
				w2 = w2 -> next;
				continue;
			}
			if(((Movie*)w2 -> data) -> movie_id > ((Movie*)w1 -> data) -> movie_id)
				break;
			if(((Movie*)w2 -> data) -> movie_id == ((Movie*)w1 -> data) -> movie_id)
			{
				counter++;
				break;
			}
			w2 = w2 -> next;
		}
		w1 = w1 -> next;
	}
	return counter;
}
Linked *unwatched(User *b, User *a)
{
	Linked *list = create(NULL);
	Linked *wl1 = a -> watched;
	while (wl1 != NULL)
	{
		if(wl1 -> data == NULL)
		{
			wl1 = wl1 -> next;
			continue;
		}
		bool in = false;
		Linked *wl2 = b -> watched;
		while(wl2 != NULL)
		{
			if(wl2 -> data == NULL)
			{
				wl2 = wl2 -> next;
				continue;
			}
			if(wl2 -> data == wl1 -> data)
			{
				in = true;
				break;
			}
			wl2 = wl2 -> next;
		}
		if(!in)
			add(list,create(wl1 -> data));
		wl1 = wl1 -> next;
	}
	if(list->next == NULL)
		return NULL;
	next(&list);
	return list;
}
Linked *compareAll(Linked *ulist, User *u)
{
	Linked *list = new Linked;
	list -> data = NULL;
	list -> next = NULL;
	Linked *temo = ulist;
	while(temo != NULL)
	{
		float a = uratio((User*)temo -> data, u);
		unsigned uid = ((User*)temo -> data) -> user_id;
		Match *n = new Match;
		n -> user_id = uid;
		n -> ratio = a;
		add(list, create((void*)n));
		temo = temo -> next;
	}
	return list -> next;
}
float uratio(User *u1, User *u2)
{
	if(u1 == u2)
		return K;
	return (float)(kes(u1,u2)*K)/bir(u1,u2);
}
unsigned bir(User *u1, User *u2)
{
	unsigned counter = 0;
	Linked *user1 = u1 -> watched;
	Linked *user2 = u2 -> watched;
	while (user1 != NULL)
	{
		counter++;
		user1 = user1 -> next;
	}
	while(user2 != NULL)
	{
		counter++;
		user2 = user2 -> next;
	}
	return counter - kes(u1,u2);
}
Linked *file_user(Linked *list, const char *file)
{
	Linked *temp = new Linked;
	temp -> next = NULL;
	temp -> data = NULL;
	ifstream fin(file);
	string output;
	getline(fin, output);
	while(getline(fin, output))
	{
		string myText(output);
		istringstream iss(myText);
		string user_id;
    	string movie_id;
		getline(iss,user_id, '\t');
		getline(iss,movie_id, '\n');
		User *tmp = NULL;
		if(temp -> next != NULL)
			tmp = find_user(temp, atoi(user_id.substr(1).c_str()));
		Movie *m;
		if ( tmp != NULL)
		{
			m = find_movie(list, atoi(movie_id.substr(1).c_str()));
			m -> wc += 1;
			if((Linked*)tmp -> watched == NULL)
				((Linked*)tmp -> watched) -> data = m;
			else
				add_movie(tmp -> watched, m);
		}
		else
		{
			User *crt = create_user(atoi(user_id.substr(1).c_str()));
			add_user(temp,crt);
			crt -> watched = create((void*)find_movie(list, atoi(movie_id.substr(1).c_str())));
		}
	}
	return temp -> next;
}
void print_user(User *temp)
{
	if(temp != NULL)
	{
    	cout << "- - - - - - - - - - - - - - - - #" << temp -> user_id << endl;
		print_movie_linked(temp -> watched);
	}
}
void print_user_linked(Linked *list)
{
	while (list != NULL)
	{
    	print_user((User*)list -> data);
    	list = list -> next;
  	}
}
