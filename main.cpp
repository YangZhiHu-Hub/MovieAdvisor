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

#include "libs/generalh.h"

using namespace std;
int menu;
void print_match(Match *m)
{
	Match *temp = m;
	if(temp != NULL)
		cout << "-------------------------" << endl;
		cout << "| USER ID" << " | " << "RATE\t|" << endl;
		cout << "| " << temp -> user_id << "\t    " << setprecision (3) << fixed << temp -> ratio << "%\t|";
	cout << endl;
}
void print_match_linked(Linked *list)
{
	while (list != NULL)
	{
		print_match((Match*)list -> data);
		list = list -> next;
	}
}
void usort (Linked **list)
{
	Linked *temp = NULL;
	Linked *biggest = NULL;
	Linked *sorted = new Linked;
	sorted -> data = NULL;
	sorted -> next = NULL;
	while(*list != NULL)
	{
		temp = *list;
		biggest = temp;
		while (temp != NULL)
		{
			if(((Match*)temp -> data) -> ratio > ((Match*)biggest -> data) -> ratio)
				biggest = temp;
			temp = temp -> next;
		}
		add(sorted,create(biggest->data));
		if(biggest == *list)
		{
			next(list);
			continue;
		}
		remove(list,biggest);
	}
	next(&sorted);
	*list = sorted;
}
void msort (Linked **list)
{
	Linked *temp = NULL;
	Linked *biggest = NULL;
	Linked *sorted = new Linked;
	sorted -> data = NULL;
	sorted -> next = NULL;
	while(*list != NULL)
	{
		temp = *list;
		biggest = temp;
		while (temp != NULL)
		{
			if(((Movie*)temp -> data) -> wc > ((Movie*)biggest -> data) -> wc)
				biggest = temp;
			temp = temp -> next;
		}
		add(sorted,create(biggest -> data));
		if(biggest == *list)
		{
			next(list);
			continue;
		}
		remove(list,biggest);
	}
	next(&sorted);
	*list = sorted;
}
void mn()
{
	cout << "\nEnter the menu number\n"
		"1.To compare a new user\n"
		"2.To see all users and the sorted similarity ratios\n"
		"3.To see recommended user's details and the recommendable movies\n"
		"4.To see all users and watched movies\n"
		"5.To see all movie ids and movie names\n"
		"6.To see the user details\n"
		"7.To see the movie details\n"
		"8.To see the most watched 3 movies\n"
		"0.Exit\n";
	cin >> menu;
}

int main(int arg1, char **arg2)
{
	char *mfile = "files/movie_idmap.txt";
	char *ufile = "files/client-preference.txt";
	int selection = 0;
	switch(arg1)
	{
		case 4:
			mfile = arg2[3];
		case 3:
			ufile = arg2[2];
		case 2:
			selection = atoi(arg2[1]);
			while (selection < 0 || selection >99)
			{
				cout << "Enter a valid number: ";
				cin >> selection;
			}
			break;
		case 1:
			cout << "\n\tWarning! You are using defaults!\n"
					"You will be notified for user id and program will use\n"
					"default values for file names...\n"
					"For specifying file names you can use:\n"
					<< arg2[0]
					<< " [user_id] [user_file] [movie_file]\n"
					" --> press ENTER to continue, CTRL+C to ABORT!: ";
			string input;
			getline(cin,input);
			cout << "Enter user id to compare: ";
			cin >> input;
			selection = atoi(input.c_str());
			while (selection < 0 || selection >99)
			{
				cout << "Enter a valid number: ";
				cin >> selection;
			}
	}
	Linked *mv = file_movie(mfile);
	Linked *usr = file_user(mv, ufile);
	start:
	Linked *c = compareAll(usr, find_user(usr, selection));
	usort(&c);
	cout << "\nThe most matched 3 users\n" << endl;
	if(c != NULL)
	{
		print_match((Match*)c -> next -> data);
		print_match((Match*)c -> next -> next -> data);
		print_match((Match*)c -> next -> next -> next -> data);
	}
	cout << "-------------------------" << endl;
	mn();
	while (menu != 0)
	{
		switch (menu)
		{
			case 1:
			{
				cout << "To compare a new user enter a user id: ";
				cin >> selection;
				while (selection < 0 || selection >99)
				{
					cout << "Enter a valid number: ";
					cin >> selection;
				}
				goto start;
				break;
			}
			case 2:
			{
				cout << "\nAll users and the sorted similarity ratios: \n"<< endl;
				print_match_linked(c);
				cout << "-------------------------" << endl;
				mn();
				break;
			}
			case 3:
			{
				Linked *yeni = create(NULL);
				Linked *_i = c;
				while( ((Match*)_i -> next -> data) -> ratio == ((Match*)c -> next -> data) -> ratio )
				{
					Linked *difference = unwatched(find_user(usr, selection), find_user(usr, ((Match*)_i -> next -> data) -> user_id));
					cout << "\nRecommended user: " << ((Match*)_i -> next -> data) -> user_id << endl;
					cout << "-------------------------" << endl;
					msort(&difference);
					print_movie_linked(difference);
					if(difference != NULL)
					{
						Linked *t = difference;
						while(t != NULL && ((Movie*)t -> data) -> wc == ((Movie*)difference -> data) -> wc)
						{
							add(yeni,create(t->data));
							t = t -> next;
						}
					}
					_i = _i -> next;
				}
				cout << "-------------------------" << endl;
				next(&yeni);
				msort(&yeni);
				if(yeni != NULL)
					print_movie((Movie*)yeni->data);
				mn();
				break;
			}
			case 4:
			{
				print_user_linked(usr);
				mn();
				break;
			}
			case 5:
			{
				cout << "\nSorted all movies: \n" << endl;
				msort(&mv);
				print_movie_linked(mv);
				mn();
				break;
			}
			case 6:
			{
				print_user(find_user(usr, selection));
				mn();
				break;
			}
			case 7:
			{
				unsigned movie;
				cout << "Enter a movie id: ";
				cin >> movie;
				cout << "Details: " << endl;
				cout << "MOVIE ID" << "\t" << "RATE" << "\t\t\t" << "MOVIE NAME" << endl;
				print_movie(find_movie(mv, movie));
				mn();
				break;
			}
			case 8:
			{
				cout << "The most watched 3 movies: " << endl;
				msort(&mv);
				cout << "MOVIE ID" << "\t" << "RATE" << "\t\t\t" << "MOVIE NAME" << endl;
				if(mv != NULL)
				{
					print_movie((Movie*)mv -> data);
					print_movie((Movie*)mv -> next -> data);
					print_movie((Movie*)mv -> next -> next -> data);
				}
				mn();
				break;
			}
			default:
			{
				cout << "Please enter a valid menu option: ";
				cin >> menu;
				break;
			}
		}
	}
	return 0;
}
