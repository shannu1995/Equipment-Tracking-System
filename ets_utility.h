/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Summer 2015 Assignment #2
 * Full Name        : Shanmuka Prasad Sivapurapu
 * Student Number   : s3453738
 * Course Code      : COSC 1076
 * Program Code     : BP   0096
 * Start up code provided by David Shaw
 * Based on 2014 code by Paul Miller and Virginia King
 **********************************************************************/
#include "ets_type.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef ETS_UTILITY
#define ETS_UTILITY
#define NUM_MENU_OPTS 12

void read_rest_of_line(void);
BOOLEAN ets_init(struct ets * ets);
BOOLEAN load_data(struct ets * ets,
	const char * equip_fname,
	const char * member_fname,
	const char * loan_fname);
void ets_free(struct ets * ets); 

#endif

