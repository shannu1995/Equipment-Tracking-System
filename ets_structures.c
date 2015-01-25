#include "ets_structures.h"

/* initialises the ets data structure to safe initial values. */
BOOLEAN ets_init(struct ets * ets)
{
	if(!ets)
		return FALSE;
	memset(ets, 0, sizeof *ets);
	ets->loans = malloc(sizeof *(ets->loans));
	if(!ets->loans)
	{
		fprintf(stderr, "Fatal Error: Failed to initialize loans\n");
		return FALSE;
	}
	ets->loans->head = NULL;
	ets->loans->length = 0;
	
	ets->equipment = malloc(sizeof *(ets->equipment));
	if(!ets->equipment)
	{
		fprintf(stderr, "Fatal Error: Failed to initialize equipment\n");
		return FALSE;
	}
	ets->equipment->head = NULL;
	ets->equipment->length = 0;
	
	ets->members = malloc(sizeof *(ets->members));
	if(!ets->members)
	{
		fprintf(stderr, "Fatal Error: Failed to initialize members\n");
		return FALSE;
	}
	ets->members->head = NULL;
	ets->members->length = 0;
	
	return TRUE;
}

/* loads data from the .dat files into memory. */
BOOLEAN load_data(struct ets * ets, const char * equip_fname, const char * member_fname, const char * loan_fname)
{
	struct equipment_info *item;
	struct member_info *person;
	struct loan_info *loan;
	FILE *equip_file, *member_file, *loan_file;
	char *token;
	char *tokens[NUM_FIELDS];
	char *member_tokens[MEMBER_FIELDS];
	char *loan_tokens[NUM_FIELDS]; 
	char line[BUFFER_SIZE];
	enum member_fields member_field_type;
	enum string_result result;
	enum equip_fields field_type;
	enum loan_fields loan_field_type;
	unsigned quantity;
	unsigned lent;
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
		field_type = ID;
		token = strtok(line, DELIMETER);
		while(token != NULL)
		{
			tokens[field_type] = token;
			field_type++;
			token = strtok(NULL, DELIMETER);
		}
		str_to_unsigned(tokens[QUANTITY],&quantity);
		item = malloc(sizeof *item);
		memset(item, 0, sizeof *item);
		create_equipment(item, tokens[ID], tokens[NAME], quantity);
		add_item_node(ets->equipment, item);
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
		member_field_type = MEM_ID;
		token = strtok(line, DELIMETER);
		
		while(token != NULL)
		{
			member_tokens[member_field_type] = token;
			member_field_type++;
			token = strtok(NULL, DELIMETER);
		}
		lent = 0;
		person = malloc(sizeof *person);
		memset(person, 0, sizeof *person);
		create_member(person, member_tokens[MEM_ID], member_tokens[FIRST_NAME], member_tokens[LAST_NAME], lent);
		add_member_node(ets->members, person);
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
		loan_field_type = MEMBER_ID;
		token = strtok(line, DELIMETER);
		while(token != NULL)
		{
			loan_tokens[loan_field_type] = token;
			loan_field_type++;
			token = strtok(NULL, DELIMETER);
		}
		str_to_unsigned(loan_tokens[NUMBER_LENT], &quantity);
		loan = malloc(sizeof *loan);
		memset(loan, 0, sizeof *loan);
		create_loan(loan, loan_tokens[MEMBER_ID], loan_tokens[ITEM_ID], quantity);
		add_loan_node(ets->loans, loan);
	}
	fclose(loan_file);
	return TRUE;
}
/* frees all dynamically allocated data. */
void ets_free(struct ets * ets)
{
	UNUSED(ets);
}
void create_equipment(struct equipment_info *item, char *id, char *name, unsigned quantity)
{
	strcpy(item->equipID, id);
	strcpy(item->equipName, name);
	item->quantity = quantity;
}
void create_member(struct member_info *person, char *id, char *first_name, char *last_name, unsigned lent)
{
	strcpy(person->memberID,id);
	strcpy(person->lastName,last_name);
	strcpy(person->firstName,first_name);
	person->borrowed = lent;
}
void create_loan(struct loan_info *loan, char *member_id, char *item_id, unsigned amount)
{
	strcpy(loan->memberID, member_id);
	strcpy(loan->equipID, item_id);
	loan->number = amount;
}
BOOLEAN add_item_node(struct equipment_list *list, struct equipment_info *item)
{
	struct equipment_node *new_node, *prev, *curr;
	if(list == NULL || item == NULL)
		return FALSE;
	prev = NULL;
	curr = list->head;
	new_node = malloc(sizeof(new_node));
	if(!new_node)
	{
		return FALSE;
	}
	new_node->data = item;
	while(curr != NULL && strcmp(item->equipName, curr->data->equipName))
	{
		prev = curr;
		curr = curr->next;
	}
	new_node->next = curr;
	if(prev == NULL)
	{
		list->head = new_node;
	}
	else
	{
		prev->next = new_node;
	}
	list->length++;
	return TRUE;
}


BOOLEAN add_member_node(struct member_list *list, struct member_info *person)
{
	struct member_node *new_node, *prev, *curr;
	if(list == NULL || person == NULL)
		return FALSE;
	prev = NULL;
	curr = list->head;
	new_node = malloc(sizeof(new_node));
	if(!new_node)
	{
		return FALSE;
	}
	new_node->data = person;
	while(curr != NULL && strcmp(person->lastName, curr->data->lastName))
	{
		prev = curr;
		curr = curr->next;
	}
	new_node->next = curr;
	if(prev == NULL)
	{
		list->head = new_node;
	}
	else
	{
		prev->next = new_node;
	}
	list->length++;
	return TRUE;
}

BOOLEAN add_loan_node(struct loan_list *list, struct loan_info *loan)
{
	struct loan_node *new_node, *prev, *curr;
	if(list == NULL || loan == NULL)
		return FALSE;
	prev = NULL;
	curr = list->head;
	new_node = malloc(sizeof(new_node));
	if(!new_node)
	{
		return FALSE;
	}
	new_node->data = loan;
	while(curr != NULL && strcmp(loan->memberID, curr->data->memberID))
	{
		prev = curr;
		curr = curr->next;
	}
	new_node->next = curr;
	if(prev == NULL)
	{
		list->head = new_node;
	}
	else
	{
		prev->next = new_node;
	}
	list->length++;
	return TRUE;
}


