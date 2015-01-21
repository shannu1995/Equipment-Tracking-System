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

/* initialises the menu */
void menu_init(struct menu_item  menu[])
{
	int i;
	char *options[] =
	{"Loan Equipment", "Return Equipment", "Query Equipment ID", "Query Member ID",
	"Display Equipment List", "Display Loan List", "Save and Exit", "Add New Equipment", "Change Equipment Amount",
	"Add Member", "Delete Member",
	"Abort"};
	
	BOOLEAN (*options_funcs[])(struct ets*) =
	{
		loan_equipment, return_equipment, query_equipment_id, query_member_id, display_equipment, display_loan_list,
		save, add_equipment, change_equipment_amount, add_member, delete_member, abort_program
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
	printf("\n");
	for(i = 0; i < NUM_MENU_ITEMS; i++)
	{
		printf("%d. %s\n", i + 1, menu[i].name);
	}
}
