#include "ets_structures.h"

/* initialises the ets data structure to safe initial values. */
BOOLEAN ets_init(struct ets * ets)
{
	if(!ets)
		return FALSE;
	memset(ets, 0, sizeof *ets);
	ets->items_list = malloc(sizeof *(ets->items_list));
	if(!ets->items_list)
		return FALSE;
	ets->items_list->head = NULL;
	ets->items_list->length = 0;
	ets->loans_list = malloc(sizeof *(ets->loans_list));
	if(!ets->loans_list)
		return FALSE;
	ets->loans_list->head = NULL;
	ets->loans_list->length = 0;
	
	ets->members_list = malloc(sizeof *(ets->members_list));
	if(!ets->items_list)
		return FALSE;
	ets->members_list->head = NULL;
	ets->members_list->length = 0;
	return TRUE;
}

/* loads data from the .dat files into memory. */
BOOLEAN load_data(struct ets * ets, const char * equip_fname, const char * member_fname, const char * loan_fname)
{
	FILE *equip_file, *member_file, *loan_file;
	char line[BUFFER_SIZE];
	char *token;
	char *tokens[NUM_FIELDS];
	enum string_result result;
	enum ets_fields field_type;
	enum loan_fields loan_field_type;
	enum member_fields member_field_type;
	unsigned amount;
	struct ets_item *item;
	struct ets_item *loan;
	struct ets_item *member;
	equip_file = fopen(equip_fname, "r");
	if(!equip_file)
	{
		fprintf(stderr, "Cannot open equipment file\n");
		return FALSE;
	}
	while((result = get_string(line, BUFFER_SIZE, equip_file)) != STRING_EMPTY)
	{
		if(result == STRING_TOOLONG)
			return FALSE;
		field_type = ITEM_ID;
		token = strtok(line, DELIMETER);
		while(token != NULL)
		{
			tokens[field_type] = token;
			field_type++;
			token = strtok(NULL, DELIMETER);
		}
		str_to_unsigned(tokens[ITEM_AVAILABILITY],&amount);
		item = malloc(sizeof *item);
		memset(item, 0, sizeof *item);
		create_item(item, tokens[ITEM_ID], tokens[ITEM_NAME], amount);
		add_node(ets->items_list, item);
	}
	fclose(equip_file);
	member_file = fopen(member_fname, "r");
	if(!member_file)
	{
		fprintf(stderr, "Cannot open member file\n");
		return FALSE;
	}
	while((result = get_string(line, BUFFER_SIZE, member_file)) != STRING_EMPTY)
	{
		if(result == STRING_TOOLONG)
			return FALSE;
		member_field_type = MEMBER_ID;
		token = strtok(line, DELIMETER);
		while(token != NULL)
		{
			tokens[member_field_type] = token;
			member_field_type++;
			token = strtok(NULL, DELIMETER);
		}
		member = malloc(sizeof *member);
		memset(member, 0, sizeof *member);
		create_member(member, tokens[MEMBER_ID], tokens[LAST_NAME], tokens[FIRST_NAME]);
		add_member_node(ets->members_list, member);
	}
	fclose(member_file);
	loan_file = fopen(loan_fname, "r");
	if(!loan_file)
	{
		fprintf(stderr, "Cannot open loan file\n");
		return FALSE;
	}
	while((result = get_string(line, BUFFER_SIZE, loan_file)) != STRING_EMPTY)
	{
		if(result == STRING_TOOLONG)
			return FALSE;
		loan_field_type = BORROWER_ID;
		token = strtok(line, DELIMETER);
		while(token != NULL)
		{
			tokens[loan_field_type] = token;
			loan_field_type++;
			token = strtok(NULL, DELIMETER);
		}
		str_to_unsigned(tokens[ITEMS_BORROWED], &amount);
		loan = malloc(sizeof *loan);
		memset(loan, 0, sizeof *loan);
		create_loans(loan, tokens[BORROWER_ID], tokens[BORROWEE_ID], amount);
		add_node(ets->loans_list, loan);
	}
	fclose(loan_file);
	return TRUE;
}

void create_item(struct ets_item *item, char *itemId, char *name, unsigned quantity)
{
	strcpy(item->itemId, itemId);
	strcpy(item->itemName, name);
	item->available = quantity;
}

void create_loans(struct ets_item *loan, char *borrowerId, char *borroweeId, unsigned quantity)
{
	strcpy(loan->borrowerId, borrowerId);
	strcpy(loan->borroweeId, borroweeId);
	loan->items_borrowed = quantity;
}
void create_member(struct ets_item *member, char *memberId, char *lastName, char *firstName)
{
	strcpy(member->memberId, memberId);
	strcpy(member->lastName, lastName);
	strcpy(member->firstName, firstName);
}
/* frees all dynamically allocated data. */
void free_node(struct ets_node *node)
{
	free(node->data);
	free(node);
	node = NULL;
}
void ets_free(struct ets * ets)
{
	struct ets_node *node, *temp;    
	if(!ets)
	{
		/* Nothing to free */
		return;
	}
	node = ets->items_list->head;
	temp = NULL;
	while(node != NULL)
	{
		temp = node;
		node = node->next;
		free_node(temp);
	}    
	node = ets->loans_list->head;
	temp = NULL;
	while(node != NULL)
	{
		temp = node;
		node = node->next;
		free_node(temp);
	}
	
	node = ets->members_list->head;
	temp = NULL;
	while(node != NULL)
	{
		temp = node;
		node = node->next;
		free_node(temp);
	}
	
	free(ets->items_list);
	ets->items_list = NULL;    
	free(ets->loan_file);
	free(ets->equip_file);
	free(ets->member_file);
	ets->loan_file = NULL;
	ets->equip_file = NULL;
	ets->member_file = NULL;
	
}

BOOLEAN add_node(struct ets_list *list, struct ets_item *item)
{
	struct ets_node *new_node, *curr, *prev;
	if(list == NULL || item == NULL)
		return FALSE;
	prev = NULL;
	curr = list->head;
	new_node = malloc(sizeof *(new_node));
	if(new_node == NULL)
		return FALSE;
	memset(new_node, 0, sizeof *new_node);
	new_node->data = item;
	while(curr != NULL && strcmp(item->itemName, curr->data->itemName) > 0)
	{
		prev = curr;
		curr = curr->next;
	}
	new_node->next = curr;
	if(prev == NULL)
		list->head = new_node;
	else
		prev->next = new_node;
	list->length += 1;
	return TRUE;
}

BOOLEAN add_member_node(struct ets_list *list, struct ets_item *member)
{
	struct ets_node *new_node, *curr, *prev;
	if(list == NULL || member == NULL)
	{
		if(member == NULL)
		{
			printf("Node unable to initialize\n");
		}
		else
		{
			printf("List unable to initialize\n");
		}
		return FALSE;
	}
	prev = NULL;
	curr = list->head;
	new_node = malloc(sizeof *(new_node));
	if(new_node == NULL)
		return FALSE;
	memset(new_node, 0, sizeof *new_node);
	new_node->data = member;
	while(curr != NULL && strcmp(member->lastName, curr->data->lastName) > 0)
	{
		prev = curr;
		curr = curr->next;
	}
	new_node->next = curr;
	if(prev == NULL)
		list->head = new_node;
	else
		prev->next = new_node;
	list->length += 1;
	printf("%s\t%s\t%s\n",new_node->data->memberId, new_node->data->lastName, new_node->data->firstName);
	return TRUE;
}

BOOLEAN combine_items_loans(struct ets * ets)
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
				strcpy(loan_data->itemName, item_data->itemName);
				strcpy(item_data->firstName, loan_data->firstName);
				strcpy(item_data->lastName, loan_data->lastName);
				item_data->total = item_data->available - loan_data->items_borrowed;
			}
			curr_loan = curr_loan->next;
		}
		if(item_data->total == 0)
			item_data->total = item_data->available;
		curr_item = curr_item->next;
	}
	return TRUE;
}

BOOLEAN combine_members_loans(struct ets * ets)
{
	struct ets_node *curr_member;
	struct ets_item *member_data;
	struct ets_node *curr_loan;
	struct ets_item *loan_data;
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
			{
				strcpy(loan_data->firstName, member_data->firstName);
				strcpy(loan_data->lastName, member_data->lastName);
				member_data->items_borrowed = loan_data->items_borrowed;
			}
			curr_loan = curr_loan->next;
		}
		curr_member = curr_member->next;
	}
	return TRUE;
}

BOOLEAN find_item(struct ets * ets, char *needle)
{
	struct ets_node  *curr_node;
	struct ets_item  *curr_data;
	curr_node = ets->items_list->head;
	while(curr_node != NULL)
	{
		curr_data = curr_node->data;
		if(strcmp(curr_data->itemId, needle) == 0)
			return TRUE;
		curr_node = curr_node->next;
	}
	return FALSE;
}

BOOLEAN find_member(struct ets * ets, char *needle)
{
	struct ets_node  *curr_node;
	struct ets_item  *curr_data;
	curr_node = ets->members_list->head;
	while(curr_node != NULL)
	{
		curr_data = curr_node->data;
		if(strcmp(curr_data->memberId, needle) == 0)
			return TRUE;
		curr_node = curr_node->next;
	}
	return FALSE;
}

BOOLEAN delete_item_node(struct ets_list *list, char *item_id, struct ets_item *removed_item)
{
	struct ets_node *prev, *curr;
	if(list == NULL || item_id == NULL)
	{
		return  FALSE;
	}    
	prev = NULL;
	curr = list->head;
	/* Traverse through list until the item with the given id is found or
	* the end of the list is reached */
	while(curr != NULL && strcmp(item_id, curr->data->itemId) != 0)
	{
		prev = curr;
		curr = curr->next;
	}
	    
	/* Check if item was found */
	if (curr == NULL)
	{
		return FALSE;
	}    
	/* Copy data from node being removed to the removed_item pointer for
	* printing */
	memcpy(removed_item, curr->data, sizeof *(curr->data));   
	/* Remove desired node from list and change the link from the node before
	* it to point to the next node in the list */
	if(prev == NULL)
	{
		/* Node to delete is at head of list */
		list->head = curr->next;
	}
	else
	{
		prev->next = curr->next;
	}
	free_node(curr);
	return TRUE;
}

BOOLEAN delete_member_node(struct ets_list *list, char *member_id, struct ets_item *removed_member)
{
	struct ets_node *prev, *curr;
	if(list == NULL || member_id == NULL)
	{
		return  FALSE;
	}    
	prev = NULL;
	curr = list->head;
	/* Traverse through list until the item with the given id is found or
	* the end of the list is reached */
	while(curr != NULL && strcmp(member_id, curr->data->memberId) != 0)
	{
		prev = curr;
		curr = curr->next;
	}
	if(curr->data->items_borrowed != 0)
	{
		printf("Cannot delete member if loans are due\n");
		return FALSE;
	}	
	/* Check if item was found */
	if (curr == NULL)
	{
		return FALSE;
	}    
	/* Copy data from node being removed to the removed_item pointer for
	* printing */
	memcpy(removed_member, curr->data, sizeof *(curr->data));   
	/* Remove desired node from list and change the link from the node before
	* it to point to the next node in the list */
	if(prev == NULL)
	{
		/* Node to delete is at head of list */
		list->head = curr->next;
	}
	else
	{
		prev->next = curr->next;
	}
	free_node(curr);
	return TRUE;
}

