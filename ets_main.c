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

#include "ets_menu.h"
#include "ets_structures.h"
#include <stdlib.h>


int main(int argc, char * argv[])
{
	struct ets ets;
	struct menu_item menu_items[NUM_MENU_ITEMS];
	if(argc != NUMARGS)
	{
		fprintf(stderr,"Fatal Error: Must have %d number of command line arguments\n",NUMARGS);
		return EXIT_FAILURE;
	}
	ets_init(&ets);
	load_data(&ets, argv[1], argv[2], argv[3]);
	menu_init(menu_items);    
	menu_print(menu_items);
	display_equipment(&ets);
	return EXIT_SUCCESS;
}
