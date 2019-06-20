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

struct Movie
{
	unsigned movie_id;
	string movie_name;
	unsigned wc;
};

Movie *create_movie (unsigned, string);
void add_movie(Linked*, Movie*);
Linked *file_movie(const char *);
Movie *find_movie(Linked *, unsigned);
void print_movie(Movie *);
void print_movie_linked(Linked *);
