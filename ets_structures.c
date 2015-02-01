#include "ets_structures.h"

/*Initialises the ets data structure to safe initial values. */
BOOLEAN ets_init(struct ets * ets)
{
	/*If ets is not initialized, return FALSE*/
	if(!ets)
		return FALSE;
	memset(ets, 0, sizeof *ets);
	/*Allocates memory for the items list*/
	ets->items_list = malloc(sizeof *(ets->items_list));
	/*If memory allocation of the items has failed*/
	if(!ets->items_list)
		return FALSE;
	/*Initializing the items list by defaulting values to NULL and zero*/
	ets->items_list->head = NULL;
	ets->items_list->length = 0;
	/*Allocates memory for the loans list*/
	ets->loans_list = malloc(sizeof *(ets->loans_list));
	/*If memory allocation of the loans has failed*/
	if(!ets->loans_list)
		return FALSE;
	/*Initializing the loans list by defaulting the values to NULL and zero*/
	ets->loans_list->head = NULL;
	ets->loans_list->length = 0;
	/*Allocates memory for the members list*/
	ets->members_list = malloc(sizeof *(ets->members_list));
	/*If memory allocation of members list has failed*/
	if(!ets->items_list)
		return FALSE;
	/*Initializing members by defaulting the values to NULL and zero*/
	ets->members_list->head = NULL;
	ets->members_list->length = 0;
	return TRUE;
}

/* loads data from the .dat files into memory. */
BOOLEAN load_data(struct ets * ets, const char * equip_fname,
	       	const char * member_fname, const char * loan_fname)
{
	/*Everytime a line is read, it is tokenized with the delimeter "|".
	 * That token is passed into an array of enums.*/
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
	int num_fields;
	equip_file = fopen(equip_fname, "r");
	/*Check if equipment file exists or not*/
	if(!equip_file)
	{
		fprintf(stderr, "Cannot open equipment file\n");
		return FALSE;
	}
	while((result = get_string(line, BUFFER_SIZE, equip_file))
		       	!= STRING_EMPTY)
	{
		if(result == STRING_TOOLONG)
			/*If string is too long*/
			return FALSE;
		field_type = ITEM_ID;
		token = strtok(line, DELIMETER);
		num_fields = 0;
		while(token != NULL)
		{
			tokens[field_type] = token;
			if(is_valid_item(token, field_type) == FALSE)
			{
				printf("Corrupt file, exiting\n");
				return FALSE;
			}
			field_type++;
			num_fields++;
			token = strtok(NULL, DELIMETER);
		}
		if(num_fields != 3)
		{
			fprintf(stderr, "Fatal Error: Number of data fields must be 3, in the %s file, it is %d\n"
					,equip_fname, num_fields);
			return FALSE;
		}
		str_to_unsigned(tokens[ITEM_AVAILABILITY],&amount);
		if(amount < 1 || amount > 9999)
		{
			printf("Number of items must be between 1 and 9999\n");
			return FALSE;
		}
		item = malloc(sizeof *item);
		/*Initializes all variables to NULL or 0*/
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
	while((result = get_string(line, BUFFER_SIZE, member_file))
		       	!= STRING_EMPTY)
	{
		if(result == STRING_TOOLONG)
			return FALSE;
		member_field_type = MEMBER_ID;
		token = strtok(line, DELIMETER);
		num_fields = 0;
		while(token != NULL)
		{
			tokens[member_field_type] = token;
			if(is_valid_member(token, member_field_type) == FALSE)
			{
				printf("Corrupt file, exiting\n");
				return FALSE;
			}
			member_field_type++;
			num_fields++;
			token = strtok(NULL, DELIMETER);
		}
		if(num_fields != 3)
		{
			fprintf(stderr,"Fatal Error: Number of fields must be 3, in the %s file, it is %d\n",
					member_fname, num_fields);
			return FALSE;
		}
		member = malloc(sizeof *member);
		memset(member, 0, sizeof *member);
		create_member(member, tokens[MEMBER_ID],
			       	tokens[LAST_NAME], tokens[FIRST_NAME]);
		add_member_node(ets->members_list, member);
	}
	/*Safely closes the pointer */
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
		num_fields = 0;
		while(token != NULL)
		{
			tokens[loan_field_type] = token;
			if(is_valid_loan(token, loan_field_type) == FALSE)
			{
				printf("Corrupt file, exiting\n");
				return FALSE;
			}
			loan_field_type++;
			num_fields++;
			token = strtok(NULL, DELIMETER);
		}
		if(num_fields != 3)
		{
			fprintf(stderr,"Fatal Error: Number of fields must be 3, in the %s file, it is %d\n",loan_fname, num_fields);
			return FALSE;
		}
		str_to_unsigned(tokens[ITEMS_BORROWED], &amount);
		if(amount < 1 || amount > 9999)
		{
			printf("Number of items must be between 1 and 9999\n");
			return FALSE;
		}
		/*Allocates memory for a loan*/
		loan = malloc(sizeof *loan);
		memset(loan, 0, sizeof *loan);
		create_loans(loan, tokens[BORROWER_ID], tokens[BORROWEE_ID], amount);
		add_node(ets->loans_list, loan);
	}
	/*Safely closing the loan file*/
	fclose(loan_file);
	/*Allocates memory to ets->equip_file which can be used for saving
	 * and exits if allocation fails*/
	ets->equip_file = (char *) malloc(sizeof(char) * (strlen(equip_fname) + 1));
	if(!ets->equip_file)
	{
		printf("Cannot malloc items_file\n");
		return FALSE;
	}
	/*Allocates memory to ets->member_file and exits if allocation fails*/
	ets->member_file = (char *) malloc(sizeof(char) * (strlen(member_fname) + 1));
	if(!ets->member_file)
	{
		printf("Cannot malloc member_file\n");
		return FALSE;
	}
	/*Allocates memory to ets->loan_file and exits if allocation fails*/
	ets->loan_file = (char *) malloc(sizeof(char) * (strlen(loan_fname) + 1));
	if(!ets->loan_file)
	{
		printf("Cannot malloc loan file\n");
		return FALSE;
	}
	/*Copies the equipment file name, member file name and loan file name
	 *into the strings present in ets*/
	strcpy(ets->equip_file, equip_fname);
	strcpy(ets->member_file, member_fname);
	strcpy(ets->loan_file, loan_fname);
	return TRUE;
}

void create_item(struct ets_item *item, char *itemId, char *name,
	       	unsigned quantity)
{
	strcpy(item->itemId, itemId);
	strcpy(item->itemName, name);
	item->available = quantity;
}

void create_loans(struct ets_item *loan, char *borrowerId, char *borroweeId,
	       	unsigned quantity)
{
	strcpy(loan->borrowerId, borrowerId);
	strcpy(loan->borroweeId, borroweeId);
	loan->items_borrowed = quantity;
}
void create_member(struct ets_item *member, char *memberId,
	       	char *lastName, char *firstName)
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
	/*Free the memory of each list*/
	free(ets->items_list);
	free(ets->members_list);
	free(ets->loans_list);
	ets->items_list = NULL;    
	/*Free the memory of each file*/
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
	/*Add node in an ascending order*/
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
	while(curr != NULL && strcmp(member->firstName, curr->data->firstName) > 0)
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

/*This function combines items and loans.
 * it iterates through both the items_list and loans_list.
 * It updates the number of items lent by subtracting from the loan_data->items_borrowed
 * */
BOOLEAN combine_items_loans(struct ets * ets)
{
	struct ets_node *curr_item;
	struct ets_item *item_data;
	struct ets_node *curr_loan;
	struct ets_item *loan_data;
	if(!ets)
		return FALSE;
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
				if(loan_data->items_borrowed == 0)
				{
					delete_loan_node(ets->loans_list,
							loan_data->borroweeId,
							loan_data);
				}
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
		return TRUE;
	}
	curr_member = ets->members_list->head;
	/*Outer Loop(member loop)*/
	while(curr_member != NULL)
	{
		member_data = curr_member->data;
		curr_loan = ets->loans_list->head;
		/*Inner Loop(member loop)*/
		while(curr_loan != NULL)
		{
			loan_data = curr_loan->data;
			if(strcmp(member_data->memberId, loan_data->borrowerId) == 0)
			{
				strcpy(loan_data->firstName,
					       	member_data->firstName);
				strcpy(loan_data->lastName,
					       	member_data->lastName);
				strcpy(member_data->itemId,
					       	loan_data->borroweeId);
				/*updates the number of items_borrowed by adding it with loan_data->items_borrowed*/
				member_data->items_borrowed += loan_data->items_borrowed;
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
		{
			return TRUE;
		}
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
		{
			return TRUE;
		}
		curr_node = curr_node->next;
	}
	printf("No member with id as %s has been found\n",needle);
	return FALSE;
}
BOOLEAN find_loan(struct ets * ets, char *item_needle, char *member_needle)
{
	struct ets_node *curr_node;
	struct ets_item *curr_data;
	curr_node = ets->loans_list->head;
	while(curr_node != NULL)
	{
		curr_data = curr_node->data;
		if(strcmp(curr_data->borroweeId, item_needle) == 0 &&
		strcmp(curr_data->borrowerId, member_needle) == 0)
			return TRUE;
		curr_node = curr_node->next;
	}
	return FALSE;
}
BOOLEAN delete_item_node(struct ets_list *list, char *item_id,
	       	struct ets_item *removed_item)
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

BOOLEAN delete_member_node(struct ets_list *list, char *member_id,
	       	struct ets_item *removed_member)
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
		printf("Cannot delete member because loans are due\n");
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
BOOLEAN is_valid_item(char *field, enum ets_fields field_type)
{
	/*This functions checks to see if the entered field is valid or not*/
	switch(field_type)
	{
		case ITEM_ID:
			if(strlen(field) != IDLEN || field[0] != 'E')
			{
				if(field[0] != 'E')
					printf("Starting letter must be an \'E\'\n");
				else
					printf("Id length must be %d\n",IDLEN);
				return FALSE;
			}
			break;
		case ITEM_NAME:
			if(strlen(field) > NAMELEN)
			{
				printf("String is too bog\n");
				return FALSE;
			}
			break;
		case ITEM_AVAILABILITY:
			if(is_unsigned(field) == FALSE)
				return FALSE;
	}
	return TRUE;
}
BOOLEAN is_valid_member(char *field, enum member_fields field_type)
{
	/*This functions checks to see if the entered field is valid or not*/
	switch(field_type)
	{
		case MEMBER_ID:
			if(strlen(field) != IDLEN || field[0] != 'M')
			{
				if(field[0] != 'M')
					printf("Starting letter must be an \'M\'\n");
				else
					printf("Id length must be %d\n",IDLEN);
				return FALSE;
			}
			break;
		case FIRST_NAME:
			if(strlen(field) > NAMELEN)
			{
				printf("String is too big\n");
				return FALSE;
			}
			break;
		case LAST_NAME:
			if(strlen(field) > NAMELEN)
			{
				printf("String is too big\n");
				return FALSE;
			}
			break;
	}
	return TRUE;
}

BOOLEAN is_valid_loan(char *field, enum loan_fields field_type)
{
	switch(field_type)
	{
		case BORROWER_ID:
			if(field[0] != 'M' || strlen(field) > IDLEN)
			{
				return FALSE;
			}
			if(strlen(field) < IDLEN)
			{
				printf("Member Id must have 5 characters\n");
				return FALSE;
			}
			break;
		case BORROWEE_ID:
			if(field[0] != 'E' || strlen(field) > IDLEN)
			{
				return FALSE;
			}
			break;
		case ITEMS_BORROWED:
			if(is_unsigned(field) == FALSE)
				return FALSE;
	}
	return TRUE;
}

BOOLEAN save_member_data(struct ets * ets, FILE * memberFp)
{
	/* Get head of list as starting node */
	struct ets_node * node = ets->members_list->head;
	if(!memberFp)
		return FALSE;
	while(node)
	{       
		/* Print node -> data to file */
		fprintf(memberFp, "%s|%s|%s\n",node->data->memberId,
			       	node->data->firstName, node->data->lastName);
		/* get next node */
		node = node->next;
	}
	return TRUE;
}

BOOLEAN save_loan_data(struct ets * ets, FILE * loanFp)
{
	/* Get head of list as starting node */
	struct ets_node * node = ets->loans_list->head;
	if(!loanFp)
		return FALSE;
	while(node)
	{       
		/* Print node -> data to file */
		fprintf(loanFp, "%s|%s|%u\n",node->data->borrowerId,
			       	node->data->borroweeId,
			       	node->data->items_borrowed);
		/* get next node */
		node = node->next;
	}
	return TRUE;
}

void print_item(struct ets * ets, char *itemId)
{
	struct ets_node *item_node;
	struct ets_item *item_data;
	item_node = ets->items_list->head;
	while(item_node != NULL)
	{
		item_data = item_node->data;
		if(strcmp(item_data->itemId, itemId) == 0)
		{
			printf("%s\t%s x %u\n",item_data->itemId,
					item_data->itemName,
					item_data->available);
		}
		item_node = item_node->next;
	}
}

void print_member(struct ets * ets, char *memberId)
{
	struct ets_node *member_node;
	struct ets_item *member_data;
	member_node = ets->members_list->head;
	while(member_node != NULL)
	{
		member_data = member_node->data;
		if(strcmp(member_data->memberId, memberId) == 0)
		{
			printf("%s %s %s\n",member_data->memberId,
					member_data->lastName,
					member_data->firstName);
		}
		member_node = member_node->next;
	}
}

void display_member_info(struct ets * ets, char *id)
{
	struct ets_node *member_node;
	struct ets_item *member_data;
	struct ets_node *curr_loan;
	struct ets_item *loan_data;
	int i;
	member_node = ets->members_list->head;
	while(member_node != NULL)
	{
		member_data = member_node->data;
		if(strcmp(member_data->memberId, id) == 0)
		{
			curr_loan = ets->loans_list->head;
			for(i = 1; i <= 50; i++)
				printf("-");
			printf("\n");
			printf("%s\t%s %s\t\t\t%u\n",member_data->memberId,member_data->lastName,
					member_data->firstName,
					member_data->items_borrowed);
			while(curr_loan != NULL)
			{
				loan_data = curr_loan->data;
				if(strcmp(member_data->memberId, loan_data->borrowerId) == 0)
				{
					printf("\t  %s %s x %u\n",loan_data->borroweeId,
						       	loan_data->itemName,
						       	loan_data->items_borrowed);
				}
				curr_loan = curr_loan->next;
			}
		}
		member_node = member_node->next;
	}
}

BOOLEAN save_item_data(struct ets * ets, FILE * equipFp)
{
	/* Get head of list as starting node */
	struct ets_node * node = ets->items_list->head;
	if(!equipFp)
		return FALSE;
	while(node)
	{      
		/* Print node -> data to file */
		fprintf(equipFp, "%s|%s|%u\n", node->data->itemId,
		    node->data->itemName,node->data->available);
		/* get next node */
		node = node->next;
	}
	return TRUE;
}

BOOLEAN combine_members_loans2(struct ets * ets)
{
	struct ets_node *curr_member;
	struct ets_item *member_data;
	struct ets_node *curr_loan;
	struct ets_item *loan_data;
	if(!ets)
		return FALSE;
	if(ets->members_list->length == 0)
	{
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
			if(strcmp(member_data->memberId,
				loan_data->borrowerId) == 0)
			{
				strcpy(loan_data->firstName,
					member_data->firstName);
				strcpy(loan_data->lastName,
					member_data->lastName);
				strcpy(member_data->itemId,
					loan_data->borroweeId);
			}
			curr_loan = curr_loan->next;
		}
		curr_member = curr_member->next;
	}
	return TRUE;
}

void add_to_existing_loan(struct ets * ets, char *item_needle,
	       	char *member_needle, unsigned amount)
{
	struct ets_node *curr_node;
	struct ets_item *curr_data;
	curr_node = ets->loans_list->head;
	while(curr_node != NULL)
	{
		curr_data = curr_node->data;
		if(strcmp(curr_data->borroweeId, item_needle) == 0 && strcmp(curr_data->borrowerId, member_needle) == 0)
		{
			curr_data->items_borrowed += amount;
		}
		curr_node = curr_node->next;
	}
}

BOOLEAN delete_loan_node(struct ets_list *list, char *itemId,
	       	struct ets_item *removed_item)
{
	struct ets_node *prev, *curr;
	if(list == NULL || itemId == NULL)
	{
		return  FALSE;
	}    
	prev = NULL;
	curr = list->head;
	/* Traverse through list until the item with the given id is found or
	* the end of the list is reached */
	while(curr != NULL && strcmp(itemId, curr->data->borroweeId) != 0)
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

BOOLEAN item_borrowed(struct ets * ets, char * itemId, unsigned quantity)
{
	struct ets_node *curr_node;
	struct ets_item *item_data;
	curr_node = ets->items_list->head;
	while(curr_node != NULL)
	{
		item_data = curr_node->data;
		if(strcmp(itemId, item_data->itemId) == 0)
		{
			item_data->total -= quantity;
			return TRUE;
		}
		curr_node = curr_node->next;
	}
	return FALSE;
}

BOOLEAN item_returned(struct ets * ets, char * itemId, unsigned quantity)
{
	struct ets_node *curr_node;
	struct ets_item *item_data;
	curr_node = ets->items_list->head;
	while(curr_node != NULL)
	{
		item_data = curr_node->data;
		if(strcmp(itemId, item_data->itemId) == 0)
		{
			item_data->total += quantity;
			return TRUE;
		}
		curr_node = curr_node->next;
	}
	return FALSE;
}

