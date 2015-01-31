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
#ifndef ETS_STRUCTURES
#define ETS_STRUCTURES
#include "ets_utility.h"
#define MEMBER_SUBHEADING "ID      Name                             # Lent"
/* this will remove warnings on unused variables in the skeleton code */
#define UNUSED(var) (void)var
#define NUMARGS 4
#define IDLEN 5
#define NAMELEN 31
#define EQUIP_FIELDS 3
#define MEMBER_FIELDS 4

/* This is the ets structure you will pass to many functions */

struct ets 
{
	struct ets_list *items_list;
	struct ets_list *loans_list;
	struct ets_list *members_list;
	char *loan_file;
	char *equip_file;
	char *member_file;
};

struct ets_list
{
	struct ets_node *head;
	unsigned length;
};

struct ets_node
{
	struct ets_item *data;
	struct ets_node *next;
};

struct ets_item
{
	char itemId[IDLEN + 1];
	char itemName[NAMELEN + 1];
	unsigned available;
	char memberId[IDLEN + 1];
	char firstName[NAMELEN + 1];
	char lastName[NAMELEN + 1];
	char borrowerId[IDLEN + 1];
	char borroweeId[IDLEN + 1];
	unsigned items_borrowed;
	unsigned total;
};

enum ets_fields
{
	ITEM_ID, ITEM_NAME, ITEM_AVAILABILITY
};
enum loan_fields
{
	BORROWER_ID, BORROWEE_ID, ITEMS_BORROWED
};
enum member_fields
{
	MEMBER_ID, FIRST_NAME, LAST_NAME
};
BOOLEAN ets_init(struct ets * ets);
BOOLEAN load_data(struct ets * ets, const char * equip_fname, const char * member_fname, const char * loan_fname);
BOOLEAN add_node(struct ets_list *list, struct ets_item *item);
BOOLEAN add_member_node(struct ets_list *list, struct ets_item *member);
void create_loans(struct ets_item *item, char *borrowerId, char *borroweeId, unsigned quantity);
void create_item(struct ets_item *item, char *itemId, char *name, unsigned quantity);
void create_member(struct ets_item *member, char *memberId, char *lastName, char *firstName);
void free_node(struct ets_node *node);
void ets_free(struct ets * ets);
void print_item(struct ets * ets, char *itemId);
BOOLEAN combine_items_loans(struct ets * ets);
BOOLEAN combine_members_loans(struct ets * ets);
BOOLEAN combine_members_loans2(struct ets * ets);
BOOLEAN delete_item_node(struct ets_list *list, char *item_id, struct ets_item *removed_item);
BOOLEAN delete_member_node(struct ets_list *list, char *memberId, struct ets_item *removed_member);
BOOLEAN delete_loan_node(struct ets_list *list, char *itemId, struct ets_item *removed_loan);
BOOLEAN find_item(struct ets *ets, char *needle);
BOOLEAN find_member(struct ets *ets, char *needle);
BOOLEAN find_loan(struct ets * ets, char *itemId, char *memberId);
BOOLEAN is_valid_item(char *field, enum ets_fields field_type);
BOOLEAN is_valid_member(char *field, enum member_fields field_type);
BOOLEAN is_valid_loan(char *field, enum loan_fields field_type);
BOOLEAN save_item_data(struct ets * ets, FILE * itemFp);
BOOLEAN save_member_data(struct ets * ets, FILE * memberFp);
BOOLEAN save_loan_data(struct ets * ets, FILE * loanFp);
BOOLEAN item_borrowed(struct ets * ets, char * itemId, unsigned quantity);
void print_member(struct ets * ets, char *memberId);
void display_member_info(struct ets * ets, char *id);
void add_to_existing_loan(struct ets * ets, char *memberId, char *itemId, unsigned amount);
BOOLEAN item_returned(struct ets * ets, char * itemId, unsigned quantity);
#endif
