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

#include "hes.h"
#include "linked.h"
#include "../user/user.h"
#include "../movie/movie.h"

struct Match
{
	unsigned user_id;
	double ratio;
};
void print_match(Match *);
void print_match_linked(Linked *);
