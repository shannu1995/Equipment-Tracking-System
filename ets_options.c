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
		printf("%s\t%s\t%u\t%u\n",item_data->itemId, item_data->itemName, item_data->available, item_data->total);
		curr_item = curr_item->next;
	}
	return TRUE;
}

BOOLEAN display_member_list(struct ets * ets)
{
	struct ets_node *curr_member;
	struct ets_item *member_data;
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
		curr_member = curr_member->next;
		printf("%s\t%s\t%s\t%u\n",member_data->memberId, member_data->firstName, member_data->lastName, member_data->items_borrowed);
	}
	return TRUE;
}

BOOLEAN loan_equipment(struct ets * ets)
{
	return FALSE;
}

BOOLEAN return_equipment(struct ets * ets)
{
	UNUSED(ets);
	return FALSE;
}

BOOLEAN query_equipment_id(struct ets * ets)
{
	struct ets_node *item_node;
	struct ets_item *item_data;
	enum string_result result;
	struct ets_node *curr_loan;
	struct ets_item *loan_data;
	char line[BUFFER_SIZE];
	UNUSED(result);
	printf("Please enter item ID\n");
	result = get_string(line,IDLEN + 2,stdin);
	item_node = ets->items_list->head;
	while(item_node != NULL)
	{
		item_data = item_node->data;
		if(strcmp(item_data->itemId, line) == 0)
		{
			curr_loan = ets->loans_list->head;
			printf("%s\t%s\t\t\t%u\n",item_data->itemId,item_data->itemName,item_data->available - item_data->total);
			while(curr_loan != NULL)
			{
				loan_data = curr_loan->data;
				if(strcmp(item_data->itemId, loan_data->borroweeId) == 0)
				{
					printf("\t  %s %s %s*%u\n",loan_data->borrowerId, loan_data->firstName, loan_data->lastName, loan_data->items_borrowed);
				}
				curr_loan = curr_loan->next;
			}
		}
		item_node = item_node->next;
	}
	return FALSE;
}

BOOLEAN query_member_id(struct ets * ets)
{
	struct ets_node *member_node;
	struct ets_item *member_data;
	struct ets_node *curr_loan;
	struct ets_item *loan_data;
	enum string_result result;
	char line[BUFFER_SIZE];
	printf("Please enter member ID\n");
	result = get_string(line,IDLEN + 2,stdin);
	UNUSED(result);
	member_node = ets->members_list->head;
	while(member_node != NULL)
	{
		member_data = member_node->data;
		if(strcmp(member_data->memberId, line) == 0)
		{
			curr_loan = ets->loans_list->head;
			printf("%s\t%s %s\t\t\t%u\n",member_data->memberId,member_data->firstName,member_data->lastName,member_data->items_borrowed);
			while(curr_loan != NULL)
			{
				loan_data = curr_loan->data;
				if(strcmp(member_data->memberId, loan_data->borrowerId) == 0)
				{
					printf("\t  %s %s*%u\n",loan_data->borroweeId, loan_data->itemName, loan_data->items_borrowed);
				}
				curr_loan = curr_loan->next;
			}
		}
		member_node = member_node->next;
	}
	return FALSE;
}

BOOLEAN display_loan_list(struct ets * ets)
{
	struct ets_node *member_node;
	struct ets_item *member_data;
	struct ets_node *curr_loan;
	struct ets_item *loan_data;
	member_node = ets->members_list->head;
	while(member_node != NULL)
	{
		member_data = member_node->data;
		curr_loan = ets->loans_list->head;
		printf("%s\t%s %s\t\t\t%u\n",member_data->memberId,member_data->firstName,member_data->lastName,member_data->items_borrowed);
		while(curr_loan != NULL)
		{
			loan_data = curr_loan->data;
			if(strcmp(member_data->memberId, loan_data->borrowerId) == 0)
			{
				printf("\t  %s %s*%u\n",loan_data->borroweeId, loan_data->itemName, loan_data->items_borrowed);
			}
			curr_loan = curr_loan->next;
		}
		member_node = member_node->next;
	}
	return TRUE;
}

BOOLEAN save(struct ets * ets)
{
	UNUSED(ets);
	return FALSE;
}

BOOLEAN add_equipment(struct ets * ets)
{
	char id[IDLEN + 2];
	char name[NAMELEN + 2];
	int quantity;
	enum int_result unsigned_result;
	enum string_result result;
	struct ets_item *item;
	BOOLEAN is_valid_id = FALSE;
	BOOLEAN is_valid_name = FALSE;
	BOOLEAN is_valid_quantity = FALSE;
	printf("Please enter new item Id\n");
	while(!is_valid_id)
	{
		result = get_string(id,IDLEN + 2,stdin);
		if(result == STRING_SUCCESS)
			is_valid_id = TRUE;
		else
			printf("Invalid item id, try again\n");
	}
	printf("Please enter the equipment name\n");
	while(!is_valid_name)
	{
		result = get_string(name, NAMELEN + 2, stdin);
		if(result == STRING_SUCCESS)
			is_valid_name = TRUE;
		else
			printf("Invalid item name, try again\n");
	}
	printf("Please enter the total quantity\n");
	while(!is_valid_quantity)
	{
		unsigned_result = get_int(&quantity,BUFFER_SIZE, 1, 99, stdin);
		if(unsigned_result == INT_SUCCESS && quantity > 0)
			is_valid_quantity = TRUE;
		else
			printf("Invalid quantity, try again\n");
	}
	item = malloc(sizeof *(item));
	memset(item, 0, sizeof *item);
	create_item(item, id, name, (unsigned)quantity);
	add_node(ets->items_list, item);
	return FALSE;
}

BOOLEAN change_equipment_amount(struct ets * ets)
{
	char id[IDLEN + 2];
	int quantity;
	enum int_result unsigned_result;
	enum string_result result;
	struct ets_node *curr_node;
	struct ets_item *item_data;
	BOOLEAN is_valid_id = FALSE;
	BOOLEAN is_valid_quantity = FALSE;
	printf("Please enter the equipment ID\n");
	while(!is_valid_id)
	{
		result = get_string(id,IDLEN + 2,stdin);
		if(result == STRING_SUCCESS)
		{
			if(find_item(ets,id) == FALSE)
			{
				printf("No item with %s as its ID\n",id);
			}
			else
			{
				is_valid_id = TRUE;
			}
		}
		else
			printf("Invalid item id, try again\n");
	}
	curr_node = ets->items_list->head;
	while(curr_node != NULL)
	{
		item_data = curr_node->data;
		if(strcmp(item_data->itemId, id) == 0)
		{
			printf("%s\t%s x %u\n",item_data->itemId,item_data->itemName,item_data->available);
			printf("Please enter revised quantity(Enter 0 to delete)\n");
			while(!is_valid_quantity)
			{
				unsigned_result = get_int(&quantity,BUFFER_SIZE, 0, 99, stdin);
				if(unsigned_result == INT_SUCCESS && quantity >= 0)
				{
					if(quantity == 0)
					{
						delete_item_node(ets->items_list,item_data->itemId,item_data);
					}
					is_valid_quantity = TRUE;
				}
				else
					printf("Invalid quantity, try again\n");
			}
			item_data->available = (unsigned)quantity;
		}
		curr_node = curr_node->next;
	}
	return TRUE;
}

BOOLEAN add_member(struct ets * ets)
{
	char id[IDLEN + 2];
	char fname[NAMELEN + 2];
	char lname[NAMELEN + 2];
	enum string_result result;
	struct ets_item *member;
	BOOLEAN is_valid_id = FALSE;
	BOOLEAN is_valid_first_name = FALSE;
	BOOLEAN is_valid_last_name = FALSE;
	printf("Please enter new member Id\n");
	while(!is_valid_id)
	{
		result = get_string(id,IDLEN + 2,stdin);
		if(result == STRING_SUCCESS)
			is_valid_id = TRUE;
		else
			printf("Invalid item id, try again\n");
	}
	printf("Please enter the member's first name\n");
	while(!is_valid_first_name)
	{
		result = get_string(fname, NAMELEN + 2, stdin);
		if(result == STRING_SUCCESS)
			is_valid_first_name = TRUE;
		else
			printf("Invalid first name, try again\n");
	}
	printf("Please enter the member's last name\n");
	while(!is_valid_last_name)
	{
		result = get_string(lname, NAMELEN + 2, stdin);
		if(result == STRING_SUCCESS)
			is_valid_last_name = TRUE;
		else
			printf("Invalid last name, try again\n");
	}
	member = malloc(sizeof *(member));
	memset(member, 0, sizeof *member);
	create_member(member, id, fname, lname);
	add_member_node(ets->members_list, member);
	return FALSE;
}

BOOLEAN delete_member(struct ets * ets)
{
	char id[IDLEN + 2];
	enum string_result result;
	struct ets_item *member;
	BOOLEAN is_valid_id = FALSE;
	member = ets->members_list->head->data;
	printf("Please enter the member ID\n");
	while(!is_valid_id)
	{
		result = get_string(id,IDLEN + 2,stdin);
		if(result == STRING_SUCCESS)
			is_valid_id = TRUE;
		else
			printf("Invalid member id, try again\n");
		
	}
	delete_member_node(ets->members_list, id, member);
	return FALSE;
}

BOOLEAN abort_program(struct ets * ets)
{
	UNUSED(ets);
	return FALSE;
}
