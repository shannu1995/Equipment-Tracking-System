/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Summer 2015 Assignment #2
 * Full Name        : EDIT HERE
 * Student Number   : EDIT HERE
 * Course Code      : EDIT HERE
 * Program Code     : EDIT HERE
 * Start up code provided by David Shaw
 * Based on 2014 code by Paul Miller and Virginia King
 **********************************************************************/

#include "ets_menu.h"
#include "ets_type.h"
#include <stdlib.h>


int main(int argc, char * argv[])
{
	struct ets ets;
	struct menu_item menu_items[NUM_MENU_ITEMS];
	/* The UNUSED() function is designed to prevent warnings while your 
	 * code is only partially complete. Delete these 4 function calls once 
	 * you are using the data structures declared above in your own code */
	if(argc != NUMARGS)
	{
		fprintf(stderr,"Fatal Error: Must have %d number of command line arguments\n",NUMARGS);
		return EXIT_FAILURE;
	}
	UNUSED(argv);
	UNUSED(ets);
	menu_init(menu_items);    
	menu_print(menu_items);
	return EXIT_SUCCESS;
}