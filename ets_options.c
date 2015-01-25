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
#include "ets_options.h"

/* an example of a menu function you will need to fully define */
BOOLEAN display_equipment(struct ets * ets)
{
	struct equipment_node *curr;
	struct equipment_info *data;
	if(!ets)
		return FALSE;
	if(ets->equipment->length == 0)
	{
		printf("The equipment list is empty\n");
		return TRUE;
	}
	curr = ets->equipment->head;
	printf("IdNo\tName\t\tQuantity\n");
	while(curr != NULL)
	{
		data = curr->data;
		printf("%s\t%s\t\t%u\n",data->equipID,data->equipName,data->quantity);
		curr = curr->next;
	}
	return TRUE;
}
BOOLEAN loan_equipment(struct ets * ets)
{
	UNUSED(ets);
	return FALSE;
}

BOOLEAN return_equipment(struct ets * ets)
{
	UNUSED(ets);
	return FALSE;
}

BOOLEAN query_equipment_id(struct ets * ets)
{
	enum string_result result;
	UNUSED(result);
	return FALSE;
}

BOOLEAN query_member_id(struct ets * ets)
{
	UNUSED(ets);
	return FALSE;
}

BOOLEAN display_loan_list(struct ets * ets)
{
	UNUSED(ets);
	return FALSE;
}

BOOLEAN save(struct ets * ets)
{
	UNUSED(ets);
	return FALSE;
}

BOOLEAN add_equipment(struct ets * ets)
{
	UNUSED(ets);
	return FALSE;
}

BOOLEAN change_equipment_amount(struct ets * ets)
{
	UNUSED(ets);
	return FALSE;
}

BOOLEAN add_member(struct ets * ets)
{
	UNUSED(ets);
	return FALSE;
}

BOOLEAN delete_member(struct ets * ets)
{
	UNUSED(ets);
	return FALSE;
}

BOOLEAN abort_program(struct ets * ets)
{
	UNUSED(ets);
	return FALSE;
}
