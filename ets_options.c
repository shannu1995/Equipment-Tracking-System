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
	struct ets_node *curr_item;
	struct ets_item *item_data;
	struct ets_node *curr_loan;
	struct ets_item *loan_data;
	if(!ets)
		return FALSE;
	if(ets->items_list->length == 0)
	{
		printf("The list is empty\n");
		return TRUE;
	}
	curr_item = ets->items_list->head;
	while(curr_item != NULL)
	{
		item_data = curr_item->data;
		curr_loan = ets->loans_list->head;
		while(curr_loan != NULL)
		{
			loan_data = curr_loan->data;
			if(strcmp(item_data->itemId,loan_data->borroweeId) == 0)
			{
				item_data->total = item_data->available + loan_data->items_borrowed;
			}
			curr_loan = curr_loan->next;
		}
		if(item_data->total == 0)
			item_data->total = item_data->available;
		printf("%s\t%s\t%u\t%u\n",item_data->itemId, item_data->itemName, item_data->available, item_data->total);
		curr_item = curr_item->next;
	}
	return TRUE;
}

BOOLEAN display_member_list(struct ets * ets)
{
	struct ets_node *curr_member;
	struct ets_item *member_data;
	struct ets_node *curr_loan;
	struct ets_item *loan_data;
	printf("\n");
	if(!ets)
		return FALSE;
	if(ets->members_list->length == 0)
	{
		printf("The list is empty\n");
		return TRUE;
	}
	curr_member = ets->members_list->head;
	while(curr_member != NULL)
	{
		member_data = curr_member->data;
		curr_loan = ets->loans_list->head;
		while(curr_loan != NULL)
		{
			loan_data = curr_loan->data;
			if(strcmp(member_data->memberId, loan_data->borrowerId) == 0)
				member_data->items_borrowed = loan_data->items_borrowed;
			curr_loan = curr_loan->next;
		}
		curr_member = curr_member->next;
		printf("%s\t%s\t%s\t%u\n",member_data->memberId, member_data->firstName, member_data->lastName, member_data->items_borrowed);
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
	return TRUE;
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
