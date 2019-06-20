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

Movie *create_movie (unsigned movie_id = 0, string movie_name = "")
{
	Movie *new_movie = new Movie;
	new_movie -> movie_id = movie_id;
	new_movie -> movie_name = movie_name;
	new_movie -> wc = 0;
	return new_movie;
}
void add_movie(Linked *list, Movie *new_movie)
{
	Linked *node = create((void *)new_movie);
	add(list, node);
}
Linked *file_movie(const char *file)
{
	Linked *m = new Linked;
	ifstream fin(file);
	string output;
	(getline(fin, output));
	while(getline(fin, output))
	{
		string myText(output);
		istringstream iss(myText);
		string movie_id;
		string movie_name;
		getline(iss,movie_id, ' ');
		getline(iss,movie_name, '\n');
		add_movie(m, create_movie(atoi(movie_id.substr(1).c_str()), movie_name));
	}
	return m -> next;
}
Movie *find_movie(Linked *list ,unsigned movie_id)
{
	Linked *a = list;
	while (a != NULL)
	{
		if (movie_id == ((Movie*)a -> data) -> movie_id)
			return (Movie*)a -> data;
		a = a -> next;
	}
	return NULL;
}
void print_movie(Movie *m)
{
	Movie *temp = m;
	if(temp != NULL)
		cout << temp -> movie_id << "\t\t" << temp -> wc << ((temp -> wc == 0 || temp -> wc == 1)?" user":" users") << " watched \t" << temp -> movie_name;
	cout << endl;
}
void print_movie_linked(Linked *a)
{
	cout << "MOVIE ID" << "\t" << "RATE" << "\t\t\t" << "MOVIE NAME" << endl;
	while (a != NULL)
	{
		if(a->data != NULL)
			print_movie((Movie*)a -> data);
		a = a -> next;
	}
}
