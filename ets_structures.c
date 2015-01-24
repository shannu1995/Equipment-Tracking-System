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
	FILE *equip_file, *member_file, *loan_file;
	char *token;
	char *tokens[NUM_FIELDS];
	char line[BUFFER_SIZE];
	enum string_result result;
	enum equip_fields field_type;
	unsigned quantity;
	UNUSED(member_file);
	UNUSED(loan_file);
	UNUSED(member_fname);
	UNUSED(loan_fname);      
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
	return FALSE;
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
