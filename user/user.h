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

struct User
{
	unsigned user_id;
	Linked *watched;
};

User *create_user(unsigned);
void add_user(Linked *, User *);
void add_watch(User *, Linked *);
Linked *file_user(Linked *, const char *);
User *find_user(Linked *, unsigned int);
unsigned kes(User*,User*);
unsigned bir(User*,User*);
float uratio(User*,User*);
void print_user(User *);
void print_user_linked(Linked *);
void print_user_film(User *);
Linked *compareAll(Linked *, User *);
Linked *unwatched(User *, User *);
