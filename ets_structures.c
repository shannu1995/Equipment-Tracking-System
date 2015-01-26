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
void ets_free(struct ets * ets)
{
	UNUSED(ets);
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
