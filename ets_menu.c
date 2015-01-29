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

/* initialises the menu */
void menu_init(struct menu_item  menu[])
{
	int i;
	char *options[] =
	{"Loan Equipment", "Return Equipment", "Query Equipment ID", "Query Member ID",
	"Display Equipment List", "Display Loan List","Display Member List", "Save and Exit", "Add New Equipment", "Change Equipment Amount",
	"Add Member", "Delete Member",
	"Abort"};
	
	BOOLEAN (*options_funcs[])(struct ets*) =
	{
		loan_equipment, return_equipment, query_equipment_id, query_member_id, display_equipment, display_loan_list,
		display_member_list, save, add_equipment, change_equipment_amount, add_member, delete_member, abort_program
	};
	
	for(i = 0; i < NUM_MENU_ITEMS; i++)
	{
		strcpy(menu[i].name, options[i]);
		menu[i].func = options_funcs[i];
	}
	
}

void menu_print(struct menu_item  menu[])
{
	int i;
	printf("Main Menu\n");
	for(i = 0; i < NUM_MENU_ITEMS; i++)
	{
		printf("\t%d. %s\n", i + 1, menu[i].name);
	}
	printf("\n");
}

int get_valid_selection(struct menu_item menu[])
{
	int selection;
	enum int_result selection_result;
	BOOLEAN valid_option_selected = FALSE;    
	printf("\n\n");
	while(!valid_option_selected)
	{
		printf("\nSelect Option(1 - 13): ");
		selection_result = get_int(&selection, BUFFER_SIZE, 1, NUM_MENU_OPTS, stdin);
		/* Test if input was a valid selection */
		if(selection_result == INT_SUCCESS)
		{
			valid_option_selected = TRUE;
		}
		else
		{
			printf("Invalid input\n\n");
			menu_print(menu);
		}
	}
	return selection;
}
