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
	int selection;
	struct menu_item menu_items[NUM_MENU_ITEMS];
	BOOLEAN exit = FALSE;
	BOOLEAN load_success;
	if(argc != NUMARGS)
	{
		fprintf(stderr,"Fatal Error: Must have %d number of command line arguments\n",
		NUMARGS);
		printf("Enter in the format ./ets <equip_file> <member_file> <loan_file>\n");
		return EXIT_FAILURE;
	}
	ets_init(&ets);
	load_success = load_data(&ets, argv[1], argv[2], argv[3]);
	if(load_success == FALSE)
	{
		/*If there was a problem with loading the file*/
		printf("Make sure that you enter in the format ./ets <equip_file> <member_file> <loan_file>\n");
		return EXIT_FAILURE;
	}
	combine_members_loans(&ets);
	combine_items_loans(&ets);
	menu_init(menu_items);    
	do
	{
		printf("\n\n");
		menu_print(menu_items);
		selection = get_valid_selection(menu_items);
		/*If either the abort option or save & exit option is selected*/
		if((selection == 13 || selection == 8)
		&& menu_items[selection - 1].func(&ets) == TRUE)
		{
			exit = TRUE;
			break;
		}
		if(selection != 13 && selection != 8)
			menu_items[selection - 1].func(&ets);
		combine_members_loans2(&ets);
	}
	while(exit == FALSE);
	ets_free(&ets);
	return EXIT_SUCCESS;
}
